#include <stdio.h>
#include <stdlib.h>
#include "configuracion.h"
#include "interfaces.h"

int main() {
    jugador *jugadores = NULL;
    barcos *barcosElegidos = NULL;
    int tam_tablero = 0, num_barcos = 0, tam_lista = 0;

    // Llamamos al menú principal pasando las direcciones de las variables
    menuPrincipal(&jugadores, &barcosElegidos, &tam_tablero, &num_barcos, &tam_lista, 0);

    // Liberar memoria al salir
    if (jugadores != NULL && barcosElegidos != NULL) {
        eliminarConfiguracion(barcosElegidos, jugadores, tam_tablero);
    }

    return 0;
}
