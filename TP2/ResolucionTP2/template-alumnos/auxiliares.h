
//
// Este archivo contiene las declaraciones de las funciones auxiliares
// que ustedes necesiten implementar. Tienen que coincidir con el código
// de esas mismas funciones, que estará en auxiliares.cpp
//

#pragma once   // esta línea es para que el archivo se incluya una sola vez

#include "definiciones.h"

bool estaEnTablero (pos p, tablero &t);
bool hayMina (pos p, tablero& t);
void removerPosicion (banderitas &b, int posicion);