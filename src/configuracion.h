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

void inicializarTableros(char **, char**, int);
barcos *barcosParaJugar(int *, int *, int*);
jugador * configurarJugador(int , int);
void imprimirTableroFlota(char **, int);
void imprimirTableroOponente(char **, int);
void mostrarConfiguracion(int , int , barcos *, jugador *);
void guardarPartida(barcos *, jugador *, int, int, int);
barcos * recuperarBarcos(int *, int *, int *);
jugador *recuperarJugadores(int , int , int );
void eliminarConfiguracion(barcos *, jugador *, int);
int contarBarcosHundidos(char **flotaOponente, char **oponente, int tam_tablero);
int contar_hundidos_jugador(jugador *, int);

#endif // __CONFIGURACION__H__
