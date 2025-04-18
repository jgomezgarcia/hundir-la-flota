#include "configuracion.h"
#include "disparo_Automatico.h"



static void marcar_barco_hundido (jugador* jug, char id_barco, int tam_tablero);
static int barco_hundido(jugador* defensor, char id_barco, int tam_tablero);
int comprobar_resultados_disparo(jugador* defensor, int* fila, int* columna, int tam_tablero, int* tocado);
static void gestionar_turnos (jugador *jugadores, int tam_tablero);

//Precondición: tener inicializados los tableros, el numero de barcos, y saber el disparo del jugador segun el turno
//Cabecera: int comprobar_resultados_disparo(jugador* defensor, int* fila, int* columna, int tam_tablero, int* tocado)
//Postcondición: devolverá un numero evaluando donde reciba el disparo

int comprobar_resultados_disparo(jugador* defensor, int* fila, int* columna, int tam_tablero, int* tocado) {
    // Validar coordenadas
    if (columna < 0 || columna >= tam_tablero || fila < 0 || fila >= tam_tablero) {
        return -1; // Coordenadas inválidas
    }

    // Verificar si ya se disparó aquí
    if (defensor->Tablero_oponente[fila][columna] != AGUA) {
        return -2; // Disparo repetido
    }

    // Registrar el disparo
    defensor->Tablero_oponente[fila][columna] = 1;

    // Comprobar resultado
    if (defensor->Tablero_flota[fila][columna] == AGUA) {
        defensor->Tablero_oponente[fila][columna] = AGUA;
        if (defensor->Tablero_oponente[fila][columna] == AGUA){
            defensor->Tablero_oponente[fila][columna] = '*';
        }
        *tocado = 0;

        return 0; // Agua
    }
    else if (defensor->Tablero_flota[fila][columna] == BARCO) {
        defensor->Tablero_oponente[fila][columna] = TOCADO;
        *tocado = 1;

        // Verificar si el barco está hundido
        char id_barco = defensor->Tablero_flota[fila][columna];

        // Buscar todas las partes del barco
        if (barco_hundido(defensor, id_barco, tam_tablero)) {
            int hundidos_num;
            marcar_barco_hundido(&defensor,id_barco,tam_tablero);
            hundidos_num = contar_hundidos_jugador(&defensor, tamTablero)

                // Verificar si todos los barcos están hundidos
                if ( hundidos_num == defensor->Num_Barcos) {
                    return 3; // Victoria
                }

            return 2; // Barco hundido
        }
        return 1; // Barco tocado
    }
        *tocado = 0;
    return -1; // Error desconocido
}

// Cabecera : static int barco_hundido(jugador* defensor, char id_barco, int tam_tablero);
// Precondicion: recorra la matriz observando si es tocado o hundido
// Poscondicion: devolvera un uno si el barco esta hundido (verdadero), sino u 0 (falso)

static int barco_hundido(jugador* defensor, char id_barco, int tam_tablero) {
    for (int i = 0; i < tam_tablero; i++) {
        for (int j = 0; j < tam_tablero; j++) {
            if (defensor->Tablero_flota[i][j] == id_barco) {
                char estado = defensor->Tablero_oponente[i][j];
                if (estado != TOCADO && estado != HUNDIDO) {
                    return 0; // Parte intacta encontrada
                }
            }
        }
    }
    return 1; // Todas las partes tocadas/hundidas
}

// Cabecera : static void marcar_barco_hundido (jugador* jug, char id_barco, int tam_tablero);
// Precondicion: recibir la matriz del jugador que recibe disparos, y que el id_barco se encuentre "hundido" osea todas sus posiciones tocadas
// Poscondicion: va a marcar todo ese barco como hundido

static void marcar_barco_hundido (jugador* jug, char id_barco, int tam_tablero){
    for (int i = 0; i < tam_tablero; i++) {
            for (int j = 0; j < tam_tablero; j++) {
                    if (defensor->Tablero_flota[i][j] == id_barco) {
                        defensor->Tablero_oponente[i][j] = HUNDIDO;
                    }
            }
    }
}

// Cabecera : static void gestionar_turnos (jugador *jugadores, int tam_tablero)
// Precondicion: recibir resultado disparo tras saber si es disparo automatico o manual y saber quien es el jugadir_actual
// Poscondicion: segun el disparo y su resultado realizara las distintas funciones hasta que el juego acabe o el jugador quiera pausar la partida

static void gestionar_turnos(jugador *jugadores, int tam_tablero) {

    int turno_actual = 0; // Índice del jugador actual
    int juego_terminado = 0;

    // Variables necesarias para el disparo automatico
    int ultimo_fila = -1, ultimo_columna = -1;
    int direccion_fila = 0, direccion_columna = 0;
    int impactos = 0;
    int tocado = 0;

    while (!juego_terminado) {
        jugador *atacante = &jugadores[turno_actual];
        jugador *defensor = &jugadores[(turno_actual + 1) % MAX_JUGADORES];

        printf("\n--- Turno de %s (Disparos: %d) ---\n", atacante->Nom_Jugador, atacante->Num_Disparos);

        int fila, columna;
        int resultado;

        do {
            // Realizar disparo según el tipo
            if (atacante->Tipo_Disparo == 'A') {
                disparo_automatico(atacante->Tablero_oponente, &fila, &columna, &ultimo_fila, &ultimo_columna, &tocado, &direccion_fila, &direccion_columna, &impactos);
                printf("Disparo automático en: (%d, %d)\n", fila, columna);
            } else {
                printf("\nTablero de Disparos:\n");
                imprimirTableroOponente(atacante->Tablero_oponente, tam_tablero);
                disparo_manual(atacante, defensor, &fila, &columna);
            }

            // Procesar resultado
            resultado = comprobar_resultados_disparo(defensor, fila, columna, tam_tablero, &tocado);
            atacante->Num_Disparos++; // Contar el disparo

            // Manejar resultado
            switch(resultado) {
                case 0: // Agua
                    atacante->Tablero_oponente[fila][columna] = AGUA;
                    printf("¡Agua! Turno terminado.\n");
                    break;

                case 1: // Tocado
                    atacante->Tablero_oponente[fila][columna] = TOCADO;
                    printf("¡Tocado! Continúa %s.\n", atacante->Nom_Jugador);
                    break;

                case 2: // Hundido
                    atacante->Tablero_oponente[fila][columna] = HUNDIDO;
                    printf("¡Hundido! %s sigue disparando.\n", atacante->Nom_Jugador);
                    break;

                case 3: // Victoria
                    atacante->Tablero_oponente[fila][columna] = HUNDIDO;
                    printf("¡%s gana la partida!\n", atacante->Nom_Jugador);
                    atacante->Ganador_Ronda = GANADOR;
                    defensor->Ganador_Ronda = PERDEDOR;
                    juego_terminado = 1;
                    break;

                case -1: case -2: // Errores
                    atacante->Num_Disparos--; // No contar disparos inválidos
                    break;
            }

        } while ((resultado == 1 || resultado == 2) && !juego_terminado);

        // Cambiar turno si fue agua (resultado 0)
        if (resultado == 0) {
            turno_actual = (turno_actual + 1) % MAX_JUGADORES;
        }
    }
}


