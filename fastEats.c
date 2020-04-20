#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct {
   int id;
   char tipoRestaurante[10];
} eTipo;

typedef struct {
   int tipo;
   int id;
   char nombreRestaurante[20];
} eRestaurante;

typedef struct {
   int restaurante;
   int id;
   double precio;
   int complemento;
   int cantidad;
   char menu[75];
} eMenu;

typedef struct {
   int restaurante;
   int menu;
   int id;
   double precio;
   char descripcion[30];
} eOpcion;

typedef struct {
   int restaurante;
   int id;
   int numero;
   int opcion;
   char descripcion[30];
} eComplemento;


int opcionTipo, opcionRestaurante, opcionMenu, opcionOpcion, opcionComplemento;
int totalTipo, totalRestaurante, totalMenu, totalOpcion, totalComplemento;
int posicionMenu, posicionOpcion, posicionComplemento;
double aPagar=0.0;

int leerTipo(eTipo tipos[]);
int leerRestaurante(eRestaurante restaurantes[]);
int leerMenu(eMenu menus[]);
int leerOpcion(eOpcion opciones[]);
int leerComplemento(eComplemento complementos[]);
FILE *archivoPedido;

void seleccionOpcion(eRestaurante restaurante[], eMenu menu[],
                     eOpcion opcion[]);
void seleccionComplemento(eRestaurante restaurante[], eMenu menu[],
                    eComplemento complemento[]);


int main()
{
    eTipo tipo[10];
    eRestaurante restaurante[20];
    eMenu menu[40];
    eOpcion opcion[60];
    eComplemento complemento[70];
    char nombre[50];
    char telefono[15];
    char direccion[80];
    int formaPago;
    int i, j;

    archivoPedido = fopen("pedidos.txt","w");
    totalTipo = leerTipo(tipo);
    totalRestaurante = leerRestaurante(restaurante);
    totalMenu = leerMenu(menu);
    totalOpcion = leerOpcion(opcion);
    totalComplemento = leerComplemento(complemento);

    fprintf(archivoPedido,"%s\n\n","     FastEats");
    printf(" Â¡Bienvenido a FastEats!\n\n");
    printf(" Por favor indique:\n");
    printf("Nombre: ");
    gets(nombre);
    fprintf(archivoPedido,"Nombre       : %s\n",nombre);
    printf("Telefono: ");
    gets(telefono);
    fprintf(archivoPedido,"TelÃ©fono     : %s\n",telefono);
    printf("Direccion: ");
    gets(direccion);
    fprintf(archivoPedido,"DirecciÃ³n    : %s\n",direccion);
    printf("\n Indique forma de pago:\n");

    do {
        printf("1.- Efectivo\n");
        printf("2.- Tarjeta\n");
        printf(" Opcion: ");
        scanf("%d", &formaPago);
    } while (formaPago != 1 && formaPago != 2);
    if (formaPago == 1)
       fprintf(archivoPedido,
       "Forma de pago: Efectivo\n\n  S u   P e d i d o\n  =================\n");
    else
       fprintf(archivoPedido,
        "Forma de pago: Tarjeta\n\n  S u   P e d i d o\n  =================\n");

// Selecciona el tipo de restaurante para mostrar solo los de ese tipo

    do {
        printf("\n %s escoja la opcion mas apetecible para hoy:\n", nombre);
        for (i=0;i<totalTipo;i++) {
            printf("%d.- %s", tipo[i].id, tipo[i].tipoRestaurante);
        };
        printf("0.- Salir y guardar pedido\n");
        printf(" Opcion: ");
        scanf("%d", &opcionTipo);
        
        if (opcionTipo == 0) {
           printf("Gracias por utilizar nuestros servicios\n");
           break;
        }
        else
           fprintf(archivoPedido,"-Comida %s",tipo[opcionTipo-1].tipoRestaurante);


// Muestra los restaurantes del tipo seleccionado

        do {
           printf("\n Restaurantes de comida %s\n",tipo[opcionTipo-1].tipoRestaurante);
           for (j=0; j<totalRestaurante; j++) {
               if (restaurante[j].tipo == opcionTipo) {
                  printf(" %d.- %s", restaurante[j].id,
                         restaurante[j].nombreRestaurante);
               }
           }
           printf(" 0.- Regresar al menu anterior\n");
           printf("  Opcion: ");
           scanf("%d", &opcionRestaurante);
       
           if (opcionRestaurante == 0)
              continue;
           else
              fprintf(archivoPedido," -Restaurante %s",
                      restaurante[opcionRestaurante-1].nombreRestaurante);

// Muestra el menu del restaurante seleccionado

           do {
              printf("\n Menu de %s\n",
                     restaurante[opcionRestaurante-1].nombreRestaurante);
              posicionMenu = -1;
              for (j=0; j<totalMenu; j++) {
                  if (menu[j].restaurante == opcionRestaurante) {
                     if (posicionMenu == -1)
                        posicionMenu = j;
                     if (menu[j].precio == 0 )
                        printf("  %d.- %s", menu[j].id, menu[j].menu);
                     else
                        printf("  %d.- %s\tEuros %.2lf\n", menu[j].id,
                               menu[j].menu, menu[j].precio);
                  }
              }
              printf("  0.- Regresar al menu anterior\n");
              printf("   Opcion: ");
              scanf("%d", &opcionMenu);

              if (opcionMenu == 0)
                 continue;
              else
                 if (menu[opcionMenu-1+posicionMenu].precio == 0 )
                    fprintf(archivoPedido,"  -%s",
                            menu[opcionMenu-1+posicionMenu].menu);
                 else {
                    fprintf(archivoPedido,"  -%s\t\t\tEuros %.2lf\n",
                            menu[opcionMenu-1+posicionMenu].menu,
                            menu[opcionMenu-1+posicionMenu].precio);
                    aPagar+=menu[opcionMenu-1+posicionMenu].precio;
                 }

// Muestra las opciones del menu seleccionado

              seleccionOpcion(restaurante, menu, opcion);

// Muestra los complementos del menu seleccionado

              seleccionComplemento(restaurante, menu, complemento);

           } while (opcionMenu != 0);
        } while (opcionRestaurante != 0);
    } while (opcionTipo != 0);
    fprintf(archivoPedido,"\n\t  +--------------------------+\n");
    fprintf(archivoPedido,"\t  | Total a pagar ==> %6.2lf |\n",aPagar);
    fprintf(archivoPedido,"\t  +--------------------------+\n");

    return 0;
}

int leerTipo(eTipo tipos[]) {
   eTipo tipo;
   FILE *archivoTipo;
   int total=0;

   archivoTipo = fopen("tipos.txt","r");
   if (archivoTipo == NULL) {
      printf("Error al abrir archivo de tipos de restaurantes\n");
      exit(1);
   }
   while (!feof(archivoTipo)) {
      fscanf(archivoTipo,"%d,", &tipo.id);
      fgets(tipo.tipoRestaurante, 10, archivoTipo);
      tipos[total] = tipo;
      total++;
   }
   fclose(archivoTipo);
   return total-1;
}

int leerRestaurante(eRestaurante restaurantes[]) {
   eRestaurante restaurante;
   FILE *archivoRestaurante;
   int total=0;

   archivoRestaurante = fopen("restaurantes.txt","r");
   if (archivoRestaurante == NULL) {
      printf("Error al abrir archivo de restaurantes\n");
      exit(2);
   }
   while (!feof(archivoRestaurante)) {
      fscanf(archivoRestaurante, "%d,%d,", &restaurante.tipo, &restaurante.id);
      fgets(restaurante.nombreRestaurante, 20, archivoRestaurante);
      restaurantes[total] = restaurante;
      total++;
   }
   fclose(archivoRestaurante);
   return total-1;
}

int leerMenu(eMenu menus[]) {
   eMenu menu;
   FILE *archivoMenu;
   int total=0;

   archivoMenu = fopen("menu.txt","r");
   if (archivoMenu == NULL) {
      printf("Error al abrir archivo de menus\n");
      exit(3);
   }
   while (!feof(archivoMenu)) {
      fscanf(archivoMenu, "%d,%d,%lf,%d,%d,", &menu.restaurante, &menu.id,
             &menu.precio, &menu.complemento, &menu.cantidad);
      fgets(menu.menu, 75, archivoMenu);
      menus[total] = menu;
      total++;
   }
   fclose(archivoMenu);
   return total-1;
}

int leerOpcion(eOpcion opciones[]) {
   eOpcion opcion;
   FILE *archivoOpcion;
   int total=0;

   archivoOpcion = fopen("opciones.txt","r");
   if (archivoOpcion == NULL) {
      printf("Error al abrir archivo de opciones\n");
      exit(4);
   }
   while (!feof(archivoOpcion)) {
      fscanf(archivoOpcion,"%d,%d,%d,%lf,", &opcion.restaurante,
             &opcion.menu, &opcion.id, &opcion.precio);
      fgets(opcion.descripcion, 30, archivoOpcion);
      opciones[total] = opcion;
      total++;
   }
   fclose(archivoOpcion);
   return total-1;
}

int leerComplemento(eComplemento complementos[]) {
   eComplemento complemento;
   FILE *archivoComplemento;
   int total=0;

   archivoComplemento = fopen("complementos.txt","r");
   if (archivoComplemento == NULL) {
      printf("Error al abrir archivo de complementos\n");
      exit(5);
   }
   while (!feof(archivoComplemento)) {
      fscanf(archivoComplemento,"%d,%d,%d,%d,", &complemento.restaurante,
             &complemento.id, &complemento.numero, &complemento.opcion);
      fgets(complemento.descripcion, 30, archivoComplemento);
      complementos[total] = complemento;
      total++;
   }
   fclose(archivoComplemento);
   return total-1;
}


// Funcion para seleccionar las opciones si las tiene

void seleccionOpcion(eRestaurante restaurante[], eMenu menu[],
                    eOpcion opcion[]) {
int cantidadOpcion, hayOpcion=0;
int j;

  cantidadOpcion = 0;
  for (j=0; j<totalOpcion; j++) {
     if (opcion[j].restaurante == opcionRestaurante &&
        opcion[j].menu == opcionMenu) {
        if (!hayOpcion) {
           printf("\n Opciones del menu %s\n",
                  menu[opcionMenu-1+posicionMenu].menu);
           hayOpcion=1;
           posicionOpcion = j;
        }
        if (opcion[j].precio == 0 )
           printf("   %d.- %s", opcion[j].id, opcion[j].descripcion);
        else
           printf("   %d.- %s\tEuros %.2lf\n", opcion[j].id,
                  opcion[j].descripcion, opcion[j].precio);
        cantidadOpcion++;
     }
  }
}

// Funcion para seleccionar los complementos si los tiene

void seleccionComplemento(eRestaurante restaurante[], eMenu menu[],
                    eComplemento complemento[]) {
int complementoAnterior;
int i,j;

   if (menu[opcionMenu-1+posicionMenu].complemento != 0) {
      printf("\n Complementos del menu %s\n",
             menu[opcionMenu-1+posicionMenu].menu);
      for (i=1; i<=menu[opcionMenu-1+posicionMenu].cantidad; i++) {
         posicionComplemento = -1;
         complementoAnterior = 1;
         for (j=0; j<totalComplemento; j++) {
             if (complemento[j].restaurante == opcionRestaurante &&
                 complemento[j].id ==
                                  menu[opcionMenu-1+posicionMenu].complemento) {
                if (complemento[j].numero == complementoAnterior) {
                   printf("    %d.- %s", complemento[j].opcion,
                          complemento[j].descripcion);
                   if (posicionComplemento == -1)
                      posicionComplemento = j;
                   else if (posicionComplemento == -2)
                      posicionComplemento = j-1;
                }
                else {
                   printf("     Opcion: ");
                   scanf("%d", &opcionComplemento);
                   fprintf(archivoPedido,"   %s",
                           complemento[opcionComplemento-1+posicionComplemento].descripcion);
                   posicionComplemento = -2;
                   complementoAnterior = complemento[j].numero;
                   printf("    %d.- %s", complemento[j].opcion,
                          complemento[j].descripcion);
                }
             }
         }
             printf("     Opcion: ");
             scanf("%d", &opcionComplemento);
             fprintf(archivoPedido,"   %s",
              complemento[opcionComplemento-1+posicionComplemento].descripcion);
      }
   }
   printf("su pedido esta realizado,muchas gracias. Desea algo mas?\n");
} 
