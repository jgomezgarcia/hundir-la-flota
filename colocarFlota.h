#ifndef COLOCAR_BARCOS_H
#define COLOCAR_BARCOS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "configuracion.h"

typedef struct {
    char **tablero;
    int filas;
    int columnas;
} Tablero;

char ** colocarBarcos(Jugadores * jugador, numBarcos);
void colocarBarcoUsuario(Jugadores *jugador, Barco *barco);
int poderColocar(Jugadores *jugador, int fila, int col, int tamanoBarco, int orientacion);


#endif // COLOCAR_BARCOS_H

