#pragma once

#include "Juego.h"
#include "colors.h"
#include <fstream>

const int N_HUECOS = 2; // huecos a dejar en el formato de las celdas.

using namespace std;

istream& operator>> (istream& in, Juego& juego);

void mostrar_cabecera();
void pedir_pos(int& fila, int& columna);
void mostrar_resultado(Juego& juego);
void mostrar_juego_consola(Juego& juego); // TODO: esto debería ser const Juego& juego
bool carga_juego(Juego& juego);