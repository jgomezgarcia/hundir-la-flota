#ifndef COLOCAR_BARCOS_H
#define COLOCAR_BARCOS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"

typedef struct {
    char **tablero;
    int filas;
    int columnas;
} Tablero;

//Precondición: tener inicializados los tableros y recibir el número de barcos para saber las iteraciones
//Cabecera: (char **) colocarBarcos (jugador* jug, int numBarcos)
//Postcondición: devuelve una matriz con los barcos colocados

char ** colocarBarcos(jugador *,Barcos *, int);



#endif // COLOCAR_BARCOS_H
