#include <stdio.h>
#include <stdlib.h>
#include "posPartida.h"

//Precondición: recibir por referencia todas las variables y recibir un tablero ya inicializado con su tamaño correspondiente
//Poscondición: Devuelve la cantidad de veces que aparece repetida un mismo tipo de casilla
static void contarCasillas(int *vacias, int *agua, int *tocadas, int *hundidas, char **tableroOponente, int tam_tablero){
  for(int i = 0; i < tam_tablero; i++){
    for(int j = 0; j < tam_tablero, j++){
      switch(tableroOponente[i][j]){
        case '-':
          (*vacias)++;
        break;

        case 'A':
          (*agua)++;
        break;

        case 'T':
          (*tocadas)++;
        break;

        case 'H':
          (*hundidas)++;
        break;
      }
    }
  }
}

//Precondición: recibir la estructura jugadores ya inicializada con el tamaño de los tableros a jugar
void resumenPartida(jugador *jugadores, int tam_tablero) {

    int vacias1 = 0, agua1 = 0, tocadas1 = 0, hundidas1 = 0, vacias2 = 0, agua2 = 0, tocadas2 = 0, hundidas2 = 0;

    contarCasillas(&vacias1, &agua1, &tocadas1, &hundidas1, jugadores[0].Tablero_oponente, tam_tablero);  //Para el jugador 1
    contarCasillas(&vacias2, &agua2, &tocadas2, &hundidas2, jugadores[1].Tablero_oponente, tam_tablero);  //Para el jugador 2

    printf("|            |        Valor de las casillas             |         Barcos           |\n");
    printf("|------------|---------|-------|-----|--------|---------|---------|-------|--------|\n");
    printf("| Jugador    | Disparos| Vacías| Agua| Tocadas| Hundidas| Hundidos| Restan| Ganador|\n");
    printf("|------------|---------|-------|-----|--------|---------|---------|-------|--------|\n");
    printf("| Jugador1   |   %4d  |  %4d | %3d |   %4d |    %4d |    %4d |  %4d |    %1d   |\n",
           jugadores[0].numDisparos, vacias1, agua1, tocadas1, hundidas1, contar_hundidos_jugador(&jugadores[0], tam_tablero) , jugadores[1].Num_Barcos, jugadores[0].Ganador_Ronda);
    printf("| Jugador2   |   %4d  |  %4d | %3d |   %4d |    %4d |    %4d |  %4d |    %1d   |\n",
           disparos2, vacias2, agua2, tocadas2, hundidas2, contar_hundidos_jugador(&jugadores[1], tam_tablero) , jugadores[0].Num_Barcos,jugadores[1].Ganador_Ronda);

    for(int i = 0; i < MAX_JUGADORES; i++){ //Imprimimos los tableros para cada jugador
      printf("JUGADOR %d: ", i+1);
      imprimirTableroFlota(jugadores[i].Tablero_flota, tam_tablero);
      imprimirTableroOponente(jugadores[i].Tablero_oponente, tam_tablero);
      printf("\n");
    }
}
