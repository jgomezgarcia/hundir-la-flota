#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "interfaces.h"
#include "configuracion.h"
#include "colocarFlota.h"
#include "posPartida.h"
#include "resultadoDisparo.h"
#include "disparoAutomatico.h"

void menuPrincipal(jugador *jugadores, barcos *barcosElegidos, int tam_tablero, int numBarcos, int tam_lista){

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
        printf("\nTu opcion: ");
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
    case 1: menuConfiguracion(jugadores, barcosElegidos, tam_tablero, numBarcos, tam_lista);
            break;
    case 2: menuPartida();
            break;
    case 3: Sleep(500);
            system("cls");
            Sleep(500);
            printf("Saliendo del juego...\n");
            Sleep(1000);
            exit(1);
    }
}

void menuConfiguracion(jugador *jugadores, barcos *barcosElegidos, int tam_tablero, int numBarcos, int tam_lista){
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
        printf("\nTu opcion: ");
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
    case 1:
            barcosElegidos = barcosParaJugar(&numBarcos, &tam_lista, &tam_tablero);
            jugadores = configurarJugador(tam_tablero, numBarcos);
            break;
    case 2: mostrarConfiguracion(tam_tablero, numBarcos, barcosElegidos, jugadores);
            break;
    case 3: eliminarConfiguracion(barcosElegidos, jugadores, tam_tablero);
            break;
    case 4: guardarPartida(barcosElegidos, jugadores, tam_lista, numBarcos, tam_tablero);
            break;
    case 5: barcosElegidos = recuperarBarcos(&tam_tablero, &numBarcos, &tam_lista);
            break;
    case 6: menuPrincipal(jugadores, barcosElegidos, tam_tablero, numBarcos, tam_lista);
            break;
        }
}

void menuPartida(jugador *jugadores, barcos *barcosElegidos, int tam_tablero, int numBarcos, int tam_lista){
    int op;
    int valido = 0, terminado;

    system("cls");
    Sleep(500);
    printf("****************************\n\nPARTIDA\n\n****************************\n\n");
    Sleep(500);

    printf ("Elige que quieres hacer\n\n");
    printf("Opciones:\n\n");
    printf("1.Jugar Partida\n2.Reiniciar Partida\n3.Reanudar\n4.Volver\n\n");
    Sleep(500);

    while (valido==0) {  // Bucle infinito hasta que se ingrese una opción válida
        printf("\nTu opcion: ");
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
    case 1:
            //Colocación de barcos en base al tipo de disparo
            for(int i = 0; i<MAX_JUGADORES; i++){
                if(jugador[i]->Tipo_Disparo=='M'){
                    colocarBarcos(&jugador[i], barcosElegidos, numBarcos, tam_tablero);
                }
                else{
                    for(int j =0;j<numBarcos;j++){
                        colocarBarcoAutomatico(jugador[i], barcosElegidos, tam_tablero);
                    }
                }
            }
            system("cls");
            //
            do{

            }while();

            break;
    case 2: //por determinar
            break;
    case 3: //por determinar
            break;
    case 4: menuPrincipal(jugadores, barcosElegidos, tam_tablero, numBarcos, tam_lista);
            break;
        }
}
