#ifndef __CONFIGURACION__H__
#define __CONFIGURACION__H__

#define MAX_JUGADORES 2
#define LONGITUD_NOMBRE 21

typedef struct{
  char Nom_Barco[LONGITUD_NOMBRE];
  char Id_Barco;
  int Tam_Barco;
}barcos;

typedef enum {PERDEDOR, GANADOR}ganador;

typedef struct{
  int Id_Jugador;
  char Nom_Jugador[LONGITUD_NOMBRE];
  char Tipo_Disparo;  //Automático(A) y Manual(M)
  int Num_Disparos;
  int Num_Barcos;
  ganador Ganador_Ronda;
  int turno; //0 no turno y 1 si turno
  char **Tablero_flota;
  char **Tablero_oponente;
} jugador;

barcos *barcosParaJugar(int );
jugador * configurarJugador(int , int);
int validarNumBarcos(int , int );
void imprimirTableros(jugador, int);
void imprimirConfiguracion(int, int, char, char, jugador *);

#endif // __CONFIGURACION__H__
