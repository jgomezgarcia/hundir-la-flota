#include <stdio.h>
#include <stdlib.h>
#include "configuracion.h"
#include "colocarFlota.h"


//Función para colocar barcos

//Precondición: tener inicializados los tableros y recibir el número de barcos para saber las iteraciones
//Cabecera: (char **) colocarBarcos (Jugadores*, int )
//Postcondición: devuelve una matriz con los barcos colocados

char **colocarBarcos(jugador *jug, Barcos *barcos, int numBarcos) {
    inicializarTablero(jug);
    printf("Tablero inicial:\n");
    imprimirTablero(jug);

    for (int i = 0; i < numBarcos; i++) {
        colocarBarcoUsuario(jug, &barcos[i]);
        printf("\nTablero después de colocar %s:\n", barcos[i].nombre);
        imprimirTablero(jug);
    }
    return jug->tablero;
}

//Función para colocar cada Barco

//Precondición: tener inicializado los tableros
//Cabecera: void colocarBarcoUsuario(Jugadores *, Barco *)
//Postcondición: coloca el barco que sea necesario

void colocarBarcoUsuario(jugador *jug, Barcos *barco) {
    	int fila, columna, orientacion;
    	int valido = 0;
    	do {
        	printf("\nIngrese la fila y columna inicial donde colocar el barco %s (tamano %d): ", barco->nombre, barco->tamano);
        	scanf("%d %d", &fila, &columna);

		printf("Ingrese la orientación \n(0 para horizontal hacia derecha\n1 para horizontal hacia inzquierda\n2 para vertical hacia abajo\n3 para vertical hacia arriba\n4 para diagonal derecha-abajo\n5 para diagonal derecha-arriba\n6 para diagonal izquierda-arriba\n7 para diagonal izquierda-abajo): ");
        	scanf("%d", &orientacion);

		valido = poderColocar(jug, fila, columna, barco->tamano, orientacion);
        	if (valido == 0) {
            		printf("Ubicacion invalida. Intente de nuevo.\n");
        	}
    	} while (valido == 0);

    	for (int i = 0; i < barco->tamano; i++) {
        	switch (orientacion){
			case 0: jug->tablero[fila][columna+i] = 'X'; break;
			case 1: jug->tablero[fila][columna-i] = 'X'; break;
			case 2: jug->tablero[fila+i][columna] = 'X'; break;
			case 3: jug->tablero[fila-i][columna] = 'X'; break;
			case 4: jug->tablero[fila+i][columna+i] = 'X'; break;
			case 5: jug->tablero[fila-i][columna+i] = 'X'; break;
			case 6: jug->tablero[fila-i][columna-i] = 'X'; break;
			case 7: jug->tablero[fila+i][columna-i] = 'X'; break;
		}
		marcarZonaSegura(jug,fila, columna, barco->tamano,orientacion);
    	}
}

//Función para saber si en esa posición se puede colocar

//Precondición: Saber la posicion donde se quiere poner el barco, su tamaño y orientacion
//Cabecera: int poderColocar(Jugadores *, int , int , int , int )
//Postcondición: Devuelve 0 si se puede colocar y 1 si no se puede

int poderColocar(jugador *jug, int fila, int columna, int tamanoBarco, int orientacion) {
    if (jug->tablero[fila][columna] == '*' || jug->tablero[fila][columna] == 'X')
        return 0;

    for (int i = 0; i < tamanoBarco; i++) {
        int nuevaFila = fila;
        int nuevaCol = columna;
        switch (orientacion) {
            case 0: nuevaCol = columna + i; break;
            case 1: nuevaCol = columna - i; break;
            case 2: nuevaFila = fila + i; break;
            case 3: nuevaFila = fila - i; break;
            case 4: nuevaFila = fila + i; nuevaCol = columna + i; break;
            case 5: nuevaFila = fila - i; nuevaCol = columna + i; break;
            case 6: nuevaFila = fila - i; nuevaCol = columna - i; break;
            case 7: nuevaFila = fila + i; nuevaCol = columna - i; break;
        }

        // Verificar límites del tablero
        if (nuevaFila < 0 || nuevaFila >= FILAS || nuevaCol < 0 || nuevaCol >= COLUMNAS)
            return 0;

        if (jug->tablero[nuevaFila][nuevaCol] == '*' ||
            jug->tablero[nuevaFila][nuevaCol] == 'X') {
            return 0;
        }
    }
    return 1; // Todas las posiciones son válidas
}


//Funcion para marcar la zona segura alrededor de X

//Precondicion: tener incializado el tablero, pasar el punto inicial y el tamañó del barco
//Cabecera: void marcarZonaSegura(jugadores *, int , int , int )
//Postcondicion: devuelve el tablero por referencia con la zona segura marcada

void marcarZonaSegura(jugador *jug, int fila, int col, int tamano, int orientacion) {
    for (int k = 0; k < tamano; k++) {  // Cambié 'i' por 'k' para evitar conflicto con el 'i' del bucle interno
        int nuevaFila = fila;
        int nuevaCol = col;

        switch (orientacion) {
            case 0: nuevaCol = col + k; break;
            case 1: nuevaCol = col - k; break;
            case 2: nuevaFila = fila + k; break;
            case 3: nuevaFila = fila - k; break;
            case 4: nuevaFila = fila + k; nuevaCol = col + k; break;
            case 5: nuevaFila = fila - k; nuevaCol = col + k; break;
            case 6: nuevaFila = fila - k; nuevaCol = col - k; break;
            case 7: nuevaFila = fila + k; nuevaCol = col - k; break;
        }

        // Marcar las 8 casillas alrededor de cada parte del barco
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int fSegura = nuevaFila + i;
                int cSegura = nuevaCol + j;

                // Verificar que estamos dentro de los límites del tablero
                if (fSegura >= 0 && fSegura < FILAS &&
                    cSegura >= 0 && cSegura < COLUMNAS &&
                    jug->tablero[fSegura][cSegura] != 'X') {  // Solo marcamos si no es parte del barco
                    jug->tablero[fSegura][cSegura] = '*';
                    }
            }
        }
    }
}

// Función para imprimir el tablero

void imprimirTablero(jugador *jug) {
    printf("\n   ");
    for (int j = 0; j < COLUMNAS; j++) {
        printf("%2d ", j); // Encabezado de columnas
    }
    printf("\n");

    for (int i = 0; i < FILAS; i++) {
        printf("%2d ", i); // Encabezado de filas
        for (int j = 0; j < COLUMNAS; j++) {
            printf("%2c ", jug->tablero[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

