#include <stdlib.h>
#include <time.h>
#include "resultadoDisparo.h"

typedef enum {ALEATORIO, ALREDEDOR, DIRECCION, CAMBIO_DIRECCION} estado;

void disparoAutomatico(
    char **tablero_oponente,
    char **tablero_flota,
    int tam_tablero,
    int *fila, int *columna,
    int *ultima_fila, int *ultima_columna,
    int *numTocado,
    estado *estadoDisparoAnterior,
    int *ultima_direccionX, int *ultima_direccionY,
    resultado *resultadoDisparoA
) {
    static int indice_direccion = 0;
    static int primera_fila_tocado = -1;
    static int primera_columna_tocado = -1;
    static int necesita_cambio_direccion = 0;

    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int nueva_fila, nueva_columna;

    srand(time(NULL));

    int disparoRealizado = 0;

    // Modo ALEATORIO
    if (*estadoDisparoAnterior == ALEATORIO && !disparoRealizado) {
        do {
            *fila = rand() % tam_tablero;
            *columna = rand() % tam_tablero;
        } while (tablero_oponente[*fila][*columna] != '-');

        *resultadoDisparoA = resultadoDisparo(*fila, *columna, tam_tablero, tablero_flota, tablero_oponente);
        disparoRealizado = 1;

        if (*resultadoDisparoA == TOCADO) {
            *estadoDisparoAnterior = ALREDEDOR;
            *ultima_fila = *fila;
            *ultima_columna = *columna;
            primera_fila_tocado = *fila;
            primera_columna_tocado = *columna;
            indice_direccion = 0;
        }
    }

    // Modo ALREDEDOR
    if (*estadoDisparoAnterior == ALREDEDOR && !disparoRealizado) {
        while (indice_direccion < 8 && !disparoRealizado) {
            nueva_fila = *ultima_fila + dx[indice_direccion];
            nueva_columna = *ultima_columna + dy[indice_direccion];

            if (nueva_fila >= 0 && nueva_columna >= 0 &&
                nueva_fila < tam_tablero && nueva_columna < tam_tablero &&
                tablero_oponente[nueva_fila][nueva_columna] == '-') {

                *fila = nueva_fila;
                *columna = nueva_columna;
                *resultadoDisparoA = resultadoDisparo(*fila, *columna, tam_tablero, tablero_flota, tablero_oponente);
                disparoRealizado = 1;

                if (*resultadoDisparoA == TOCADO) {
                    *estadoDisparoAnterior = DIRECCION;
                    *ultima_direccionX = dx[indice_direccion];
                    *ultima_direccionY = dy[indice_direccion];
                    *ultima_fila = *fila;
                    *ultima_columna = *columna;
                } else if (*resultadoDisparoA == HUNDIDO) {
                    *estadoDisparoAnterior = ALEATORIO;
                    *numTocado = 0;
                }
            }
            indice_direccion++;
        }

        if (!disparoRealizado) {
            *estadoDisparoAnterior = ALEATORIO;
        }
    }

    // Modo DIRECCION
    if (*estadoDisparoAnterior == DIRECCION && !disparoRealizado) {
        nueva_fila = *ultima_fila + *ultima_direccionX;
        nueva_columna = *ultima_columna + *ultima_direccionY;

        if (nueva_fila >= 0 && nueva_columna >= 0 &&
            nueva_fila < tam_tablero && nueva_columna < tam_tablero &&
            tablero_oponente[nueva_fila][nueva_columna] == '-') {

            *fila = nueva_fila;
            *columna = nueva_columna;
            *resultadoDisparoA = resultadoDisparo(*fila, *columna, tam_tablero, tablero_flota, tablero_oponente);
            disparoRealizado = 1;

            if (*resultadoDisparoA == TOCADO) {
                *ultima_fila = *fila;
                *ultima_columna = *columna;
            } else if (*resultadoDisparoA == HUNDIDO) {
                *estadoDisparoAnterior = ALEATORIO;
                *numTocado = 0;
            } else {
                *estadoDisparoAnterior = CAMBIO_DIRECCION;
                *ultima_fila = primera_fila_tocado;
                *ultima_columna = primera_columna_tocado;
                *ultima_direccionX *= -1;
                *ultima_direccionY *= -1;
            }
        } else {
            *estadoDisparoAnterior = CAMBIO_DIRECCION;
            *ultima_fila = primera_fila_tocado;
            *ultima_columna = primera_columna_tocado;
            *ultima_direccionX *= -1;
            *ultima_direccionY *= -1;
        }
    }

    // Modo CAMBIO_DIRECCION
    if (*estadoDisparoAnterior == CAMBIO_DIRECCION && !disparoRealizado) {
        nueva_fila = *ultima_fila + *ultima_direccionX;
        nueva_columna = *ultima_columna + *ultima_direccionY;

        if (nueva_fila >= 0 && nueva_columna >= 0 &&
            nueva_fila < tam_tablero && nueva_columna < tam_tablero &&
            tablero_oponente[nueva_fila][nueva_columna] == '-') {

            *fila = nueva_fila;
            *columna = nueva_columna;
            *resultadoDisparoA = resultadoDisparo(*fila, *columna, tam_tablero, tablero_flota, tablero_oponente);
            disparoRealizado = 1;

            if (*resultadoDisparoA == TOCADO) {
                *estadoDisparoAnterior = DIRECCION;
                *ultima_fila = *fila;
                *ultima_columna = *columna;
            } else if (*resultadoDisparoA == HUNDIDO) {
                *estadoDisparoAnterior = ALEATORIO;
                *numTocado = 0;
            } else {
                *estadoDisparoAnterior = ALEATORIO;
            }
        } else {
            *estadoDisparoAnterior = ALEATORIO;
        }
    }
}
