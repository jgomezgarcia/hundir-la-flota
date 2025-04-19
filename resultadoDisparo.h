#ifndef RESULTADOS_H
#define RESULTADOS_H


#include "configuracion.h"
#include "disparoAutomatico.h"
#include "interfaces.h"

int comprobar_resultados_disparo(jugador* defensor, int* fila, int* columna, int tam_tablero, int* tocado);
void gestionar_turnos (jugador *jug1,jugador *jug2, int tam_tablero, barcos *barcosElegidos, int tam_lista, int numBarcos);


#endif // RESULTADOS_H

