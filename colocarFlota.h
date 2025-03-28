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

//Precondici�n: tener inicializados los tableros y recibir el n�mero de barcos para saber las iteraciones
//Cabecera: (char **) colocarBarcos (jugador* jug, int numBarcos)
//Postcondici�n: devuelve una matriz con los barcos colocados

char ** colocarBarcos(jugador *, int);

//Precondici�n: tener inicializado los tableros
//Cabecera: void colocarBarcoUsuario(jugador *jug, barcos *barco)
//Postcondici�n: coloca el barco que sea necesario

void colocarBarcoUsuario(jugador *, barcos *);


//Precondici�n: Saber la posicion donde se quiere poner el barco, su tama�o y orientacion
//Cabecera: int poderColocar(jugador *, int fila, int columna , int tamanoBarco, int orientacion)
//Postcondici�n: Devuelve 0 si se puede colocar y 1 si no se puede

int poderColocar(jugador *, int , int , int , int );

//Precondicion: tener incializado el tablero, pasar el punto inicial y el tama�� del barco
//Cabecera: void marcarZonaSegura(jugador *jug, int fila, int col , int tamano, int orientacion)
//Postcondicion: devuelve el tablero por referencia con la zona segura marcada

void marcarZonaSegura(jugador *, int , int , int , int );





#endif // COLOCAR_BARCOS_H

