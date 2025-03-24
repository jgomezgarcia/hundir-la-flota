#include <stdio.h>
#include <stdlib.h>
#include "configuracion.h"

int main()
{
    barcos *barcosMain;
    barcosMain = cargar_barcos();
    printf("Nom: %s, Id: %c, Tam: %d. \n", barcosMain[5].Nom_Barco, barcosMain[5].Id_Barco, barcosMain[5].Tam_Barco);
    return 0;
}
