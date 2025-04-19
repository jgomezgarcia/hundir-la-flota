#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "interfaces.h"
#include "configuracion.h"
#include "colocarFlota.h"
#include "posPartida.h"
#include "resultadoDisparo.h"
#include "disparoAutomatico.h"

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    while (getchar() != '\n');
}

// Función para mostrar el encabezado de un menú
static void mostrarEncabezado(const char *titulo) {
    system("cls");
    printf("****************************\n\n");
    printf("%s\n\n", titulo);
    printf("****************************\n\n");
    Sleep(500);
}

// Función para obtener una opción válida del usuario
static int obtenerOpcion(int min, int max) {
    int opcion;
    int valido = 0;

    while (!valido) {
        printf("\nTu opcion: ");
        if (scanf("%d", &opcion) != 1) {
            printf("\nEntrada invalida, debes introducir un numero\n");
        } else if (opcion >= min && opcion <= max) {
            valido = 1;
        } else {
            printf("\nNumero no valido, introduce una opcion entre %d y %d.\n", min, max);
        }
        limpiarBuffer();
    }

    return opcion;
}

void menuPrincipal(jugador **jugadores, barcos **barcosElegidos, int *tam_tablero, int *numBarcos, int *tam_lista) {
    while (1) {  // Bucle infinito para mantener el programa activo
        mostrarEncabezado("BIENVENIDO A HUNDIR LA FLOTA");

        printf("Opciones:\n\n");
        printf("1. Configuracion\n");
        printf("2. Jugar\n");
        printf("3. Salir\n\n");
        Sleep(500);

        int op = obtenerOpcion(1, 3);

        switch (op) {
            case 1:
                menuConfiguracion(jugadores, barcosElegidos, tam_tablero, numBarcos, tam_lista);
                break;
            case 2:
                if (*jugadores == NULL || *barcosElegidos == NULL) {
                    printf("\nDebes configurar la partida primero!\n");
                    Sleep(1000);
                } else {
                    menuPartida(jugadores, barcosElegidos, *tam_tablero, *numBarcos, *tam_lista);
                }
                break;
            case 3:
                mostrarEncabezado("SALIENDO DEL JUEGO");
                printf("Gracias por jugar. Hasta pronto!\n");
                Sleep(1000);
                exit(0);
        }
    }
}

void menuConfiguracion(jugador **jugadores, barcos **barcosElegidos, int *tam_tablero, int *numBarcos, int *tam_lista) {
    while (1) {  // Bucle para mantener el menú de configuración
        mostrarEncabezado("CONFIGURACION");

        printf("Opciones:\n\n");
        printf("1. Introducir datos\n");
        printf("2. Mostrar\n");
        printf("3. Borrar\n");
        printf("4. Guardar\n");
        printf("5. Cargar\n");
        printf("6. Volver\n\n");
        Sleep(500);

        int opcion = obtenerOpcion(1, 6);

        switch (opcion) {
            case 1:
                *barcosElegidos = barcosParaJugar(numBarcos, tam_lista, tam_tablero);
                *jugadores = configurarJugador(*tam_tablero, *numBarcos);
                Sleep(1000);
                break;
            case 2:
                if (*jugadores == NULL || *barcosElegidos == NULL) {
                    printf("\nNo hay datos configurados todavia!\n");
                    Sleep(1000);
                } else {
                    mostrarConfiguracion(*tam_tablero, *numBarcos, *barcosElegidos, *jugadores);
                    printf("\nPresiona Enter para continuar...");
                    getchar();
                }
                break;
            case 3:
                if (*jugadores != NULL && *barcosElegidos != NULL) {
                    eliminarConfiguracion(*barcosElegidos, *jugadores, *tam_tablero);
                    *jugadores = NULL;
                    *barcosElegidos = NULL;
                    printf("\nConfiguracion eliminada correctamente.\n");
                } else {
                    printf("\nNo hay configuracion para borrar!\n");
                }
                Sleep(1000);
                break;
            case 4:
                if (*jugadores != NULL && *barcosElegidos != NULL) {
                    guardarPartida(*barcosElegidos, *jugadores, *tam_lista, *numBarcos, *tam_tablero);
                    printf("\nPartida guardada correctamente.\n");
                } else {
                    printf("\nNo hay datos para guardar!\n");
                }
                Sleep(1000);
                break;
            case 5:
                *barcosElegidos = recuperarBarcos(tam_tablero, numBarcos, tam_lista);
                *jugadores = recuperarJugadores(*tam_tablero, *numBarcos, *tam_lista);
                printf("\nPartida cargada correctamente.\n");
                Sleep(1000);
                break;
            case 6:
                return;  // Salir del menú de configuración
        }
    }
}

void menuPartida(jugador **jugadores, barcos **barcosElegidos, int tam_tablero, int numBarcos, int tam_lista) {
    while (1) {
        mostrarEncabezado("PARTIDA");

        printf("Opciones:\n\n");
        printf("1. Jugar Partida\n");
        printf("2. Reiniciar Partida\n");
        printf("3. Volver\n\n");
        Sleep(500);

        int op = obtenerOpcion(1, 3);

        switch (op) {
            case 1: {
                // Colocación de barcos para ambos jugadores
                for (int i = 0; i < MAX_JUGADORES; i++) {
                    system("cls");
                    printf("=== COLOCANDO BARCOS PARA %s ===\n\n", (*jugadores)[i].Nom_Jugador);
                    colocarBarcos(&(*jugadores)[i], *barcosElegidos, numBarcos, tam_tablero);

                    //NO SE SI SE QUIERE IMPRIMIR EL TABLERO
                    //printf("\nTablero final de %s:\n", (*jugadores)[i].Nom_Jugador);
                    //imprimirTableroFlota((*jugadores)[i].Tablero_flota, tam_tablero);

                    guardarPartida(*barcosElegidos, *jugadores, tam_lista, numBarcos, tam_tablero);
                    printf("\nPresiona Enter para continuar...");
                    limpiarBuffer();
                    getchar();
                }
                printf("\n¡Todos los barcos han sido colocados!\n");
                printf("Preparados para comenzar la batalla...\n");
                Sleep(2000);
                system("cls");
                gestionar_turnos(&(*jugadores)[0], &(*jugadores)[1], tam_tablero, barcosElegidos, tam_lista, numBarcos);
                return;
            }
            case 2:
                // Aquí iriía la lógica de reiniciar la partida
                printf("\nPartida reiniciada.\n");
                Sleep(1000);
                return;
            case 3:
                return;
        }
    }
}
