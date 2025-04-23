#include <stdlib.h>
#include <stdbool.h>
#include "configuracion.h"
void disparo_automatico(char **tablero_oponente, int tam_tablero,
                       int *fila, int *columna,
                       int *ultimo_fila, int *ultimo_columna,
                       int *tocado, int *direccion_fila, int *direccion_columna,
                       int *impactos, int intentos_adicionales[8]) {

    const int direcciones[8][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},    // N, S, O, E
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}   // NO, NE, SO, SE
    };

    static int direcciones_ordenadas[8];
    static bool orden_inicializado = false;

    // Si estamos persiguiendo un barco
    if (*tocado) {
        if (*direccion_fila != 0 || *direccion_columna != 0) {
            // Continuar en la misma dirección
            int nueva_fila = *ultimo_fila + *direccion_fila;
            int nueva_columna = *ultimo_columna + *direccion_columna;

            if (nueva_fila >= 0 && nueva_fila < tam_tablero &&
                nueva_columna >= 0 && nueva_columna < tam_tablero &&
                tablero_oponente[nueva_fila][nueva_columna] == '-') {

                *fila = nueva_fila;
                *columna = nueva_columna;
                *ultimo_fila = nueva_fila;
                *ultimo_columna = nueva_columna;
                return;
            } else {
                // Probar la dirección opuesta
                *direccion_fila = -(*direccion_fila);
                *direccion_columna = -(*direccion_columna);
                *ultimo_fila = *ultimo_fila - *direccion_fila;
                *ultimo_columna = *ultimo_columna - *direccion_columna;

                int nueva_fila = *ultimo_fila + *direccion_fila;
                int nueva_columna = *ultimo_columna + *direccion_columna;

                if (nueva_fila >= 0 && nueva_fila < tam_tablero &&
                    nueva_columna >= 0 && nueva_columna < tam_tablero &&
                    tablero_oponente[nueva_fila][nueva_columna] == '-') {

                    *fila = nueva_fila;
                    *columna = nueva_columna;
                    *ultimo_fila = nueva_fila;
                    *ultimo_columna = nueva_columna;
                    return;
                }

                // Si también falla, reiniciar seguimiento
                *direccion_fila = 0;
                *direccion_columna = 0;
                *impactos = 0;
                for (int i = 0; i < 8; i++) intentos_adicionales[i] = 0;
                orden_inicializado = false;
            }
        }

        // Si no tenemos una dirección definida
        if (!orden_inicializado) {
            for (int i = 0; i < 8; i++) direcciones_ordenadas[i] = i;

            // Mezclar aleatoriamente (Fisher-Yates)
            for (int i = 7; i > 0; i--) {
                int j = rand() % (i + 1);
                int temp = direcciones_ordenadas[i];
                direcciones_ordenadas[i] = direcciones_ordenadas[j];
                direcciones_ordenadas[j] = temp;
            }

            orden_inicializado = true;
        }

        // Probar direcciones aleatorias adyacentes
        for (int i = 0; i < 8; i++) {
            int dir_idx = direcciones_ordenadas[i];

            if (intentos_adicionales[dir_idx] == 0) {
                int nueva_fila = *ultimo_fila + direcciones[dir_idx][0];
                int nueva_columna = *ultimo_columna + direcciones[dir_idx][1];

                intentos_adicionales[dir_idx] = 1;

                if (nueva_fila >= 0 && nueva_fila < tam_tablero &&
                    nueva_columna >= 0 && nueva_columna < tam_tablero &&
                    tablero_oponente[nueva_fila][nueva_columna] == '-') {

                    *fila = nueva_fila;
                    *columna = nueva_columna;

                    *direccion_fila = direcciones[dir_idx][0];
                    *direccion_columna = direcciones[dir_idx][1];
                    *impactos += 1;
                    *ultimo_fila = nueva_fila;
                    *ultimo_columna = nueva_columna;

                    return;
                }
            }
        }

        // Si agotamos todas las direcciones
        *tocado = 0;
        *direccion_fila = 0;
        *direccion_columna = 0;
        *impactos = 0;
        orden_inicializado = false;
        for (int i = 0; i < 8; i++) intentos_adicionales[i] = 0;
    }

    // Si no se está siguiendo ningún barco
    do {
        *fila = rand() % tam_tablero;
        *columna = rand() % tam_tablero;
    } while (tablero_oponente[*fila][*columna] != '-');
}

