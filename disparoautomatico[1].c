#include "disparo_automatico.h"

void disparo_automatico(char tablero_oponente[N][N], int *fila, int *columna, int *ultimo_fila, int *ultimo_columna, int *tocado) {
    if (*tocado) {
        int direcciones[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
        for (int i = 0; i < 8; i++) {
            int nueva_fila = *ultimo_fila + direcciones[i][0];
            int nueva_columna = *ultimo_columna + direcciones[i][1];
            if (nueva_fila >= 0 && nueva_fila < N && nueva_columna >= 0 && nueva_columna < N && tablero_oponente[nueva_fila][nueva_columna] == ' ') {
                *fila = nueva_fila;
                *columna = nueva_columna;
                return;
            }
        }
    }

    do {
        *fila = rand() % N;
        *columna = rand() % N;
    } while (tablero_oponente[*fila][*columna] != ' ');
}

/*
#include <time.h>

void disparo_automatico(char tablero[FILAS][COLUMNAS]){
    int fila, columna, direccion, disparo_acertado = 0;     
    int direcciones[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    srand(time(NULL));

    do {
        fila = rand() % FILAS;
        columna = rand() % COLUMNAS;
    } while (tablero[fila][columna] == TOCADO || tablero[fila][columna] == AGUA); 

    if(tablero[fila][columna] != BARCO)
        tablero[fila][columna] = AGUA
        
    else {

        tablero[fila][columna] = TOCADO
        for (int i = 0; i < 8; i++){
            int nueva_fila = fila + direcciones[i][0];
            int nueva_columna = columna + direcciones[i][1];

            if(nueva_fila >= 0 && nueva_fila < FILAS && nueva_columna >= 0 && nueva_columna < COLUMNAS && tablero[nueva_fila][nueva_columna] == BARCO)
                tablero[nueva_fila][nueva_columna] = TOCADO
            
            else {
                if (tablero[nueva_fila][nueva_columna] == ' ')
                    tablero[nueva_fila][nueva_columna] = AGUA
                
                return;
            }
        
        }
    }

}
*/