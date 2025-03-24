#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "configuracion.h"

static void desglosarInfoBarcos(char *, barcos *);

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

//Poscondición: imprimir por pantalla los tipos de barcos disponibles
void listar_barcos(barcos *barcosMostrar, int numBarcos){
  printf("\n --- BARCOS DISPONIBLES --- \n");
  printf("   \t Nombre \t Tam \t\n");
  for(int i = 0; i < numBarcos; i++){
    printf("%d: \t %s \t %d \t\n", i+1, barcosMostrar[i].Nom_Barco, barcosMostrar[i].Tam_Barco);
  }
  printf("---------------------------");
}
