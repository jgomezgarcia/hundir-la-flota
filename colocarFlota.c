#include <stdio.h>
#include <stdlib.h>
#include "configuracion.h"
#include "colocarFlota.h"
#include <time.h>


//Precondición: tener inicializado los tableros
//Cabecera: void colocarBarcoUsuario(jugador *jug, barcos *barco)
//Postcondición: coloca el barco que sea necesario

void colocarBarcoUsuario(jugador *, Barcos *);


//Precondición: Saber la posicion donde se quiere poner el barco, su tamaño y orientacion
//Cabecera: int poderColocar(jugador *, int fila, int columna , int tamanoBarco, int orientacion)
//Postcondición: Devuelve 0 si se puede colocar y 1 si no se puede

int poderColocar(jugador *, int , int , int , int );

//Precondicion: tener incializado el tablero, pasar el punto inicial y el tamañó del barco
//Cabecera: void marcarZonaSegura(jugador *jug, int fila, int col , int tamano, int orientacion)
//Postcondicion: devuelve el tablero por referencia con la zona segura marcada

void marcarZonaSegura(jugador *, int , int , int , int );

//Precondición: saber que el jugador quiere colocarlo automaticamente, tener la estructura de barco
//Cabecera: void colocarBarcoAutomatico(Jugadores *jugador, Barco barco)
//Postcondicion: devuelve el puntero a la estructura habiendo cambiado el tablero por uno con los barcos colocados

void colocarBarcoAutomatico(jugador *, Barcos *);

void imprimirTablero(jugador *);

//Función para colocar barcos

//Precondición: tener inicializados los tableros y recibir el número de barcos para saber las iteraciones
//Cabecera: (char **) colocarBarcos (Jugadores*, int )
//Postcondición: devuelve una matriz con los barcos colocados

char ** colocarBarcos(jugador *jug, Barcos *barcos, int numBarcos) {
    srand(time(NULL)); // Inicializar la semilla de aleatoriedad
    inicializarTablero(jug);
    printf("=======TABLERO INICIAL=======\n");
    imprimirTablero(jug);

    int modo;
    printf("Seleccione el modo de colocacion de barcos (1 = Manual, 2 = Automatico): ");
    scanf("%d", &modo);


        if (modo == 1) {
            for (int i = 0; i < numBarcos; i++){
                colocarBarcoUsuario(jug, &barcos[i]);
            printf("\nTablero despues de colocar %s:\n", barcos[i].nombre);
            imprimirTablero(jug);
            }
        } else {
            int respuesta, resultado;
        do {
            printf("\nColocando barcos automaticamente...\n");
            inicializarTablero(jug);
            for (int i = 0; i < numBarcos; i++) {
                    colocarBarcoAutomatico(jug, &barcos[i]);
            }

            printf("\n\n=======TABLERO GENERADO=======\n");
            imprimirTablero(jug);

            printf("\n¿Esta satisfecho con esta disposicion? (1 = Si, 0 = No): ");
            scanf("%d", &resultado);

            if (resultado != 1) {
                respuesta = 0;
                while (getchar() != '\n');
            } else respuesta = 1;

        } while (respuesta != 1);

    }
    printf("\n\n=======TABLERO FINAL=======\n");
    imprimirTablero(jug);

    //Ahora se transcribe el tablero para que se vean solo los barcos, es decir, la zona segura no se ve
    for (int j = 0; j < COLUMNAS; j++) {
        for (int i = 0; i < FILAS; i++) {
                if(jug->tablero[i][j]=='*'){
                    jug->tablero[i][j]='.';
                }
                if(jug->tablero[i][j]=='A'){
                    jug->tablero[i][j]='.';
                }
        }
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

		printf("Ingrese la orientacion: \n0 para horizontal hacia derecha\n1 para horizontal hacia inzquierda\n2 para vertical hacia abajo\n3 para vertical hacia arriba\n4 para diagonal derecha-abajo\n5 para diagonal derecha-arriba\n6 para diagonal izquierda-arriba\n7 para diagonal izquierda-abajo\nSu eleccion: ");
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
    for (int k = 0; k < tamano; k++) {
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


void colocarBarcoAutomatico(jugador *jug, Barcos *barco) {
    int fila, col, orientacion;
    int colocado = 0;

    while (!colocado) {
        fila = rand() % FILAS;
        col = rand() % COLUMNAS;
        orientacion = rand() % 8; // 8 direcciones posibles

        if (poderColocar(jug, fila, col, barco->tamano, orientacion)) {
            for (int i = 0; i < barco->tamano; i++) {
                switch (orientacion) {
                    case 0: jug->tablero[fila][col + i] = 'X'; break; // Derecha
                    case 1: jug->tablero[fila][col - i] = 'X'; break; // Izquierda
                    case 2: jug->tablero[fila + i][col] = 'X'; break; // Abajo
                    case 3: jug->tablero[fila - i][col] = 'X'; break; // Arriba
                    case 4: jug->tablero[fila + i][col + i] = 'X'; break; // Diagonal derecha-abajo
                    case 5: jug->tablero[fila - i][col + i] = 'X'; break; // Diagonal derecha-arriba
                    case 6: jug->tablero[fila - i][col - i] = 'X'; break; // Diagonal izquierda-arriba
                    case 7: jug->tablero[fila + i][col - i] = 'X'; break; // Diagonal izquierda-abajo
                }
            }
            marcarZonaSegura(jug, fila, col, barco->tamano, orientacion);
            colocado = 1;
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


