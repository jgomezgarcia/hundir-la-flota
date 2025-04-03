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

//Precondición: tener inicializados los tableros y recibir el número de barcos para saber las iteraciones
//Cabecera: (char **) colocarBarcos (jugador* jug, int numBarcos)
//Postcondición: devuelve una matriz con los barcos colocados

char ** colocarBarcos(jugador *, barcos *, int);

//Precondición: tener inicializado los tableros
//Cabecera: void colocarBarcoUsuario(jugador *jug, barcos *barco)
//Postcondición: coloca el barco que sea necesario

void colocarBarcoUsuario(jugador *, barcos *);


//Precondición: Saber la posicion donde se quiere poner el barco, su tamaño y orientacion
//Cabecera: int poderColocar(jugador *, int fila, int columna , int tamanoBarco, int orientacion)
//Postcondición: Devuelve 0 si se puede colocar y 1 si no se puede

int poderColocar(jugador *, int , int , int , int );

//Precondicion: tener incializado el tablero, pasar el punto inicial y el tamañó del barco
//Cabecera: void marcarZonaSegura(jugador *jug, int fila, int col , int tamano, int orientacion)
//Postcondicion: devuelve el tablero por referencia con la zona segura marcada

void marcarZonaSegura(jugador *, int , int , int , int );


//Imprimir el tablero
void imprimirTablero(jugador *);


#endif // COLOCAR_BARCOS_H

