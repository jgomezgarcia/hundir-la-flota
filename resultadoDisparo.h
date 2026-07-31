#ifndef __RESULTADODISPARO__H__
#define __RESULTADODISPARO__H__

#include "configuracion.h"

typedef enum {TOCADO, HUNDIDO, AGUA, REPETIDO} resultado;

resultado resultadoDisparo(int, int, int, char **, char **);
void cambiarTurno(jugador *, int);

#endif // __RESULTADODISPARO__H__
