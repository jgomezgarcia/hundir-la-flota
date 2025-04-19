#ifndef DISPARO_AUTOMATICO_H
#define DISPARO_AUTOMATICO_H

#include "configuracion.h"
#include "resultadoDisparo.h"
#include <stdlib.h>
#include <time.h>

void disparo_automatico(char **tablero_oponente,int tam_tablero, int *fila, int *columna, int *ultimo_fila, int *ultimo_columna, int *tocado, int *direccion_fila, int *direccion_columna, int *impactos);


#endif // DISPARO_AUTOMATICO_H

