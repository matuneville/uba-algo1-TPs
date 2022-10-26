//
// Este archivo contiene las definiciones de las funciones auxiliares
// que ustedes necesiten implementar. Tienen que coincidir con las 
// declaraciones de auxiliares.h
//

#include <iostream>

#include "definiciones.h"
#include "ejercicios.h"
#include "auxiliares.h"

using namespace std;

bool estaEnTablero (pos p, tablero &t){
    return (p.first >= 0 && p.first < t.size() && p.second >= 0 && p.second < t[0].size());
}

bool hayMina (pos p, tablero& t){
    return (t[p.first][p.second]);
}

void removerPosicion (banderitas &b, int index){
    banderitas nuevoB{};
    for (int i = 0; i < b.size(); ++i) {
        if (i != index)
            nuevoB.push_back(b[index]);
    }
    b = nuevoB;
}

int cantPosicionesSinMinas(tablero& t) {
    int cantSinMinas = 0;
    for (int i = 0; i < t.size(); ++i) {
        for (int j = 0; j < t.size(); ++j) {
            pos p = make_pair(i, j);
            if (!hayMina(p, t))
                cantSinMinas++;
        }
    }
    return cantSinMinas;
}


bool esPosicionSinJugar(pos p, jugadas& j) {
    bool esJugada = false;
    for (int i = 0; i < j.size(); ++i) {
        if(p == j[i].first)
            esJugada = true;
    }
    return esJugada;
}

void agregarJugadasNuevas(pos p, int minas, jugadas& j) {
    if (esPosicionSinJugar(p,j)) {
        jugada elem = make_pair(p, minas);
        j.push_back(elem);
    }
}

bool tieneBanderita(pos p, banderitas b) {
    bool existe = false;
    for (int i = 0; i < b.size(); ++i) {
        if(b[i] == p)
            existe = true;
    }
    return existe;
}