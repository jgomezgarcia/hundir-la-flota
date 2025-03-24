#ifndef __CONFIGURACION__H__
#define __CONFIGURACION__H__

#define CONFIG_BARCOS "./configurables/barcos.txt"

typedef struct{
  char Nom_Barco[21];
  char Id_Barco;
  int Tam_Barco;
}barcos;

typedef struct{
  int Id_Jugador;
  char Nom_Jugador[21];
  char Tipo_Disparo;  //Automático(A) y Manual(M)
  int Num_Disparos;
  int Ganador_Ronda;  //0 perderdor y 1 ganador
} jugador;

barcos * cargar_barcos(int *);
void listar_barcos(barcos *, int);

#endif // __CONFIGURACION__H__
