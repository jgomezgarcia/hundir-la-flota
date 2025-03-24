#ifndef __CONFIGURACION__H__
#define __CONFIGURACION__H__

#define CONFIG_BARCOS "./configurables/barcos.txt"

typedef struct{
  char Nom_Barco[21];
  char Id_Barco;
  int Tam_Barco;
}barcos;

barcos * cargar_barcos();

#endif // __CONFIGURACION__H__
