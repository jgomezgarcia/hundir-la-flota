#include <stdio.h>
#include <stdlib.h>
#include "configuracion.h"
#include "disparoAutomatico.h"
#include "interfaces.h"

// Definición de estados según tus especificaciones

#define VACIO '-'
#define AGUA '*'
#define TOCADO 'T'
#define HUNDIDO 'H'
#define BARCO 'X'  // Estado inicial de las partes de barco

// Prototipos
static void marcar_barco_hundido(jugador* jug, char id_barco, int tam_tablero);
static int barco_hundido(jugador* defensor, char id_barco, int tam_tablero);
static int contar_hundidos_jugador(jugador* jug, int tam_tablero);
int comprobar_resultados_disparo(jugador* defensor, int fila, int columna, int tam_tablero, int* tocado);
void cambiar_turnos(jugador* jug1, jugador* jug2);


//Cabecera: int comprobar_resultados_disparo(jugador* defensor, int* fila, int* columna, int tam_tablero, int* tocado)
//Precondición: tener inicializados los tableros, el numero de barcos, y saber el disparo del jugador segun el turno
//Postcondición: devolverá un numero evaluando donde reciba el disparo

int comprobar_resultados_disparo(jugador* defensor, int fila, int columna, int tam_tablero, int* tocado) {

    // Validación de coordenadas
    if (fila < 0 || fila >= tam_tablero || columna < 0 || columna >= tam_tablero) {
        *tocado = 0;
        return -1; // Coordenadas inválidas
    }

    // Verificación de disparo repetido
    char estado_actual = defensor->Tablero_oponente[fila][columna];
    if (estado_actual != VACIO && estado_actual != AGUA) {
        *tocado = 0;
        return -2; // Disparo repetido
    }

    // Comprobar resultado del disparo
    if (defensor->Tablero_flota[fila][columna] == VACIO || defensor->Tablero_flota[fila][columna] == AGUA) {
        defensor->Tablero_oponente[fila][columna] = AGUA;
        *tocado = 0;
        return 0; // Agua
    }
    else {
        // Si es una parte del barco
        char id_barco = defensor->Tablero_flota[fila][columna];
        defensor->Tablero_oponente[fila][columna] = TOCADO;
        *tocado = 1;

        if (barco_hundido(defensor, id_barco, tam_tablero)) {
            marcar_barco_hundido(defensor, id_barco, tam_tablero);

            if (contar_hundidos_jugador(defensor, tam_tablero) == defensor->Num_Barcos) {
                return 3; // Victoria
            }
            return 2; // Barco hundido
        }
        return 1; // Barco tocado
    }
}


// Cabecera : static int barco_hundido(jugador* defensor, char id_barco, int tam_tablero);
// Precondicion: recorra la matriz observando si es tocado o hundido
// Poscondicion: devolvera un uno si el barco esta hundido (verdadero), sino u 0 (falso)

static int barco_hundido(jugador* defensor, char id_barco, int tam_tablero) {
    for (int i = 0; i < tam_tablero; i++) {
        for (int j = 0; j < tam_tablero; j++) {
            if (defensor->Tablero_flota[i][j] == id_barco &&
                defensor->Tablero_oponente[i][j] != TOCADO &&
                defensor->Tablero_oponente[i][j] != HUNDIDO) {
                return 0;
            }
        }
    }
    return 1;
}

// Cabecera : static void marcar_barco_hundido (jugador* jug, char id_barco, int tam_tablero);
// Precondicion: recibir la matriz del jugador que recibe disparos, y que el id_barco se encuentre "hundido" osea todas sus posiciones tocadas
// Poscondicion: va a marcar todo ese barco como hundido

static void marcar_barco_hundido(jugador* jug, char id_barco, int tam_tablero) {
    for (int i = 0; i < tam_tablero; i++) {
        for (int j = 0; j < tam_tablero; j++) {
            if (jug->Tablero_flota[i][j] == id_barco) {
                jug->Tablero_oponente[i][j] = HUNDIDO;
            }
        }
    }
}

// Cabecera : static void gestionar_turnos (jugador *jugadores, int tam_tablero)
// Precondicion: recibir resultado disparo tras saber si es disparo automatico o manual y saber quien es el jugadir_actual
// Poscondicion: segun el disparo y su resultado realizara las distintas funciones hasta que el juego acabe o el jugador quiera pausar la partida

void gestionar_turnos(jugador *jug1, jugador *jug2, int tam_tablero) {

    int juego_terminado = 0;
    int ultimo_fila = -1, ultimo_columna = -1;
    int direccion_fila = 0, direccion_columna = 0;
    int impactos = 0;
    int tocado = 0;

    while (!juego_terminado) {

            if (jug1.turno == 1) {
                    jugador *atacante = jug1;
                    jugador *defensor = jug2;
            }
            else if (jug2.turno == 1) {
                    jugador *atacante = jug2;
                    jugador *defensor = jug1;

            }

        printf("\n--- Turno de %s (Disparos: %d) ---\n",
              atacante->Nom_Jugador, atacante->Num_Disparos);

        int fila, columna;
        int resultado;

        do {
            if (atacante->Tipo_Disparo == 'A') {
                disparo_automatico(atacante->Tablero_oponente, &fila, &columna, &ultimo_fila, &ultimo_columna, &tocado, &direccion_fila, &direccion_columna, &impactos, tam_tablero);
                printf("Disparo automático en: (%d, %d)\n", fila, columna);
            } else {
                printf("\nTablero de Disparos:\n"); // enseñamos el tablero al oponente
                imprimirTableroOponente(atacante->Tablero_oponente, tam_tablero);
                disparo_manual(&fila, &columna);
            }

            resultado = comprobar_resultados_disparo(defensor, fila, columna, tam_tablero, &tocado);

            if (resultado >= 0) {
                atacante->Num_Disparos++;
            }

            switch(resultado) {
                case 0:
                    printf("¡Agua!\n");
                    break;
                case 1:
                    printf("¡Tocado!\n");
                    break;
                case 2:
                    printf("¡Hundido!\n");
                    break;
                case 3:
                    printf("¡Victoria de %s!\n", atacante->Nom_Jugador);
                    atacante->Ganador_Ronda = GANADOR;
                    defensor->Ganador_Ronda = PERDEDOR;
                    juego_terminado = 1;
                    break;
                case -1:
                    printf("Error: Coordenadas fuera del tablero\n");
                    break;
                case -2:
                    printf("Error: Ya habías disparado ahí\n");
                    break;
            }

            imprimirTableroOponente(atacante->Tablero_oponente, tam_tablero);
            guardarPartida(barcosElegidos,jugadores, tam_lista, numBarcos, tam_tablero);

        } while ((resultado < 0 || resultado == 1 || resultado == 2) && !juego_terminado);

        if (resultado == 0) {
            cambiar_turnos(atacante,defensor);
        }
    }
}

// Cabecera : static void cambiar_turnos(jugador* jug1, jugador* jug2
// Precondicion: recibir resultado sea igual a 0
// Poscondicion: intercambia los turnos segun el jugador que este jugando

static void cambiar_turnos(jugador* jug1, jugador* jug2){

    if (jug1.turno == 1) {
        jug1.turno = 0;
        jug2.turno = 1;
    }
    else {
        jug1.turno = 1;
        jug2.turno = 0;
    }
}
