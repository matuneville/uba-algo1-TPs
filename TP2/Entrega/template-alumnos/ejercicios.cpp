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

/* Este algoritmo tiene una complejidad de O(n * m^2). La complejidad de agregarJugadasNuevas es O(n),
   ya que recorre t0do el largo de jugadas. Luego, el peor caso posible para esta función es tener
   que recorrer todas las casillas del tablero (m^2), cuando ninguna esta jugada ni tiene minas adyacentes.
   De esta manera, la complejidad es O(n) por todas las casillas = O(n*m^2) */

void jugarPlus(tablero& t, banderitas& b, pos p, jugadas& j) {
    if (!tieneBanderita(p, b) && estaEnTablero(p,t) && !esPosicionJugada(p,j)) {
        int minasAdy = minasAdyacentes(t, p);
        if (minasAdy >= 1)
            agregarJugadasNuevas(p, minasAdy, j);
        else {
            for (int i = -1; i <= 1; ++i) {
                for (int k = -1; k <= 1; ++k) {
                    pos posAdy = make_pair(p.first + i, p.second + k);
                    if (estaEnTablero(posAdy, t) && not tieneBanderita(posAdy, b)) {
                        agregarJugadasNuevas(posAdy, minasAdyacentes(t, posAdy), j);
                        jugarPlus(t, b, posAdy, j);
                    }
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
    bool existe2 = false, hayPosSugerible = false;
    int indice2 = 0;

    for(int i = 0; i < largoJugadas && !hayPosSugerible; i++) {
        if(j[i].second == 2) {
            if(existen1y1Horizontales(j, j[i].first,t)){
                hayPosSugerible = true;
                p = sugieroPHorizontal(j[i].first, t, j, b, hayPosSugerible);
            }
            else if(existen1y1Verticales(j, j[i].first,t)) {
                hayPosSugerible = true;
                p = sugieroPVertical(j[i].first, t, j, b, hayPosSugerible);
            }
        }
    }

    return hayPosSugerible;
}