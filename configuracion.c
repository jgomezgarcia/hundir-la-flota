#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include "configuracion.h"

#define CONFIG_BARCOS "./configurables/barcos.txt"
#define GUARDAR_PARTIDA "./configurables/juego.txt"
#define PORCENTAJE_AGUA 0.6


static void desglosarInfoBarcos(char *, barcos *);
static int numLineasFichero(FILE *);
static barcos *leerBarcos(int *);
static void listarBarcos(int , barcos *);
static int indicePorIdBarco(char , barcos *, int);
static char ** reservar_tablero(int);
static void eliminarSalto(char *, int);
static int validarNumBarcos(int , int);
static void volcarEnFicheroTableros(char **, char **, int, FILE *);
static void liberarTableros(int , char **, char **);
static void recuperarTableros(char **, char *, int, FILE *);


//Precondición: recibir una cadena ya inicializada y recibe por referencia la estructura barco
//Poscondición: separa la cadena por tokens
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

//Precondición: {tam_tablero >= 3}
//Poscondición: devuelve puntero a matriz de char guardada en memoria
static char ** reservar_tablero(int tam_Tablero){
  char **tablero;
  tablero = (char **)malloc(tam_Tablero*sizeof(char *));
  for(int i = 0; i < tam_Tablero; i++){
    tablero[i] = (char *)malloc(tam_Tablero * sizeof(char));
  }

  return tablero;
}

//Precondición: {*nBarcosDisponibles > 0}
//Poscondición: devuelve la estructura de barcos ya inicializada con los disponibles
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

//Precondición: {nBarcos > 0 ^ *barcosListados != NULL}
//Poscondición: imprime por pantalla los barcos disponibles leidos de fichero
static void listarBarcos(int nBarcos, barcos *barcosListados){
  printf("--- BARCOS JUGABLES ---\n");
  printf("%-15s %-5s %-5s\n", "Nombre", "ID", "Tam");
  for (int i = 0; i < nBarcos; i++) {
      printf("%-15s %-5c %-5d\n",barcosListados[i].Nom_Barco,barcosListados[i].Id_Barco,barcosListados[i].Tam_Barco);
  }
  printf("--------------------------\n");
}

//Precondición: {id != NULL, barcosDisponibles != NULL, nBarcosDisponibles > 0}
//Poscondición: devuelve un entero con el índice del barco encontrado
static int indicePorIdBarco(char id, barcos *barcosDisponibles, int nBarcosDisponibles){
  for(int i = 0; i < nBarcosDisponibles; i++){
    if(barcosDisponibles[i].Id_Barco == id){
      return i;
    }
  }

  return -1;
}

//Precondición: {*aux != NULL, tamano > 0}
//Poscondición: devuelve la cadena eliminando \n  y sustituyendolo por \0
static void eliminarSalto(char *aux, int tamano){
  for(int i = 0; i < tamano; i++){
    if(aux[i] == '\n'){
      aux[i] = '\0';
    }
  }
}

//Precondición: {**flota != NULL, **oponente != NULL, tam_tablero >= 3}
//Poscondición: inicializa ambos tableros asignandole caracteres a cada posición

//Precondición: recibir una cadena ya inicializada y recibe por referencia la estructura barco
//Poscondición: devuelve 1 si es valido y 0 sino lo es
static int validarNumBarcos(int tamBarcos, int tamTablero){
  int espacioTablero, aguaDisponible;
  float porcentajeAguaDisponible;

  espacioTablero = tamTablero*tamTablero;
  aguaDisponible = espacioTablero - tamBarcos;
  porcentajeAguaDisponible = (float)aguaDisponible/espacioTablero;

  if(porcentajeAguaDisponible >= PORCENTAJE_AGUA){
    return 1;
  } else {
    return 0;
  }

}

//Precondición: recibir los tableros ya inicializados, tam >= 3, fichero ya abierto
//Poscondición: vuelca en fichero los tableros
static void volcarEnFicheroTableros(char **flota, char **oponente, int tam, FILE *f){
  if(f == NULL){
    printf("No se pudo abrir el fichero juego.txt. \n");
    exit(1);
  }
  for(int i = 0; i < tam; i++){
      for(int j = 0; j < tam; j++){
        fprintf(f, "%c", flota[i][j]);
      }
      fprintf(f, "\n");
  }

  for(int i = 0; i < tam; i++){
      for(int j = 0; j < tam; j++){
        fprintf(f, "%c", oponente[i][j]);
      }
      fprintf(f, "\n");
  }
}

//Precondición: tam_tablero >= 3, tableros con memoria reservada
//Poscondición: elimina de memoria el espacio reservado para los tableros
static void liberarTableros(int tam_tablero, char **flota, char **oponente){
  for(int i = 0; i < tam_tablero; i++){
    free(flota[i]);
  }

  for(int i = 0; i < tam_tablero; i++){
    free(oponente[i]);
  }

  free(flota);
  free(oponente);
}

static void recuperarTableros(char **tablero, char *buffer, int tamTableros, FILE *f){
  for(int lineas = 0; lineas < tamTableros; lineas++){
    fgets(buffer, tamTableros+2, f);
    buffer[strcspn(buffer, "\n")] = '\0';
    for(int columnas = 0; columnas < tamTableros; columnas++){
      tablero[lineas][columnas] = buffer[columnas];
    }
   }
}

// Función para contar barcos hundidos de un jugador
int contar_hundidos_jugador(jugador *jug, int tamTablero) {
    if (jug == NULL || jug->Tablero_oponente == NULL) return 0;

    // Creamos matriz de visitados usando enteros (0 = no visitado, 1 = visitado)
    int **visitado = (int**)malloc(tamTablero * sizeof(int*));
    for (int i = 0; i < tamTablero; i++) {
        visitado[i] = (int*)calloc(tamTablero, sizeof(int));
    }

    int hundidos = 0;

    // Direcciones para las 8 posiciones adyacentes (horizontal, vertical, diagonal)
    int dir[8][2] = {{-1,-1}, {-1,0}, {-1,1},
                     {0,-1},          {0,1},
                     {1,-1},  {1,0}, {1,1}};

    for (int i = 0; i < tamTablero; i++) {
        for (int j = 0; j < tamTablero; j++) {
            // Si encontramos una parte de barco hundido no visitada
            if (jug->Tablero_oponente[i][j] == 'H' && visitado[i][j] == 0) {
                hundidos++; // Nuevo barco encontrado

                // Usamos arrays para simular una cola (BFS)
                int *cola_x = (int*)malloc(tamTablero * tamTablero * sizeof(int));
                int *cola_y = (int*)malloc(tamTablero * tamTablero * sizeof(int));
                int frente = 0, final = 0;

                // Marcamos y añadimos la posición inicial
                visitado[i][j] = 1;
                cola_x[final] = i;
                cola_y[final] = j;
                final++;

                while (frente < final) {
                    int x = cola_x[frente];
                    int y = cola_y[frente];
                    frente++;

                    // Exploramos las 8 direcciones posibles
                    for (int d = 0; d < 8; d++) {
                        int nx = x + dir[d][0];
                        int ny = y + dir[d][1];

                        // Verificamos límites y si es parte del mismo barco no visitado
                        if (nx >= 0 && nx < tamTablero && ny >= 0 && ny < tamTablero &&
                            jug->Tablero_oponente[nx][ny] == 'H' && visitado[nx][ny] == 0) {
                            visitado[nx][ny] = 1;
                            cola_x[final] = nx;
                            cola_y[final] = ny;
                            final++;
                        }
                    }
                }

                free(cola_x);
                free(cola_y);
            }
        }
    }

    // Liberamos la matriz de visitados
    for (int i = 0; i < tamTablero; i++) {
        free(visitado[i]);
    }
    free(visitado);

    return hundidos;
}

/*  FUNCIONES PUBLICAS  */

//Precondición: memoria reservada para ambas tableros y tam_tablero >= 3
//Poscondición: Devuelve los tableros con valores ya asignados
void inicializarTableros(char **flota, char**oponente, int tam_tablero){
  for(int i = 0; i < tam_tablero; i++){
    for(int j = 0; j < tam_tablero; j++){
      flota[i][j] = '-';
      oponente[i][j] = '-';
    }
  }
}

//Precondición: {nBarcosJugar > 0, tamListaElegidos > 0; tam_tablero >= 3}
//Poscondición: devuelve los barcos elegidos por el usuario
barcos *barcosParaJugar(int *nBarcosJugar, int *tamListaElegidos, int *tam_tablero){
    int sumaBarcosIntroducidos, indiceBarcoElegido, indicePorId, cantBarcosTipo, nBarcosDisponibles, barcosCorrectos , tamTotalBarcos;
    char tipoBarco;

    barcos *barcosDisponibles, *barcosJugar;
    barcosDisponibles = leerBarcos(&nBarcosDisponibles); //Carga los barcos jugables almacenado en barcos.txt

    do{
      printf("Introduzca el tamaño de su tablero: ");
      scanf("%d", tam_tablero);
    }while(*tam_tablero < 3);

    do{
      listarBarcos(nBarcosDisponibles, barcosDisponibles);
      printf("Introduzca la cantidad de barcos deseados para jugar.\nTenga en cuenta que su tablero tiene %d espacios disponible y los barcos no deben ocupar más del 40%%: ", (*tam_tablero)*(*tam_tablero));
      scanf("%d", nBarcosJugar);
      system("cls");
    }while(*nBarcosJugar <= 0);

    listarBarcos(nBarcosDisponibles, barcosDisponibles);
    printf("Ha elegido %d barcos en total.\n", *nBarcosJugar);

    barcosJugar = (barcos *)malloc(*nBarcosJugar*sizeof(barcos));
    if(barcosJugar == NULL){
      printf("No se pudo reservar memoria para los barcos seleccionados. \n");
      exit(1);
    }

    while(!barcosCorrectos){ //Controla que no se ocupe el 40%

        sumaBarcosIntroducidos = 0;
        indiceBarcoElegido = 0;
        tamTotalBarcos = 0;
        *tamListaElegidos = 0;

      do{ //Controla que la cantidad de barcos de cada tipo no sea superior a la total

        fflush(stdin);
        printf("\nQue tipo de barco quiere usar introduzca el id: ");
        scanf("%c", &tipoBarco);
        tipoBarco = toupper(tipoBarco);
        indicePorId = indicePorIdBarco(tipoBarco, barcosDisponibles, nBarcosDisponibles);


          if(indicePorId != -1){ //Si encuentra el id pide al usuario la cantidad que desea
            printf("Introduzca el número de barcos del tipo %c:", tipoBarco);
            scanf("%d", &cantBarcosTipo);

            sumaBarcosIntroducidos += cantBarcosTipo;

            if(*nBarcosJugar - sumaBarcosIntroducidos >= 0){   //Se encarga de controlar que no se supere el numero de barcos
              for(int j = 0; j < cantBarcosTipo; j++){       //Va guardando segun la cantidad de barcos
                strcpy(barcosJugar[indiceBarcoElegido].Nom_Barco, barcosDisponibles[indicePorId].Nom_Barco);
                barcosJugar[indiceBarcoElegido].Id_Barco = barcosDisponibles[indicePorId].Id_Barco;
                barcosJugar[indiceBarcoElegido].Tam_Barco = barcosDisponibles[indicePorId].Tam_Barco;
                indiceBarcoElegido++;
            }

            tamTotalBarcos += cantBarcosTipo * barcosDisponibles[indicePorId].Tam_Barco;
            *tamListaElegidos += 1;


            } else {
              printf("Cantidad de barcos erronea pruebe con otra cantidad que no supere a los iniciales elegidos. \n");
              sumaBarcosIntroducidos -= cantBarcosTipo;
            }

          } else {
            printf("Id de barco inválido introduzca otro. \n");
          }

      }while(sumaBarcosIntroducidos < *nBarcosJugar);


      barcosCorrectos = validarNumBarcos(tamTotalBarcos, *tam_tablero);

      if(barcosCorrectos == 1){
        printf("Barcos cargados correctamente. \n");
        Sleep(1000);
      } else {
        printf("Los barcos elegidos ocupan más del 40%% del espacio del tablero.\nPor favor, pruebe otra combinación.\n");
      }
    }


    system("cls");
    free(barcosDisponibles);
    return barcosJugar;
}

//Precondición: {tam_tablero >= 3 ^ nBarcos > 0}
//Poscondición: Devuelve la estructura jugador ya cargada con la configuración elegida
jugador *configurarJugador(int tam_tablero, int nBarcos){
  jugador *jugadorConfigurar;

  jugadorConfigurar = (jugador *)malloc(MAX_JUGADORES * sizeof(jugador));

  char tipoDisparo, tipoTurno;
  int turno;
  srand(time(NULL));

  for(int i = 0; i < MAX_JUGADORES; i++){
    fflush(stdin);
    printf("Introduzca el nombre para el jugador %d: ", i+1);
    fgets(jugadorConfigurar[i].Nom_Jugador, LONGITUD_NOMBRE, stdin);
    printf("\n");
    eliminarSalto(jugadorConfigurar[i].Nom_Jugador, LONGITUD_NOMBRE);

    do{
      printf("Introduzca el tipo de disparo para el jugador %s, Automático(A) o Manual(M): ", jugadorConfigurar[i].Nom_Jugador);
      scanf("%c", &tipoDisparo);
      printf("\n");
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
    jugadorConfigurar[i].Num_Disparos = 0;
    jugadorConfigurar[i].Ganador_Ronda = 0;
  }

  do{
      printf("Quiere asignar el turno(S/N): ");
      scanf("%c", &tipoTurno);
      tipoTurno = toupper(tipoTurno);
      fflush(stdin);
  } while(tipoTurno != 'S' && tipoTurno != 'N');  //Controla caracteres inválidos

  if(tipoTurno == 'S'){
    do{
      printf("Que jugador comenzará la partida, introduzca su número, (1/2): ");
      scanf("%d", &turno);
      printf("\n");
      jugadorConfigurar[turno-1].turno = 1;//Aquel jugador elegido se el asigna turno 1
    }while(turno > 2 || turno <= 0);
  } else {
    printf("Turno asignado automáticamente... \n");
    printf("\n");
    turno = rand() % 2;   //Devuelve un indice aleatorio
    jugadorConfigurar[turno].turno = 1;
    Sleep(1000);
  }

  printf("Configuración cargada correctamente. \n");
  printf("\n");
  system("cls");
  return jugadorConfigurar;
}

//Precondición: recibir  ya inicializado el tablero y el tamaño de tableros que debe ser mayor de 3
//Poscondición: imprime tablero flota
void imprimirTableroFlota(char **tableroFlota, int tam_tableros){
  printf("TABLERO FLOTA");
    printf("\n   ");
    for (int j = 0; j < tam_tableros; j++) {
        printf("%2d ", j); // Encabezado de columnas
    }
    printf("\n");

    for (int i = 0; i < tam_tableros; i++) {
        printf("%2d ", i); // Encabezado de filas
        for (int j = 0; j < tam_tableros; j++) {
            printf("%2c ", tableroFlota[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//Precondición: recibir  ya inicializado el tablero y el tamaño de tableros que debe ser mayor de 3
//Poscondición: imprime tablero oponente
void imprimirTableroOponente(char **tableroOponente, int tam_tableros){
  printf("TABLERO OPONENTE\n");
    printf("\n   ");
    for (int j = 0; j < tam_tableros; j++) {
        printf("%2d ", j); // Encabezado de columnas
    }
    printf("\n");

    for (int i = 0; i < tam_tableros; i++) {
        printf("%2d ", i); // Encabezado de filas
        for (int j = 0; j < tam_tableros; j++) {
            printf("%2c ", tableroOponente[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//Precondición {tam_tableros >= 3; nBarcos > 0; barcosConfigurados != NULL; jugadoresConfigurados != NULL}
//Poscondición: Imprime por pantalla toda la configuración elegida
void mostrarConfiguracion(int tam_tableros, int nBarcos, barcos *barcosConfigurados, jugador *jugadoresConfigurados){
  barcos *barcosDisponibles;    //Se usa para contabilizar la cantidad elegida de cada tipo
  int numBarcosDisponibles, numBarcosTipo;
  barcosDisponibles = leerBarcos(&numBarcosDisponibles);
  if(barcosDisponibles == NULL){
    printf("No se pudo cargar los barcos disponibles. \n");
    exit(1);
  }

  if(barcosConfigurados == NULL || jugadoresConfigurados == NULL){
    printf("No existe ninguna configuración cargada, vuelva más tarde. \n");
  }else {
    printf("--- CONFIGURACION CARGADA ---\n");
    printf("\n");
    printf("Estos son sus datos configurados sobre flota: \n");
    printf("\n");
    printf("Ha elegido %d barcos.\n", nBarcos);
    printf("\n");

    for(int i = 0; i < numBarcosDisponibles; i++){  //Recorre los barcos disponibles
      numBarcosTipo = 0;
      for(int j = 0; j < nBarcos; j++){ //Recorre los barcos elegidos
        if(barcosDisponibles[i].Id_Barco == barcosConfigurados[j].Id_Barco){
          numBarcosTipo++;
        }
      }

      if(numBarcosTipo != 0){ //Imprime solo aquellos que hayan sido elegidos
        printf("--- HAY %d %s ---\n", numBarcosTipo, barcosDisponibles[i].Nom_Barco);
        printf("\n");
      }
    }

    printf("------------------------------------------------------------------------\n");

    printf("Estos son sus datos configurados para cada jugador: \n");
    printf("\n");

    printf("Ambos jugadores han decidido jugar con tableros de %d x %d. \n", tam_tableros, tam_tableros);
    printf("\n");
    for(int i = 0; i < MAX_JUGADORES; i++){
      printf("JUGADOR %d: \n", i+1);
      printf("\n");
      printf("Nombre: %s.\n", jugadoresConfigurados[i].Nom_Jugador);
      printf("\n");
      printf("Tipo de disparo: %c.\n", jugadoresConfigurados[i].Tipo_Disparo);
      printf("\n");

      if(jugadoresConfigurados[i].turno == 1){
        printf("Inicia el turno %s. \n", jugadoresConfigurados[i].Nom_Jugador);
      }
      printf("\n");
      printf("------------------------------------------------------------------------\n");
    }

  }

  free(barcosDisponibles);
}


//Precondición: {barcosConfigurados != NULL, jugadoresConfigurados != NULL; tamListaBarcosElegidos > 0; nBarcos > 0; tam_tableros >= 3}
//Poscondición: Vuelca en fichero los datos de partida, guardandolos permanentemente
void guardarPartida(barcos *barcosConfigurados, jugador *jugadoresConfigurados, int tamListaBarcosElegidos, int nBarcos, int tam_tableros){
    FILE *fJugadores;
    int nBarcosDisponibles, cantBarcosRepetidos;
    barcos *barcosDisponibles = leerBarcos(&nBarcosDisponibles);

    if(barcosConfigurados == NULL || jugadoresConfigurados == NULL){
      printf("No hay una configuración cargada, no puede guardar configuración. Vuelva más tarde. \n");
      Sleep(1000);
    }

    fJugadores = fopen(GUARDAR_PARTIDA, "w");
    if(fJugadores == NULL){
      printf("No se pudo abrir juego.txt. \n");
      exit(1);
    }


    fprintf(fJugadores, "%d-%d-%d\n", tam_tableros, nBarcos, tamListaBarcosElegidos); //Imprime la primera línea

    for(int i = 0; i < nBarcosDisponibles; i++){  //Encontramos la cantidad de cada tipo elegido
      cantBarcosRepetidos = 0;
      for(int j = 0; j < nBarcos; j++){
        if(barcosConfigurados[j].Id_Barco == barcosDisponibles[i].Id_Barco)
          cantBarcosRepetidos++;
      }
      if(cantBarcosRepetidos != 0)
        fprintf(fJugadores, "%c-%d\n", barcosDisponibles[i].Id_Barco, cantBarcosRepetidos);   //Imprime línea con su id y cantidad
    }

    for(int i = 0; i < MAX_JUGADORES; i++){
      //Para cada jugador se imprime su información correspondiente
      fprintf(fJugadores, "%d-%s-%d-%c-%d\n", jugadoresConfigurados[i].Id_Jugador, jugadoresConfigurados[i].Nom_Jugador, jugadoresConfigurados[i].Num_Disparos, jugadoresConfigurados[i].Tipo_Disparo, jugadoresConfigurados[i].Ganador_Ronda);
      volcarEnFicheroTableros(jugadoresConfigurados[i].Tablero_flota, jugadoresConfigurados[i].Tablero_oponente, tam_tableros,fJugadores);
    }

    fclose(fJugadores);
    free(barcosDisponibles);
}

//Precondición = {tamTableros != NULL; nBarcosElegidos != NULL}
//Poscondición = devuelve un púntero a esa estructura con todos los datos cargados de nuevo
barcos * recuperarBarcos(int *tamTableros, int *nBarcosElegidos, int *tamListaBarcos){
  barcos *recuperados;
  barcos *disponibles;    //Se usara para en función de id recuperar sus otros datos

  FILE *fJuego;
  char info[50];  //Buffer para la información
  int nBarcosDisponibles, cantBarco, indexBarcos = 0;
  char idBarco;
  disponibles = leerBarcos(&nBarcosDisponibles);

  fJuego = fopen(GUARDAR_PARTIDA, "r");
  if(fJuego == NULL){
    printf("No se pudo abrir Juego.txt. \n");
    exit(1);
  }

  fgets(info, 50, fJuego);
  *tamTableros = atoi(strtok(info, "-"));   //Desglose de información
  *nBarcosElegidos = atoi(strtok(NULL, "-"));
  *tamListaBarcos = atoi(strtok(NULL, "-"));

  recuperados = (barcos *)malloc(*nBarcosElegidos * sizeof(barcos));
  if(recuperados == NULL){
    printf("No se pudo reservar memoría para los barcos guardados. \n");
    exit(1);
  }

  for(int i = 0; i < *tamListaBarcos; i++){    //Encargado de cargar la lista de elegidos
    fgets(info, 50, fJuego);
    idBarco = (strtok(info, "-"))[0];
    cantBarco = atoi(strtok(NULL, "-"));

    for(int j = 0; j < cantBarco; j++){   //Almacena según la cantidad seleccionada
      recuperados[indexBarcos++].Id_Barco = idBarco;
    }
  }

  for(int i = 0; i < nBarcosDisponibles; i++){
    for(int j = 0; j < *nBarcosElegidos; j++){
      if(disponibles[i].Id_Barco == recuperados[j].Id_Barco){   //Todo esto nos ayuda a recuperar el nombre y tamaño según el id recibido
        strcpy(recuperados[j].Nom_Barco, disponibles[i].Nom_Barco);
        recuperados[j].Tam_Barco = disponibles[i].Tam_Barco;
      }
    }
  }

  free(disponibles);
  fclose(fJuego);
  return recuperados;
}

jugador *recuperarJugadores(int tamTableros, int nBarcosElegidos, int tamListaBarcosElegidos){
  srand(time(NULL));
  char infoJugadores[100];
  char *traerTableros;
  jugador *recuperados;
  FILE *fJuego;
  int hundidosJug1, hundidosJug2, turno;

  turno = rand() % 2;

  fJuego = fopen(GUARDAR_PARTIDA, "r");
  if(fJuego == NULL){
    printf("No se pudo abrir el fichero juego.txt. \n");
    exit(1);
  }

  recuperados = (jugador *)malloc(MAX_JUGADORES * sizeof(jugador));
  if(recuperados == NULL){
    printf("No se pudo reservar memoria para los barcos recuperados. \n");
    exit(1);
  }

  traerTableros = (char *)malloc((tamTableros+2)*sizeof(char));
  if(traerTableros == NULL){
    printf("No se pudo reservar memoria para el buffer que restablece los tableros. Compruebe el tamaño de los tableros.\n");
    exit(1);
  }

  for(int i = 0; i < tamListaBarcosElegidos + 1; i++){  //Desplaza el cursor a las lineas propias del jugador
    fgets(infoJugadores, 100, fJuego);
  }

  for(int i = 0; i < MAX_JUGADORES; i++){
    recuperados[i].Tablero_flota = reservar_tablero(tamTableros);
    recuperados[i].Tablero_oponente = reservar_tablero(tamTableros);
    fgets(infoJugadores, 100, fJuego);
    recuperados[i].Id_Jugador = atoi(strtok(infoJugadores, "-"));
    strcpy(recuperados[i].Nom_Jugador, strtok(NULL, "-"));
    recuperados[i].Num_Disparos = atoi(strtok(NULL, "-"));
    recuperados[i].Tipo_Disparo = (strtok(NULL, "-"))[0];
    recuperados[i].Ganador_Ronda = atoi(strtok(NULL, "-"));

    recuperarTableros(recuperados[i].Tablero_flota, traerTableros, tamTableros, fJuego);
    recuperarTableros(recuperados[i].Tablero_oponente, traerTableros, tamTableros, fJuego);
  }

  recuperados[turno].turno = 1;
  recuperados[!turno].turno = 0;

  hundidosJug2 = contar_hundidos_jugador(&recuperados[0], tamTableros);
  hundidosJug1 = contar_hundidos_jugador(&recuperados[1], tamTableros);

  recuperados[0].Num_Barcos = nBarcosElegidos - hundidosJug1;
  recuperados[1].Num_Barcos = nBarcosElegidos - hundidosJug2;

  free(traerTableros);
  fclose(fJuego);
  return recuperados;
}

//Precondición: barcosEliminar y jugadoresEliminar deben tener memoria reservada y tam_tablero >= 3
//Poscondición: libera el espacio en memoria ocupado por las estructuras jugadores y barcos
void eliminarConfiguracion(barcos *barcosEliminar, jugador *jugadoresEliminar, int tam_tablero){
  for(int i = 0; i < MAX_JUGADORES; i++)
    liberarTableros(tam_tablero, jugadoresEliminar[i].Tablero_flota, jugadoresEliminar[i].Tablero_oponente);

  free(barcosEliminar);
  free(jugadoresEliminar);
}
