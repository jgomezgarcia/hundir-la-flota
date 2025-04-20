#include "disparoAutomatico.h"
#include "configuracion.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void disparo_automatico(char **tablero_oponente, int tam_tablero,
                       int *fila, int *columna,
                       int *ultimo_fila, int *ultimo_columna,
                       int *tocado, int *direccion_fila, int *direccion_columna,
                       int *impactos, int intentos_adicionales[8]) {

    // Todas las direcciones posibles (4 cardinales + 4 diagonales)
    const int direcciones[8][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},   // N, S, O, E
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}  // NO, NE, SO, SE
    };

    // Si hay un barco tocado pero no hundido
    if (*tocado) {
        // Si ya tenemos una dirección definida
        if (*direccion_fila != 0 || *direccion_columna != 0) {
            int nueva_fila = *ultimo_fila + *direccion_fila;
            int nueva_columna = *ultimo_columna + *direccion_columna;

            // Verificar límites del tablero (la comprobación de '-' la hace otro módulo)
            if (nueva_fila >= 0 && nueva_fila < tam_tablero &&
                nueva_columna >= 0 && nueva_columna < tam_tablero) {

                *fila = nueva_fila;
                *columna = nueva_columna;
                return;
            }
            else {
                // Si está fuera del tablero, probar dirección opuesta
                *direccion_fila = -(*direccion_fila);
                *direccion_columna = -(*direccion_columna);

                nueva_fila = *ultimo_fila + *direccion_fila;
                nueva_columna = *ultimo_columna + *direccion_columna;

                if (nueva_fila >= 0 && nueva_fila < tam_tablero &&
                    nueva_columna >= 0 && nueva_columna < tam_tablero) {

                    *fila = nueva_fila;
                    *columna = nueva_columna;
                    return;
                }
            }
        }

        // Si no hay dirección definida o ambas direcciones fallaron
        // Probar todas las direcciones adyacentes no intentadas
        for (int i = 0; i < 8; i++) {
            if (intentos_adicionales[i] == 0) {
                int nueva_fila = *ultimo_fila + direcciones[i][0];
                int nueva_columna = *ultimo_columna + direcciones[i][1];

                if (nueva_fila >= 0 && nueva_fila < tam_tablero &&
                    nueva_columna >= 0 && nueva_columna < tam_tablero) {

                    *fila = nueva_fila;
                    *columna = nueva_columna;
                    intentos_adicionales[i] = 1;

                    // Establecer dirección si es el primer impacto adicional
                    if (*impactos == 1) {
                        *direccion_fila = direcciones[i][0];
                        *direccion_columna = direcciones[i][1];
                    }
                    return;
                }
                else {
                    intentos_adicionales[i] = 1;
                }
            }
        }

        // Si todas las direcciones fueron intentadas, resetear
        *tocado = 0;
        *direccion_fila = 0;
        *direccion_columna = 0;
        *impactos = 0;
        for (int i = 0; i < 8; i++) intentos_adicionales[i] = 0;
    }

    // Disparo aleatorio si no hay barcos tocados
    do {
        *fila = rand() % tam_tablero;
        *columna = rand() % tam_tablero;
    } while (0); // La comprobación de '-' la hace otro módulo
}


