#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "configuracion.h"

#define CONFIG_BARCOS "./configurables/barcos.txt"
#define PORCENTAJE_AGUA 0.6;


static void desglosarInfoBarcos(char *, barcos *);
static int validarNumBarcos(int , int);


//Precondición: recibir una cadena ya inicializada y recibe por referencia la estructura barco
static void desglosarInfoBarcos(char *cadDesglosar, barcos * barcosInfo){
  char *infoDesglosada;

  infoDesglosada = strtok(cadDesglosar, "-"); //Obtenemos el primer token con el nombre
  strcpy(barcosInfo->Nom_Barco, infoDesglosada);

  infoDesglosada = strtok(NULL, "-");       //Obtenemos el segundo con el id
  barcosInfo->Id_Barco = infoDesglosada[0];

  infoDesglosada = strtok(NULL, "-");         //Obtenemos el tercero con el tamaño
  barcosInfo->Tam_Barco = atoi(infoDesglosada);
}

static int validarNumBarcos(int tamBarcos, int tamTablero){
  int espacioTablero, aguaDisponible;
  float porcentajeAguaDisponible;

  espacioTablero = tamTablero*tamTablero;
  aguaDisponible = espacioTablero - tamBarcos;
  porcentajeAguaDisponible = (float)aguaDisponible/espacioTablero;

  if(porcentajeAguaDisponible < PORCENTAJE_AGUA){
    return 1;
  } else {
    return 0;
  }

}

//Poscondición: devuelve un puntero al tipo de dato barco
barcos *cargar_barcos(int *numBarcos){
    FILE * f;
    *numBarcos = 0;
    barcos *barcosAlmacenado;
    char cadenaLeida[50];
    f = fopen(CONFIG_BARCOS, "r");
    if(f == NULL){
        printf("No se pudo abrir el fichero. \n");
        exit(1);
    }

    while(!feof(f)){    //Lee el fichero y en función a las numBarcos reserva memoria para barcos
      fgets(cadenaLeida, 50, f);
      *numBarcos += 1;

      if(*numBarcos == 1){  //Crea en memoria la estructura
        barcosAlmacenado = (barcos *)malloc(*numBarcos * sizeof(barcos));
        if(barcosAlmacenado == NULL){
          printf("No se pudo reservar memoria. \n");
          exit(1);
        }

      } else {  //Reajusta el tamaño de la estructura
        barcosAlmacenado = (barcos *)realloc(barcosAlmacenado, *numBarcos * sizeof(barcos));

        if(f == NULL){
          printf("No se pudo reservar memoria. \n");
          exit(1);
        }

      }

      desglosarInfoBarcos(cadenaLeida, barcosAlmacenado + *numBarcos - 1); //Menos uno para respetar los indices en C

    }

    return barcosAlmacenado;

    free(barcosAlmacenado);
    fclose(f);
}

static char ** reservar_tablero(int tam_tablero){
  char **tablero;
  tablero = (char **)malloc(tam_tablero*sizeof(char*));
  for(int i = 0; i < tam_tablero; i++){
    tablero[i] = (char **)malloc(tam_tablero*sizeof(char));
  }

  return tablero;
}

//Poscondición: imprimir por pantalla los tipos de barcos disponibles
void listar_barcos(barcos *barcosMostrar, int numBarcos){
  char seguir;
  printf("\n --- BARCOS DISPONIBLES --- \n");
  printf("   \t Nombre \t Tam \t\n");
  for(int i = 0; i < numBarcos; i++){
    printf("%d: \t %s \t %d \t\n", i+1, barcosMostrar[i].Nom_Barco, barcosMostrar[i].Tam_Barco);
  }
  printf("---------------------------");
}

int configuracion_juego(jugador jugadores[MAX_JUGADORES], barcos *barcos_jugar, int *numBarcosJugar){
  int tamano_tableros;
  for(int i = 0; i < MAX_JUGADORES; i++){ //Configuración básica de cada jugador
    printf("Introduzca el nombre para el jugador %d: ", i+1);
    fgets((jugadores+i)->Nom_Jugador, 21, stdin);   //Nombre
    //cambio((jugadores+i)->Nom_Jugador);

    do{
      printf("Introduzca el tipo de disparo del jugador %d: ", i+1);
      fflush(stdin);
      scanf("%c", &((jugadores+i)->Tipo_Disparo));  //Toma el tipo de disparo

    }while((jugadores+i)->Tipo_Disparo != 'a' || (jugadores+i)->Tipo_Disparo != 'A' || (jugadores+i)->Tipo_Disparo != 'm' || (jugadores+i)->Tipo_Disparo != 'M');


      (jugadores+i)->Id_Jugador = i+1; //Asigna el id en función del jugador que es
    }

    printf("Introduzca el tamaño del tablero, tenga en cuenta que serán las mismas filas que columnas: ");
    scanf("%d", &tamano_tableros);

    for(int j = 0; j < MAX_JUGADORES; j++){ //Reserva de ambos tableros para cada jugador
      (jugadores+j)->Tablero_flota = reservar_tablero(tamano_tableros);
      (jugadores+j)->Tablero_oponente = reservar_tablero(tamano_tableros);
    }

    do{
      printf("Introduzca el tipo de barco mostrado: ");
      listar_barcos();
    }while(char seguir == 'S' || char seguir == 's');

    return 1;
}

