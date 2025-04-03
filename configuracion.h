#ifndef __CONFIGURACION__H__
#define __CONFIGURACION__H__

#define MAX_JUGADORES 2

typedef struct{
  char Nom_Barco[21];
  char Id_Barco;
  int Tam_Barco;
}barcos;

typedef enum {PERDEDOR, GANADOR}ganador;

typedef struct{
  int Id_Jugador;
  char Nom_Jugador[21];
  char Tipo_Disparo;  //Automático(A) y Manual(M)
  int Num_Disparos;
  ganador Ganador_Ronda;
  int turno; //0 no turno y 1 si turno
  char **Tablero_flota;
  char **Tablero_oponente;
} jugador;

barcos * cargar_barcos(int *);
void listar_barcos(barcos *, int);
int configuracion_juego(jugador *, barcos *, int *);

#endif // __CONFIGURACION__H__

