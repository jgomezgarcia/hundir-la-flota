#ifndef DISPARO_AUTOMATICO_H
#define DISPARO_AUTOMATICO_H

#include "configuracion.h"
#include "resultadoDisparo.h"
#include <stdlib.h>
#include <time.h>


void disparo_automatico(
    char **tablero_oponente,
    int tam_tablero,
    int *fila,
    int *columna,
    int *ultimo_fila,
    int *ultimo_columna,
    int *tocado,
    int *direccion_fila,
    int *direccion_columna,
    int *impactos,
    int intentos_adicionales[8]  // Array de control para saber qué direcciones ya fueron probadas
);

#endif
