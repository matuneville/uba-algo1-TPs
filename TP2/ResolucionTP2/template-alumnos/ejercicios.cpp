//
// Este archivo contiene las definiciones de las funciones que implementan los ejercicios
//

#include <stdio.h>
#include <iostream>


#include "definiciones.h"
#include "ejercicios.h"
#include "auxiliares.h"

using namespace std;

/******++++**************************** EJERCICIO minasAdyacentes ***********+++***********************/

int minasAdyacentes(tablero& t, pos p) {
    int contadorMinas = 0;
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            pos celdaAdyacente = make_pair(p.first + i, p.second + j);
            if (estaEnTablero(celdaAdyacente, t) && (i != 0 || j != 0) &&
            hayMina({p.first + i, p.second + j}, t))
                contadorMinas++;
        }
    }
    return contadorMinas;
}

/******++++**************************** EJERCICIO plantarBanderita ***********+++***********************/

void cambiarBanderita(tablero& t, jugadas& j, pos p, banderitas& b) {
    int banderitasLargo = b.size();
    for (int i = 0; i < b.size() && b.size() == banderitasLargo; ++i) {
        if (b[i] == p)
            removerPosicion(b, i);
    }
    if (banderitasLargo == b.size())
        b.push_back(p);
}

/******++++**************************** EJERCICIO perdio ***********+++***********************/
bool perdio(tablero& t, jugadas& j) {
    // ...
}

/******++++**************************** EJERCICIO gano ***********+++***********************/
bool gano(tablero& t, jugadas& j) {
    // ...
}

/******++++**************************** EJERCICIO jugarPlus ***********+++***********************/
void jugarPlus(tablero& t, banderitas& b, pos p, jugadas& j) {
    // ...
}

/******++++**************************** EJERCICIO sugerirAutomatico121 ***********+++***********************/
bool sugerirAutomatico121(tablero& t, banderitas& b, jugadas& j, pos& p) {
    // ...
}
