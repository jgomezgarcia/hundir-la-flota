#ifndef DISPARO_AUTOMATICO_H_INCLUDED
#define DISPARO_AUTOMATICO_H_INCLUDED

#include "configuracion.h"
#include "resultado.h"
#include <stdlib.h>
#include <time.h>

void disparo_automatico(char **tablero_oponente,int tam_tablero, int *fila, int *columna, int *ultimo_fila, int *ultimo_columna, int *tocado, int *direccion_fila, int *direccion_columna, int *impactos);
void disparo_manual(int *fila,int *columa);


#endif // DISPARO_AUTOMATICO_H_INCLUDED

