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