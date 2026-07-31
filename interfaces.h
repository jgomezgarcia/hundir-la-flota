#ifndef __INTERFACES_H__
#define __INTERFACES_H__

#include "configuracion.h"

void menuPrincipal(jugador **jugadores, barcos **barcosElegidos, int *tam_tablero, int *numBarcos, int *tam_lista);
void menuConfiguracion(jugador **jugadores, barcos **barcosElegidos, int *tam_tablero, int *numBarcos, int *tam_lista);
void menuPartida(jugador **jugadores, barcos **barcosElegidos, int tam_tablero, int numBarcos, int tam_lista);
void limpiarBuffer();
int obtenerOpcion(int, int);

#endif // __INTERFACES_H__
