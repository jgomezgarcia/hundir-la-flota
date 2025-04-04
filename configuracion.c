#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "configuracion.h"

#define CONFIG_BARCOS "./configurables/barcos.txt"
#define PORCENTAJE_AGUA 0.6


static void desglosarInfoBarcos(char *, barcos *);
static int numLineasFichero(FILE *);
static barcos *leerBarcos(int *);
static void listarBarcos(int , barcos *);
static int indicePorIdBarco(char , barcos *, int );
static char ** reservar_tablero(int );
static void eliminarSalto(char *, int);
static void inicializarTableros(char **, char**, int );


//Precondición: recibir una cadena ya inicializada y recibe por referencia la estructura barco
static void desglosarInfoBarcos(char *cadDesglosar, barcos *barcosInfo){
  char *infoDesglosada;

  infoDesglosada = strtok(cadDesglosar, "-"); //Obtenemos el primer token con el nombre
  strcpy(barcosInfo->Nom_Barco, infoDesglosada);

  infoDesglosada = strtok(NULL, "-");       //Obtenemos el segundo con el id
  barcosInfo->Id_Barco = infoDesglosada[0];

  infoDesglosada = strtok(NULL, "-");         //Obtenemos el tercero con el tamaño
  barcosInfo->Tam_Barco = atoi(infoDesglosada);
}

//Precondición: recibir un fichero ya abierto
//Poscondición: devolver el número de lineas del fichero
static int numLineasFichero(FILE *ficheroContar){
  char bufferTemporal[40];
  int numLineas = 0;
  while(!feof(ficheroContar)){
    fgets(bufferTemporal, 40, ficheroContar);
    numLineas++;
  }

  rewind(ficheroContar);
  return numLineas;
}

static char ** reservar_tablero(int tam_Tablero){
  char **tablero;
  tablero = (char **)malloc(tam_Tablero*sizeof(char *));
  for(int i = 0; i < tam_Tablero; i++){
    tablero[i] = (char *)malloc(tam_Tablero * sizeof(char));
  }

  return tablero;
}

static barcos *leerBarcos(int *nBarcosDisponibles){
  barcos *barcosDisponibles;
  FILE *fBarcos;
  int indexBarcosDisponibles = 0;
  char infoBarcos[50];  //Informacion a desglosar

  fBarcos = fopen(CONFIG_BARCOS, "r");

  if(fBarcos == NULL){
    printf("No se pudo abrir el fichero de configuración de barcos. \n");
    exit(1);
  }

  *nBarcosDisponibles = numLineasFichero(fBarcos);

  barcosDisponibles = (barcos *)malloc(*nBarcosDisponibles * sizeof(barcos));
  if(barcosDisponibles == NULL){
    printf("No se pudo reservar memoria para los barcos jugables. \n");
    exit(1);
  }

  while(!feof(fBarcos)){
    fgets(infoBarcos, 50, fBarcos);
    desglosarInfoBarcos(infoBarcos, barcosDisponibles+indexBarcosDisponibles);
    indexBarcosDisponibles++;
  }

  fclose(fBarcos);
  return barcosDisponibles;
}

static void listarBarcos(int nBarcos, barcos *barcosListados){
  printf("---BARCOS JUGABLES---\n");
  printf("Nombre \t\t ID \t\t Tam");
  for(int i = 0; i < nBarcos; i++){
    printf("\n%s \t %c \t\t %d", barcosListados[i].Nom_Barco, barcosListados[i].Id_Barco, barcosListados[i].Tam_Barco);
  }
}

static int indicePorIdBarco(char id, barcos *barcosDisponibles, int nBarcosDisponibles){
  for(int i = 0; i < nBarcosDisponibles; i++){
    if(barcosDisponibles[i].Id_Barco == id){
      return i;
    }
  }

  return -1;
}

static void eliminarSalto(char *aux, int tamano){
  for(int i = 0; i < tamano; i++){
    if(aux[i] == '\n'){
      aux[i] = '\0';
    }
  }
}

static void inicializarTableros(char **flota, char**oponente, int tam_tablero){
  for(int i = 0; i < tam_tablero; i++){
    for(int j = 0; j < tam_tablero; j++){
      flota[i][j] = '-';
      oponente[i][j] = '-';
    }
  }
}

/*  FUNCIONES PUBLICAS  */

barcos *barcosParaJugar(int nBarcosJugar){
    int sumaBarcosIntroducidos = 0, indiceBarcoElegido = 0, indicePorId, cantBarcosTipo, nBarcosDisponibles;
    char tipoBarco;

    barcos *barcosDisponibles, *barcosJugar;
    barcosDisponibles = leerBarcos(&nBarcosDisponibles); //Carga los barcos jugables almacenado en barcos.txt

    barcosJugar = (barcos *)malloc(nBarcosJugar*sizeof(barcos));
    if(barcosJugar == NULL){
      printf("No se pudo reservar memoria para los barcos seleccionados. \n");
      exit(1);
    }

    listarBarcos(nBarcosDisponibles, barcosDisponibles);

    do{

      fflush(stdin);
      printf("\nQue tipo de barco quiere usar introduzca el id: ");
      scanf("%c", &tipoBarco);
      indicePorId = indicePorIdBarco(tipoBarco, barcosDisponibles, nBarcosDisponibles);

      if(indicePorId != -1){ //Si encuentra el id pide al usuario la cantidad que desea
        printf("Introduzca el número de barcos del tipo %c", tipoBarco);
        scanf("%d", &cantBarcosTipo);
        sumaBarcosIntroducidos += cantBarcosTipo;

        if(nBarcosJugar - sumaBarcosIntroducidos >= 0){   //Se encarga de controlar que no se supere el numero de barcos
          for(int j = 0; j < cantBarcosTipo; j++){       //Va guardando segun la cantidad de barcos
            strcpy(barcosJugar[indiceBarcoElegido].Nom_Barco, barcosDisponibles[indicePorId].Nom_Barco);
            barcosJugar[indiceBarcoElegido].Id_Barco = barcosDisponibles[indicePorId].Id_Barco;
            barcosJugar[indiceBarcoElegido].Tam_Barco = barcosDisponibles[indicePorId].Tam_Barco;
            indiceBarcoElegido++;
          }
        } else {
          printf("Cantidad de barcos errónea pruebe con una menor");
          sumaBarcosIntroducidos -= cantBarcosTipo; //Sino es valida la cantidad elimina la cantidad sumada
        }
      } else {
        printf("Id de barco inválido introduzca otro. \n");
      }

    }while(sumaBarcosIntroducidos < nBarcosJugar);

    free(barcosDisponibles);
    return barcosJugar;
}

jugador *configurarJugador(int tam_tablero, int nBarcos){
  jugador *jugadorConfigurar;

  jugadorConfigurar = (jugador *)malloc(MAX_JUGADORES * sizeof(jugador));

  char tipoDisparo, tipoTurno;
  int turno;
  srand(time(NULL));

  for(int i = 0; i < MAX_JUGADORES; i++){
    printf("Introduzca el nombre para el jugador %d: ", i+1);
    fgets(jugadorConfigurar[i].Nom_Jugador, LONGITUD_NOMBRE, stdin);
    eliminarSalto(jugadorConfigurar[i].Nom_Jugador, LONGITUD_NOMBRE);

    do{
      printf("Introduzca el tipo de disparo para el jugador %s, Automático(A) o Manual(M)", jugadorConfigurar[i].Nom_Jugador);
      scanf("%c", &tipoDisparo);
      tipoDisparo = toupper(tipoDisparo);
      fflush(stdin);
    } while(tipoDisparo != 'A' && tipoDisparo != 'M');  //Controla que el usuario no introduzca datos inválidos

    jugadorConfigurar[i].Tipo_Disparo = tipoDisparo;  //Una vez comprobado almacena


    jugadorConfigurar[i].turno = 0; //Inicializamos todos los turnos a cero para luego modifcarlos
    jugadorConfigurar[i].Id_Jugador = i;    //Id según la posición del jugadors
    jugadorConfigurar[i].Tablero_flota = reservar_tablero(tam_tablero);   //Reserva para ambos tableros
    jugadorConfigurar[i].Tablero_oponente = reservar_tablero(tam_tablero);
    inicializarTableros(jugadorConfigurar[i].Tablero_flota, jugadorConfigurar[i].Tablero_oponente, tam_tablero); //Tras su reserva se inicializan
    jugadorConfigurar[i].Num_Barcos = nBarcos;    //Número de barcos que van a jugarse en la partida
  }

  do{
      printf("Quiere asignar el turno(S/N): ");
      scanf("%c", &tipoTurno);
      tipoTurno = toupper(tipoTurno);
      fflush(stdin);
  } while(tipoTurno != 'S' && tipoTurno != 'N');  //Controla caracteres inválidos

  if(tipoTurno == 'S'){
    do{
      printf("Que jugador comenzará la partida: ");
      scanf("%d", &turno);
      jugadorConfigurar[turno-1].turno = 1; //Aquel jugador elegido se el asigna turno 1
    }while(turno > 2 || turno <= 0);
  } else {
    printf("Turno asignado automáticamente. \n");
    turno = rand() % 2;   //Devuelve un indice aleatorio
    jugadorConfigurar[turno].turno = 1;
  }

  return jugadorConfigurar;
}

//Precondición: recibir una cadena ya inicializada y recibe por referencia la estructura barco
//Poscondición: devuelve 1 si es valido y 0 sino lo es

int validarNumBarcos(int tamBarcos, int tamTablero){
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

void imprimirTableros(jugador tableroJugador, int tam_tableros){
  printf("TABLERO FLOTA\n");
    printf("\n   ");
    for (int j = 0; j < tam_tableros; j++) {
        printf("%2d ", j); // Encabezado de columnas
    }
    printf("\n");

    for (int i = 0; i < tam_tableros; i++) {
        printf("%2d ", i); // Encabezado de filas
        for (int j = 0; j < tam_tableros; j++) {
            printf("%2c ", tableroJugador.Tablero_flota[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("TABLERO OPONENTE\n");
    printf("\n   ");
    for (int j = 0; j < tam_tableros; j++) {
        printf("%2d ", j); // Encabezado de columnas
    }
    printf("\n");

    for (int i = 0; i < tam_tableros; i++) {
        printf("%2d ", i); // Encabezado de filas
        for (int j = 0; j < tam_tableros; j++) {
            printf("%2c ", tableroJugador.Tablero_oponente[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
