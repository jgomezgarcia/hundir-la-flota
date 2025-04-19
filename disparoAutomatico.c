#include "disparo_automatico.h"
#include <time.h>

void disparo_automatico(char **tablero_oponente, int tam_tablero, int *fila, int *columna, int *ultimo_fila, int *ultimo_columna, int *tocado, int *direccion_fila, int *direccion_columna, int *impactos) {
      srand(time(NULL));

    if (*tocado == 1 ) {
        if (*direccion_fila == 0 && *direccion_columna == 0) { // Si no hay dirección definida
            int direcciones[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
            for (int i = 0; i < 8; i++) {
                int nueva_fila = *ultimo_fila + direcciones[i][0];
                int nueva_columna = *ultimo_columna + direcciones[i][1];
                if (nueva_fila >= 0 && nueva_fila < tam_tablero && nueva_columna >= 0 && nueva_columna < tam_tablero && tablero_oponente[nueva_fila][nueva_columna] == ' ') {
                    *fila = nueva_fila;
                    *columna = nueva_columna;
                    *direccion_fila = direcciones[i][0]; // Guarda la dirección
                    *direccion_columna = direcciones[i][1];
                    *impactos = 1;
                    return;
                }
            }
        } else { // Si ya hay dirección definida, continuar en la misma
            int nueva_fila = *ultimo_fila + *direccion_fila;
            int nueva_columna = *ultimo_columna + *direccion_columna;
            if (nueva_fila >= 0 && nueva_fila < tam_tablero && nueva_columna >= 0 && nueva_columna < tam_tablero && tablero_oponente[nueva_fila][nueva_columna] == ' ') {
                *fila = nueva_fila;
                *columna = nueva_columna;
                (*impactos)++;
                return;
            } else { // Si el tercer disparo falla, disparar en la dirección contraria
                if (*impactos >= 2) {
                    *direccion_fila = -(*direccion_fila);
                    *direccion_columna = -(*direccion_columna);
                    *fila = *ultimo_fila + *direccion_fila;
                    *columna = *ultimo_columna + *direccion_columna;
                    *impactos = 0;
                    return;
                } else { // Si choca sin haber impactado dos veces seguidas, reiniciar dirección
                    *direccion_fila = 0;
                    *direccion_columna = 0;
                    *impactos = 0;
                }
            }
        }
    }

    // Disparo aleatorio si no hay impacto previo o si se reseteó la dirección
    do {
        *fila = rand() % tam_tablero;
        *columna = rand() % tam_tablero;
    } while (tablero_oponente[*fila][*columna] != '-');
}

}

void disparo_manual(int *fila,int *columa){
    printf("Introduce la fila y la columna del disparo: ");
    scanf("%d %d", fila, columna);
    //enviar el disparo para que lo compruebe el otro modulo
    }


