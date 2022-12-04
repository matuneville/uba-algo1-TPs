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

/* Este algoritmo tiene complejidad O(1), porque independientemente del tamaño de la entrada
   (el tamaño del tablero), en el peor caso (que tenga 8 casillas adyacentes)
   va a realizar la misma cantidad de iteraciones.
   Y lo mismo sucede con las funciones estaEnTablero y hayMina. */

int minasAdyacentes(tablero& t, pos p) {
    int contadorMinas = 0;
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            pos celdaAdyacente = make_pair(p.first + i, p.second + j);
            if (estaEnTablero(celdaAdyacente, t) && (i != 0 || j != 0) &&
            hayMina(celdaAdyacente, t))
                contadorMinas++;
        }
    }
    return contadorMinas;
}

/******++++**************************** EJERCICIO plantarBanderita ***********+++***********************/

/* Este algoritmo tiene complejidoad O(l^2). La función removerPosición tiene complejidad O(l),
   siendo l el largo de la secuencia de banderitas, ya que siempre va a realizar tantas
   iteraciones como el tamaño de l. Luego, esta funcion es llamada dentro del ciclo
   de cambiarBanderita, cuyas iteraciones tambien dependen de l (en el peor caso).
   Por lo tanto, queda una complejidad de O(l) * O(l) = O(l^2). */

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

/* Este algoritmo tiene una complejidad de O(n). De vuelta, la función hayMina no depende de n ni m,
   y la cantidad de iteraciones que realiza va a ser igual al tamaño de n, siendo n el largo
   de la secuencia de jugadas y m el largo del tablero. */

bool perdio(tablero& t, jugadas& j) {
    int cantidadMinas = 0;
    for (int i = 0; i < j.size(); ++i) {
        if(hayMina((j[i].first), t))
            cantidadMinas++;
    }
    bool tieneMina = (cantidadMinas == 1);
    return tieneMina;
}

/******++++**************************** EJERCICIO gano ***********+++***********************/

/* Este algoritmo tiene una complejidad de O(m^2). La funcion cantPosicionesSinMinas
   tiene una complejidad de m^2, siendo m el tamaño del tablero. Por lo tanto, la función gano
   tiene una complejidad de O(n), siendo n del largo de jugadas, + O(m^2), (sumadas, ya que
   la segunda no se encuentra dentro del ciclo). Luego, O(n) + O(m^2) = O(n + m^2). Pero como n <= m^2 siempre,
   podemos decir que O(n) + O(m^2) = O(m^2).*/

bool gano(tablero& t, jugadas& j) {
    int cantJugadasConMinas = 0;
    for (int i = 0; i < j.size(); ++i) {
        if(hayMina((j[i].first), t)) {
            cantJugadasConMinas++;
        }
    }
    bool gano = false;
    if(cantJugadasConMinas == 0 && j.size() == cantPosicionesSinMinas(t)) {
        gano = true;
    }
    return gano;
}

/******++++**************************** EJERCICIO jugarPlus ***********+++***********************/
// Complejidad corregida
/* Este algoritmo tiene una complejidad de O(m^2 * (l + n)).
 * Cada vez que se llama la función con una posición, uno de los chequeos que realiza la misma para ejecutarse
 * es fijarse que la posición no se encuentre en la lista de jugadas. Solo en caso de que la posición
 * no se encuentre ahí, entonces la función se ejecuta, y agrega luego dicha posición a la lista.
 * Por esa razón consideramos que en el peor caso, la función debe llamarse para todas las posiciones del tablero
 * (O(m^2)), y que la recursión no podría llamarse mas de una vez sobre la misma posición.
 * Luego, cada vez que la función es llamada, realiza los chequeos con las funciones tieneBanderita,
 * estaEnTablero, esPosicionJugada y perdio, que tienen las siguientes complejidades, respectivamente:
 *  O(l), O(1), O(n) y O(n). Luego, si pasa esos chequeos, llama a agregarJugadasNuevas, que tiene complejidad O(n).
 *  De esta manera, la complejidad de este algoritmo es O(m^2 * (l + 3n)) = O(m^2 * (l + n)) */

void jugarPlus(tablero& t, banderitas& b, pos p, jugadas& j) {
    if (!tieneBanderita(p, b) && estaEnTablero(p,t) && !esPosicionJugada(p,j) && !perdio(t,j)) {
        int minasAdy = minasAdyacentes(t, p);
        if (minasAdy >= 1)
            agregarJugadasNuevas(p, minasAdy, j);
        else {
            agregarJugadasNuevas(p, minasAdyacentes(t, p), j);
            for(int i = -1; i <= 1; i++){
                for(int k = -1; k <= 1; k++){
                    jugarPlus(t,b, make_pair(p.first+i,p.second+k),j);
                }
            }
        }
    }
}

/******++++**************************** EJERCICIO sugerirAutomatico121 ***********+++***********************/

/* Este algoritmo tiene una complejidad de O(n^2), siendo n el largo de la secuencia de jugadas.
 * El ciclo tiene una complejidad de O(n). Luego, las funciones existen121 tienen ambas complejidad de O(n)
 * (por la función esPosicionJugada). Como estas funciones son ejecutadas dentro del ciclo mencionado, la
 * complejidad de sugerirAutomatico121 es O(n) * O(n) = O(n^2) */

bool sugerirAutomatico121(tablero& t, banderitas& b, jugadas& j, pos& p) {
    int largoJugadas = j.size();
    bool hayPosSugerible = false;
    p = {-1,-1};

    for(int i = 0; i < largoJugadas && !hayPosSugerible; i++) {
        if(j[i].second == 2) {
            if(existen1y1Horizontales(j, j[i].first,t)){
                hayPosSugerible = true;
                p = sugieroPHorizontal(j[i].first, t, j, b);
            }
            else if(existen1y1Verticales(j, j[i].first,t)) {
                hayPosSugerible = true;
                p = sugieroPVertical(j[i].first, t, j, b);
            }
        }
    }
    return hayPosSugerible;
}