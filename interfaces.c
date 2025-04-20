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

static int encontrarJugadorTurno(jugador **jugadores){
  for(int i = 0; i < MAX_JUGADORES; i++){
    if((*jugadores)[i].turno == 1){
      return i;
    }
  }

  return -1;
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
        int filaDisparo, colDisparo, terminado = 0, indexJugadorTurno;
        resultado resultadoDisparoPartida;

        switch (op) {
            case 1: {
                // Colocación de barcos para ambos jugadores
                for (int i = 0; i < MAX_JUGADORES; i++) {
                    system("cls");
                    printf("=== COLOCANDO BARCOS PARA %s ===\n\n", (*jugadores)[i].Nom_Jugador);
                    colocarBarcos(&(*jugadores)[i], *barcosElegidos, numBarcos, tam_tablero);

                    printf("\nPresiona Enter para continuar...");
                    limpiarBuffer();
                    getchar();
                }
                printf("\n¡Todos los barcos han sido colocados!\n");
                printf("Preparados para comenzar la batalla...\n");
                Sleep(500);
                system("cls");

                while(!terminado){
                    mostrarEncabezado("¡ACABA CON EL ENEMIGO!");
                  indexJugadorTurno = encontrarJugadorTurno(jugadores);
                  printf("TURNO DE %s. \n", (*jugadores)[indexJugadorTurno].Nom_Jugador);
                  if((*jugadores)[indexJugadorTurno].Tipo_Disparo == 'M'){
                    printf("Asi van tus disparos: \n");
                    imprimirTableroOponente((*jugadores)[indexJugadorTurno].Tablero_oponente, tam_tablero);
                    int entradaValida = 0;
                    do {
                        printf("Ingrese la fila a disparar: ");
                            if (scanf("%d", &filaDisparo) != 1) {
                                printf("Entrada inválida. Debe ingresar un número.\n");
                        while (getchar() != '\n');
                        continue;
                        }

                        printf("Ingrese la columna a disparar: ");
                            if (scanf("%d", &colDisparo) != 1) {
                                printf("Entrada inválida. Debe ingresar un número.\n");
                        while (getchar() != '\n');
                        continue;
                        }

                        if (filaDisparo >= 0 && filaDisparo < tam_tablero && colDisparo >= 0 && colDisparo < tam_tablero) {
                            entradaValida = 1;
                        } else {
                            printf("Coordenadas fuera del tablero. Intente de nuevo.\n");
                            }

                        while (getchar() != '\n');

                    } while (!entradaValida);

                    resultadoDisparoPartida = resultadoDisparo(filaDisparo, colDisparo, tam_tablero, (*jugadores)[!indexJugadorTurno].Tablero_flota, (*jugadores)[indexJugadorTurno].Tablero_oponente);
                    (*jugadores)[indexJugadorTurno].Num_Disparos += 1;
                    imprimirTableroOponente((*jugadores)[indexJugadorTurno].Tablero_oponente, tam_tablero);
                    switch(resultadoDisparoPartida){
                      case AGUA:
                        printf("Ha disparado en agua, pierde su turno. \n");
                        (*jugadores)[!indexJugadorTurno].turno = 1;
                        (*jugadores)[indexJugadorTurno].turno = 0;
                      break;

                      case TOCADO:
                        printf("Ha tocado un barco, siga disparando. \n");
                      break;

                      case HUNDIDO:
                        printf("Enhorabuena, ha hundido un barco, siga disparando. \n");
                        (*jugadores)[!indexJugadorTurno].Num_Barcos -= 1;
                      break;
                    }
                    printf("\nPresiona Enter para continuar...");
                    limpiarBuffer();
                    getchar();
                    system("cls");


                  } else {

                    //Módulo de Dani
                          static int ultimo_fila = -1, ultimo_columna = -1;
    static int tocado = 0, direccion_fila = 0, direccion_columna = 0, impactos = 0;

    disparo_automatico((*jugadores)[indexJugadorTurno].Tablero_oponente, tam_tablero,
                       &filaDisparo, &colDisparo, &ultimo_fila, &ultimo_columna,
                       &tocado, &direccion_fila, &direccion_columna, &impactos);

    printf("Disparo automatico realizado en [%d][%d]\n", filaDisparo, colDisparo);
    resultadoDisparoPartida = resultadoDisparo(filaDisparo, colDisparo, tam_tablero,
                                               (*jugadores)[!indexJugadorTurno].Tablero_flota,
                                               (*jugadores)[indexJugadorTurno].Tablero_oponente);

    (*jugadores)[indexJugadorTurno].Num_Disparos += 1;
    imprimirTableroOponente((*jugadores)[indexJugadorTurno].Tablero_oponente, tam_tablero);

    switch (resultadoDisparoPartida) {
        case AGUA:
            printf("Disparo automatico cayó en agua. Pierde su turno.\n");
            (*jugadores)[!indexJugadorTurno].turno = 1;
            (*jugadores)[indexJugadorTurno].turno = 0;
            tocado = 0;
            direccion_fila = 0;
            direccion_columna = 0;
            impactos = 0;
            printf("\nPresiona Enter para continuar...");
            limpiarBuffer();
            getchar();
            break;

        case TOCADO:
            printf("Disparo automatico ha tocado un barco. Continua.\n");
            tocado = 1;
            ultimo_fila = filaDisparo;
            ultimo_columna = colDisparo;
            printf("\nPresiona Enter para continuar...");
            limpiarBuffer();
            getchar();
            break;

        case HUNDIDO:
            printf("Disparo automatico ha hundido un barco. Continua.\n");
            (*jugadores)[!indexJugadorTurno].Num_Barcos -= 1;
            tocado = 0;
            direccion_fila = 0;
            direccion_columna = 0;
            impactos = 0;
            printf("\nPresiona Enter para continuar...");
            limpiarBuffer();
            getchar();
            break;
    }

    system("cls");
}

                  }

                  if((*jugadores)[!indexJugadorTurno].Num_Barcos == 0){
                    printf("Enhorabuena %s, has ganado la partida. \n", (*jugadores)[indexJugadorTurno].Nom_Jugador);
                    printf("\nPresiona Enter para continuar...");
                    limpiarBuffer();
                    getchar();
                    (*jugadores)[indexJugadorTurno].Ganador_Ronda = GANADOR;
                    terminado = 1;
                  }
                }

                Sleep(1000);


                return;
            }
            case 2:
                for(int i=0; i<MAX_JUGADORES; i++){
                    inicializarTableros((*jugadores)[i].Tablero_flota, (*jugadores)[i].Tablero_oponente, tam_tablero);
                }
                printf("\nPartida reiniciada.\n");
                Sleep(1000);
                return;
            case 3:
                return;
        }
    }
}
