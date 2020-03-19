#include <stdio.h>

int main()
{
    char nombre[50];
    char telefono[10];
    char direccion[80];
    int formaPago;
    int opcion;

    printf("!Bienvenido a FastEats!\n\n");
    printf(" Por favor indique:\n");
    printf("Nombre: ");
    gets(nombre);
    printf("Telefono: ");
    gets(telefono);
    printf("Direccion: ");
    gets(direccion);
    printf("\n Indique forma de pago:\n");

    do {
        printf("1.- Efectivo\n");
        printf("2.- Tarjeta\n");
        printf(" Opcion: ");
        scanf("%d", &formaPago);
    } while (formaPago != 1 && formaPago != 2);

    do {
        printf("\n %s escoja la opcion mas apetecible para hoy\n",nombre);
        printf("1.- Comida rapida. (Burguer King, Mc Donald's, KFC , tgb)\n");
        printf("2.- Comida italina. (tagliatelle, gynos, pomodoro, massart)\n");
        printf("3.- Comida China. (Dragon inn ,Shangai, wang li, sichuan)\n");
        printf("4.- No deseo realizar otro pedido\n");
        printf(" Opcion: ");
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                printf("Perfecto! Comida rapida ha sido su eleccion\n");
                break;
            case 2:
                printf("Perfecto! Comida italiana ha sido su eleccion\n");
                break;
            case 3:
                printf("Perfecto! Comida rapida ha sido su eleccion\n");
                break;
            case 4:
                printf("Entendido!\n");
                break;
        }
        
     printf("Gracias por utilizar nuestros servicios\n");
     
    } while (opcion != 4);

    return 0;
}
