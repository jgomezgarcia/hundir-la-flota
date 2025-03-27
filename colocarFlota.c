#include <stdio.h>
#include <stdlib.h>
#include "configuracion.h"
#include "colocarFlota.h"


//Función para colocar barcos//
************************************
//Precondición: tener inicializados los tableros y recibir el número de barcos para saber las iteraciones
//Cabecera: (char **) colocarBarcos (Jugadores*, int )
//Postcondición: devuelve una matriz con los barcos colocados

char ** colocarBarcos(Jugadores * jugador, numBarcos){
	inicializarTablero(jugador);
    	for (int i = 0; i < numBarcos; i++) {
        	colocarBarcoUsuario(jugador, barcos[i]);
    	}

    	return (char **)jugador->tablero;
}

//Función para colocar cada Barco//
***********************************
//Precondición: tener inicializado los tableros
//Cabecera: void colocarBarcoUsuario(Jugadores *)
//Postcondición: coloca el barco que sea necesario

void colocarBarcoUsuario(Jugadores *jugador, Barco *barco) {
    	int fila, col, orientacion;
    	int valido = 0;
    	do {
        	printf("\nIngrese la fila y columna inicial donde colocar el barco %s (tamano %d): ", barco.nombre, barco.tamano);
        	scanf("%d %d", &fila, &col);

		printf("Ingrese la orientación (0 para horizontal hacia derecha, 1 para horizontal hacia inzquierda, 2 para vertical hacia abajo, 3 para vertical hacia arriba, 4 para diagonal derecha-abajo, 5 para diagonal derecha-arriba, 6 para diagonal izquierda-arriba, 7 para diagonal izquierda-abajo): ");
        	scanf("%d", &orientacion);

		valido = poderColocar(jugador, fila, col, barco.tamano, orientacion);
        	if (valido == 0) {
            		printf("Ubicación inválida. Recuerde dejar un espacio entre barcos. Intente de nuevo.\n");
        	}
    	} while (valido == 0);

    	for (int i = 0; i < barco.tamano; i++) {
        	switch (orientacion){
			case 0: jugador->tablero[fila][columna+i] = 'X';
				if (fila >= 0 && fila < MAX_FILAS && columna >= 0 && columna < MAX_COLUMNAS && (jugador->tablero[fila][columna+i] == 'A'||jugador->tablero[fila]				[columna+i] == '*')) {
                			jugador->tablero[fila][columna+i] = '*';
            				}
				break;
			case 1: jugador->tablero[fila][columna-i] = 'X';
				if (fila >= 0 && fila < MAX_FILAS && columna >= 0 && columna < MAX_COLUMNAS && (jugador->tablero[fila][columna-i] == 'A'||jugador->tablero[fila]				[columna-i] == '*')) {
                			jugador->tablero[fila][columna-i] = '*';
            				}
				break;
			case 2: jugador->tablero[fila+i][columna] = 'X';
				if (fila >= 0 && fila < MAX_FILAS && columna >= 0 && columna < MAX_COLUMNAS && (jugador->tablero[fila+i][columna] == 'A'||jugador->						tablero[fila+i][columna] == '*')) {
                			jugador->tablero[fila+i][columna] = '*';
            				}
				break;
			case 3: jugador->tablero[fila-i][columna] = 'X';
				if (fila >= 0 && fila < MAX_FILAS && columna >= 0 && columna < MAX_COLUMNAS && (jugador->tablero[fila-i][columna] == 'A'||jugador->tablero[fila-				i][columna] == '*')) {
                			jugador->tablero[fila-i][columna] = '*';
            				}
				break;
			case 4: jugador->tablero[fila+i][columna+i] = 'X';
				if (fila >= 0 && fila < MAX_FILAS && columna >= 0 && columna < MAX_COLUMNAS && (jugador->tablero[fila+i][columna+i] == 'A'||jugador->						tablero[fila+i][columna+i] == '*')) {
                			jugador->tablero[fila+i][columna+i] = '*';
            				}
				break;
			case 5: jugador->tablero[fila-i][columna+i] = 'X';
				if (fila >= 0 && fila < MAX_FILAS && columna >= 0 && columna < MAX_COLUMNAS && (jugador->tablero[fila-i][columna+i] == 'A'||jugador->						tablero[fila-i][columna+i] == '*')) {
                			jugador->tablero[fila-i][columna+i] = '*';
            				}

				break;
			case 6: jugador->tablero[fila-i][columna-i] = 'X';
				if (fila >= 0 && fila < MAX_FILAS && columna >= 0 && columna < MAX_COLUMNAS && (jugador->tablero[fila-i][columna-i] == 'A'||jugador->						tablero[fila-i][columna-i] == '*')) {
                			jugador->tablero[fila-i][columna-i] = '*';
            				}
				break;
			case 7: jugador->tablero[fila+i][columna-i] = 'X';
				if (fila >= 0 && fila < MAX_FILAS && columna >= 0 && columna < MAX_COLUMNAS && (jugador->tablero[fila+i][columna-i] == 'A'||jugador->						tablero[fila+i][columna-i] == '*')) {
                			jugador->tablero[fila][columna+i] = '*';
            				}
				break;
		}
    	}

//Función para saber si en esa posición se puede colocar//
********************************************************
//Precondición: Saber la posicion donde se quiere poner el barco, su tamaño y orientacion
//Cabecera: int poderColocar(Jugadores *, int , int , int , int )
//Postcondición: Devuelve 0 si se puede colocar y 1 si no se puede

int poderColocar(Jugadores *jugador, int fila, int col, int tamanoBarco, int orientacion){
	if (jugador->tablero[fila][col] != 'A' || jugador->tablero[fila][col] != '*') return 0;
	for (int i = 0; i < barco.tamano; i++){
		switch (orientacion){
			case 0: if(jugador->tablero[fila][columna+i] != '*'||jugador->tablero[fila][columna+i]!='A'){
					return 0;
				}
				break;
			case 1: if(jugador->tablero[fila][columna-i] != '*'||jugador->tablero[fila][columna-i] != 'A'){
					return 0;
				}
				break;
			case 2: if(jugador->tablero[fila+i][columna] != '*'||jugador->tablero[fila+i][columna] != 'A'){
					return 0;
				}
				break;
			case 3: if(jugador->tablero[fila-i][columna] = '*'||jugador->tablero[fila-i][columna] = 'A'){
					return 0;
				}
				break;
			case 4: if(jugador->tablero[fila+i][columna+i] != '*'||jugador->tablero[fila+i][columna+i] != 'A'){
					return 0;
				}
				break;
			case 5: if(jugador->tablero[fila-i][columna+i] != '*'||jugador->tablero[fila-i][columna+i] != '*'){
					return 0;
				}
				break;
			case 6: if(jugador->tablero[fila-i][columna-i] != '*'||jugador->tablero[fila-i][columna-i] != 'A'){
					return 0;
				}
				break;
			case 7: if(jugador->tablero[fila+i][columna-i] != '*'||jugador->tablero[fila+i][columna-i] != 'A'){
					return 0;
				}
				break;
		}
	}
}




