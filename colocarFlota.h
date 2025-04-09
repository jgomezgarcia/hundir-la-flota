#ifndef COLOCAR_BARCOS_H
#define COLOCAR_BARCOS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "configuracion.h"

//Precondición: tener inicializados los tableros y recibir el número de barcos para saber las iteraciones
//Cabecera: (char **) colocarBarcos (jugador* jug, int numBarcos)
//Postcondición: devuelve una matriz con los barcos colocados
char ** colocarBarcos(jugador *,barcos *, int, int);

//Precondición: jugador no nulo, una estructura de barcos y tener el tamañó del tablero definido
//Cabecera: void colocarBarcoAutomatico(jugador *jug, barcos barco, int tam_tablero)
//Postcondición: devuelve colocados los barcos para el jugador máquina en su estructura, NO DEVUELVE NINGUN TABLERO
void colocarBarcoAutomatico(jugador *, barcos, int);

#endif // COLOCAR_BARCOS_H
