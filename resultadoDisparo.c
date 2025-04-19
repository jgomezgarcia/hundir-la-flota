#include <stdio.h>
#include <stdlib.h>

#include "resultadoDisparo.h"

typedef enum {TOCADO, HUNDIDO, AGUA} resultado;

static int buscarBarco(int fila, int columna, int tam, char flota[10][10], char oponente[10][10], int **visitado, int **coordenadas, int *contador);

static int buscarBarco(int fila, int columna, int tam, char **flota, char **oponente, int **visitado, int **coordenadas, int *contador) {
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};  //Distintas combinaciones para desplazarnos alrededor del disparo
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};  //Distintas combinaciones para desplazarnos alrededor del disparo

    visitado[fila][columna] = 1;
    coordenadas[*contador][0] = fila;
    coordenadas[*contador][1] = columna;
    (*contador)++;

    int hundido = 1;

    for (int k = 0; k < 8; k++) {  //
        int nf = fila + dx[k];
        int nc = columna + dy[k];

        if (nf >= 0 && nf < tam && nc >= 0 && nc < tam && !visitado[nf][nc]) {
            if (flota[nf][nc] == 'X') {
                if (oponente[nf][nc] == '-') {
                    hundido = 0; // parte viva
                } else if (oponente[nf][nc] == 'T') {
                    if (!buscarBarco(nf, nc, tam, flota, oponente, visitado, coordenadas, contador))
                        hundido = 0;
                }
            }
        }
    }

    return hundido;
}

resultado resultadoDisparo(int fila, int columna, int tam_tablero, char **tableroFlota, char **tableroOponente) {
    // Reservamos matriz de visitado
    int **auxVisitado = malloc(tam_tablero * sizeof(int *));
    int **coordenadas = malloc(tam_tablero * tam_tablero * sizeof(int *));
    for (int i = 0; i < tam_tablero; i++) {
        auxVisitado[i] = calloc(tam_tablero, sizeof(int));
    }
    for (int i = 0; i < tam_tablero * tam_tablero; i++) {
        coordenadas[i] = malloc(2 * sizeof(int));  // cada posición guarda [fila, columna]
    }

    // Comprobamos el disparo
    if (tableroFlota[fila][columna] == 'X') {
        tableroOponente[fila][columna] = 'T';

        int contador = 0;
        int hundido = buscarBarco(fila, columna, tam_tablero, tableroFlota, tableroOponente, auxVisitado, coordenadas, &contador);

        if (hundido) {
            for (int i = 0; i < contador; i++) {
                int x = coordenadas[i][0];
                int y = coordenadas[i][1];
                tableroOponente[x][y] = 'H';
            }

            // Liberamos memoria
            for (int i = 0; i < tam_tablero; i++) free(auxVisitado[i]);
            free(auxVisitado);
            for (int i = 0; i < tam_tablero * tam_tablero; i++) free(coordenadas[i]);
            free(coordenadas);

            return HUNDIDO;
        } else {
            // Liberamos memoria
            for (int i = 0; i < tam_tablero; i++) free(auxVisitado[i]);
            free(auxVisitado);
            for (int i = 0; i < tam_tablero * tam_tablero; i++) free(coordenadas[i]);
            free(coordenadas);

            return TOCADO;
        }
    } else {
        tableroOponente[fila][columna] = 'A';

        // Liberaramos memoria
        for (int i = 0; i < tam_tablero; i++) free(auxVisitado[i]);
        free(auxVisitado);
        for (int i = 0; i < tam_tablero * tam_tablero; i++) free(coordenadas[i]);
        free(coordenadas);

        return AGUA;
    }
}
