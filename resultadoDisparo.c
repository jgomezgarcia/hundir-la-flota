#include <stdio.h>
#include <stdlib.h>
#include "resultadoDisparo.h"

static int buscarBarco(int, int, int, char **, char **, int **, int **, int *);

// Función auxiliar para recorrer el barco completo (DFS)
// Precondición: Recibe la fila y columna para buscar donde esta el barco para evaluarlo
// Postcondición: Devuelve un valor (1 si el barco se encuentra hundido), (0 si el barco no se encuentra totalmente hundido)

static int buscarBarco(int fila, int columna, int tam, char **flota, char **oponente, int **visitado, int **coordenadas, int *contador) {
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    visitado[fila][columna] = 1;
    coordenadas[*contador][0] = fila;
    coordenadas[*contador][1] = columna;
    (*contador)++;

    int hundido = 1;

    for (int k = 0; k < 8; k++) {
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

// Precondición: Recibir el disparo según la estructura guardada de cada jugador ( disparo automatico o manual) . 
// Postcondición: Devuelve un valor del tipo enumerado de resultado, segun el resultado del disparo

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

    if(tableroOponente[fila][columna] == 'A' || tableroOponente[fila][columna] == 'H' || tableroOponente[fila][columna] == 'T'){
      return REPETIDO;
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

            // ← insertar aquí: marcar adyacentes como agua
            int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
            int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

            for (int i = 0; i < contador; i++) {
                int x = coordenadas[i][0];
                int y = coordenadas[i][1];
                for (int k = 0; k < 8; k++) {
                    int nx = x + dx[k];
                    int ny = y + dy[k];

                    if (nx >= 0 && nx < tam_tablero && ny >= 0 && ny < tam_tablero) {
                        if (tableroOponente[nx][ny] == '-') {
                            tableroOponente[nx][ny] = 'A';
                        }
                    }
                }
            }

            // Liberar memoria antes de retornar
            for (int i = 0; i < tam_tablero; i++) free(auxVisitado[i]);
            free(auxVisitado);
            for (int i = 0; i < tam_tablero * tam_tablero; i++) free(coordenadas[i]);
            free(coordenadas);

            return HUNDIDO;
        } else {
            // Liberar memoria antes de retornar
            for (int i = 0; i < tam_tablero; i++) free(auxVisitado[i]);
            free(auxVisitado);
            for (int i = 0; i < tam_tablero * tam_tablero; i++) free(coordenadas[i]);
            free(coordenadas);

            return TOCADO;
        }
    } else {
        tableroOponente[fila][columna] = 'A';

        // Liberar memoria antes de retornar
        for (int i = 0; i < tam_tablero; i++) free(auxVisitado[i]);
        free(auxVisitado);
        for (int i = 0; i < tam_tablero * tam_tablero; i++) free(coordenadas[i]);
        free(coordenadas);

        return AGUA;
    }
}

// Precondición: Recibe la estructura jugador, y que el "resultado" haya sido o bien AGUA o REPETIDO
// Postcondición: Intercambia el turno de los jugadores

void cambiarTurno(jugador *jugadores, int jugadorTurno){
  jugadores[!jugadorTurno].turno = 1;
  jugadores[jugadorTurno].turno = 0;
}
