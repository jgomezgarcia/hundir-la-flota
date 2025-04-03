#ifndef DISPARO_AUTOMATICO_H_INCLUDED
#define DISPARO_AUTOMATICO_H_INCLUDED

#include "tablero.h"
#include "jugador.h"
#include <stdlib.h>

void disparo_automatico(char tablero_oponente[N][N], int *fila, int *columna, int *ultimo_fila, int *ultimo_columna, int *tocado, int *direccion_fila, int *direccion_columna, int *impactos);
void disparo_manual(Jugador *jugador, Jugador *oponente);


#endif // DISPARO_AUTOMATICO_H_INCLUDED
