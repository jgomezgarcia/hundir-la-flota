#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "interfaces.h"
#include "configuracion.h"
//#include "" -> Incompleto

void menuPrincipal(){

    int op;
    int valido = 0;

    system("cls"); //Limpia la terminal

    printf("****************************\n\nBIENVENIDO A HUNDIR LA FLOTA\n\n****************************\n\n");
    Sleep(500);

    printf ("Elige que quieres hacer\n\n");
    printf("Opciones:\n\n");
    printf("1.Configuracion\n2.Jugar\n3.Salir\n\n");
    Sleep(500);

    while (valido==0) {  // Bucle infinito hasta que se ingrese una opción válida
        printf("Tu opcion: ");
        if ((scanf("%d", &op)) != 1) {
            printf("\nEntrada invalida, debes introducir un numero\n");
        }else if (op >= 1 && op <= 3) {
        valido = 1;
        } else {
        printf("\nNumero no valido, introduce una opcion valida.\n");
        }
        // Limpieza del búfer
        while (getchar() != '\n');
    }


    switch (op){
    case 1: menuConfiguracion();
            break;
    case 2: menuPartida();
            break;
    case 3: Sleep(500);
            system("cls");
            Sleep(500);
            printf("\n\nSaliendo del juego...\n\n\n\n\n\n");
            Sleep(1000);
            exit(1);
    }
}

void menuConfiguracion(){
    int op;
    int valido = 0;
    system("cls");
    Sleep(500);
    printf("****************************\n\nCONFIGURACION\n\n****************************\n\n");
    Sleep(500);

    printf ("Elige que quieres hacer\n\n");
    printf("Opciones:\n\n");
    printf("1.Introducir datos\n2.Mostrar\n3.Borrar\n4.Guardar\n5.Cargar\n6.Volver\n\n");
    Sleep(500);

    while (valido==0) { // Bucle infinito hasta que se ingrese una opción válida
        printf("Tu opcion: ");
        if ((scanf("%d", &op)) != 1) {
            printf("\nEntrada invalida, debes introducir un numero\n");
        }else if (op >= 1 && op <= 6) {
        valido = 1;
        } else {
        printf("\nNumero no valido, introduce una opcion valida.\n");
        }
        // Limpieza del búfer
        while (getchar() != '\n');
    }

    switch (op){
    case 1: //por determinar
            break;
    case 2: //por determinar
            break;
    case 3: //por determinar
            break;
    case 4: //por determinar
            break;
    case 5: //por determinar
            break;
    case 6: //por determinar
            break;
        }
}

void menuPartida(){
    int op;
    int valido = 0;

    system("cls");
    Sleep(500);
    printf("****************************\n\nPARTIDA\n\n****************************\n\n");
    Sleep(500);

    printf ("Elige que quieres hacer\n\n");
    printf("Opciones:\n\n");
    printf("1.Jugar Partida\n2.Reiniciar Partida\n3.Reanudar\n4.Volver\n\n");
    Sleep(500);

    while (valido==0) {  // Bucle infinito hasta que se ingrese una opción válida
        printf("Tu opcion: ");
        if ((scanf("%d", &op)) != 1) {
            printf("\nEntrada invalida, debes introducir un numero\n");
        }else if (op >= 1 && op <= 4) {
        valido = 1;
        } else {
        printf("\nNumero no valido, introduce una opcion valida.\n");
        }
        // Limpieza del búfer
        while (getchar() != '\n');
    }

    switch (op){
    case 1: //por determinar
            break;
    case 2: //por determinar
            break;
    case 3: //por determinar
            break;
    case 4: //por determinar
            break;
        }
}

