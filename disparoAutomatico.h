#ifndef __disparoAutomatico__H__
#define __disparoAutomatico__H__

#include "resultadoDisparo.h"
typedef enum{ALEATORIO, ALREDEDOR, DIRECCION} estado;
void disparoAutomatico(
    char **tablero_oponente,
    char **tablero_flota,
    int tam_tablero,
    int *fila, int *columna,
    int *ultima_fila, int *ultima_columna,
    int *numTocado,
    estado *estadoDisparoAnterior,
    int *ultima_direccionX, int *ultima_direccionY,
    resultado *resultadoDisparo
);

#endif // __disparoAutomatico__H__
