#include <stdio.h>
#include <stdlib.h>
#include "configuracion.h"
#include "colocarFlota.h"
#include <time.h>

static void colocarBarcoUsuario(jugador *, barcos *, int);
static int poderColocar(jugador *, int , int , int , int , int);
static void marcarZonaSegura(jugador *, int , int , int , int , int);

//Función para colocar barcos

//Precondición: tener inicializados los tableros y recibir el número de barcos para saber las iteraciones
//Cabecera: (char **) colocarBarcos (Jugadores*, int )
//Postcondición: devuelve una matriz con los barcos colocados

char ** colocarBarcos(jugador *jug, barcos *barcos, int numBarcos, int tam_tablero) {
    srand(time(NULL)); // Inicializar la semilla de aleatoriedad
    printf("=======TABLERO INICIAL=======\n");
    imprimirTableroFlota(jug->Tablero_flota, tam_tablero);

    int modo, respuesta, resultado;
    printf("Seleccione el modo de colocacion de barcos (1 = Manual, 2 = Automatico): ");
    scanf("%d", &modo);


        if (modo == 1) {
            for (int i = 0; i < numBarcos; i++){
                colocarBarcoUsuario(jug, &barcos[i], tam_tablero);
            printf("\nTablero despues de colocar %s:\n", barcos[i].Nom_Barco);
            imprimirTableroFlota(jug->Tablero_flota, tam_tablero);
            }
        } else {
        do {
            printf("\nColocando barcos automaticamente...\n");
            for (int i = 0; i < numBarcos; i++) {
                    colocarBarcoAutomatico(jug, barcos[i], tam_tablero);
            }

            printf("\n\n=======TABLERO GENERADO=======\n");
            imprimirTableroFlota(jug->Tablero_flota, tam_tablero);

            printf("\n¿Esta satisfecho con esta disposicion? (1 = Si, 0 = No): ");
            scanf("%d", &resultado);

            if (resultado != 1) {
                inicializarTableros(jug->Tablero_flota, jug->Tablero_oponente, tam_tablero);
                respuesta = 0;
                while (getchar() != '\n');
            } else respuesta = 1;

        } while (respuesta != 1);

    }
    printf("\n\n=======TABLERO FINAL=======\n");
    imprimirTableroFlota(jug->Tablero_flota, tam_tablero);

    //Ahora se transcribe el tablero para que se vean solo los barcos, es decir, la zona segura no se ve
    for (int j = 0; j < tam_tablero; j++) {
        for (int i = 0; i < tam_tablero; i++) {
                if(jug->Tablero_flota[i][j]=='*'){
                    jug->Tablero_flota[i][j]='-';
                }
        }
    }


    return jug->Tablero_flota;
}


//Función para colocar cada Barco

//Precondición: tener inicializado los tableros
//Cabecera: void colocarBarcoUsuario(Jugadores *, Barco *)
//Postcondición: coloca el barco que sea necesario

static void colocarBarcoUsuario(jugador *jug, barcos *barco, int tam_tablero) {
    	int fila, columna, orientacion;
    	int valido = 0;
    	do {
        	printf("\nIngrese la fila y columna inicial donde colocar el barco %s (tamano %d): ", barco->Nom_Barco, barco->Tam_Barco);
        	scanf("%d %d", &fila, &columna);

		printf("Ingrese la orientacion: \n0 para horizontal hacia derecha\n1 para horizontal hacia izquierda\n2 para vertical hacia abajo\n3 para vertical hacia arriba\n4 para diagonal derecha-abajo\n5 para diagonal derecha-arriba\n6 para diagonal izquierda-arriba\n7 para diagonal izquierda-abajo\nSu eleccion: ");
        	scanf("%d", &orientacion);

		valido = poderColocar(jug, fila, columna, barco->Tam_Barco, orientacion, tam_tablero);
        	if (valido == 0) {
            		printf("Ubicacion invalida. Intente de nuevo.\n");
        	}
    	} while (valido == 0);

    	for (int i = 0; i < barco->Tam_Barco; i++) {
        	switch (orientacion){
			case 0: jug->Tablero_flota[fila][columna+i] = 'X'; break;
			case 1: jug->Tablero_flota[fila][columna-i] = 'X'; break;
			case 2: jug->Tablero_flota[fila+i][columna] = 'X'; break;
			case 3: jug->Tablero_flota[fila-i][columna] = 'X'; break;
			case 4: jug->Tablero_flota[fila+i][columna+i] = 'X'; break;
			case 5: jug->Tablero_flota[fila-i][columna+i] = 'X'; break;
			case 6: jug->Tablero_flota[fila-i][columna-i] = 'X'; break;
			case 7: jug->Tablero_flota[fila+i][columna-i] = 'X'; break;
		}
		marcarZonaSegura(jug,fila, columna, barco->Tam_Barco,orientacion, tam_tablero);
    	}
}

//Función para saber si en esa posición se puede colocar

//Precondición: Saber la posicion donde se quiere poner el barco, su tamaño y orientacion
//Cabecera: int poderColocar(Jugadores *, int , int , int , int )
//Postcondición: Devuelve 0 si se puede colocar y 1 si no se puede

static int poderColocar(jugador *jug, int fila, int columna, int tamanoBarco, int orientacion, int tam_tablero) {
    if (jug->Tablero_flota[fila][columna] == '*' || jug->Tablero_flota[fila][columna] == 'X')
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
        if (nuevaFila < 0 || nuevaFila >= tam_tablero || nuevaCol < 0 || nuevaCol >= tam_tablero)
            return 0;

        if (jug->Tablero_flota[nuevaFila][nuevaCol] == '*' ||
            jug->Tablero_flota[nuevaFila][nuevaCol] == 'X') {
            return 0;
        }
    }
    return 1; // Todas las posiciones son válidas
}


//Funcion para marcar la zona segura alrededor de X

//Precondicion: tener incializado el tablero, pasar el punto inicial y el tamañó del barco
//Cabecera: void marcarZonaSegura(jugadores *, int , int , int )
//Postcondicion: devuelve el tablero por referencia con la zona segura marcada

static void marcarZonaSegura(jugador *jug, int fila, int col, int tamano, int orientacion, int tam_tablero) {
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
                if (fSegura >= 0 && fSegura < tam_tablero &&
                    cSegura >= 0 && cSegura < tam_tablero &&
                    jug->Tablero_flota[fSegura][cSegura] != 'X') {  // Solo marcamos si no es parte del barco
                    jug->Tablero_flota[fSegura][cSegura] = '*';
                    }
            }
        }
    }
}


void colocarBarcoAutomatico(jugador *jug, barcos barco, int tam_tablero) {
    int fila, col, orientacion;
    int colocado = 0;

    while (!colocado) {
        fila = rand() % tam_tablero;
        col = rand() % tam_tablero;
        orientacion = rand() % 8; // 8 direcciones posibles

        if (poderColocar(jug, fila, col, barco.Tam_Barco, orientacion, tam_tablero)) {
            for (int i = 0; i < barco.Tam_Barco; i++) {
                switch (orientacion) {
                    case 0: jug->Tablero_flota[fila][col + i] = 'X'; break; // Derecha
                    case 1: jug->Tablero_flota[fila][col - i] = 'X'; break; // Izquierda
                    case 2: jug->Tablero_flota[fila + i][col] = 'X'; break; // Abajo
                    case 3: jug->Tablero_flota[fila - i][col] = 'X'; break; // Arriba
                    case 4: jug->Tablero_flota[fila + i][col + i] = 'X'; break; // Diagonal derecha-abajo
                    case 5: jug->Tablero_flota[fila - i][col + i] = 'X'; break; // Diagonal derecha-arriba
                    case 6: jug->Tablero_flota[fila - i][col - i] = 'X'; break; // Diagonal izquierda-arriba
                    case 7: jug->Tablero_flota[fila + i][col - i] = 'X'; break; // Diagonal izquierda-abajo
                }
            }
            marcarZonaSegura(jug, fila, col, barco.Tam_Barco, orientacion, tam_tablero);
            colocado = 1;
        }
    }
}

