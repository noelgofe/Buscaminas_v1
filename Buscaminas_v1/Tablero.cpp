#include "Tablero.h"

Tablero::Tablero() {
	filas = 0;
	columnas = 0;
}

Tablero::Tablero(int fils, int cols) {
	filas = fils;
	columnas = cols;
	for (int i = 0; i < fils; i++) {
		for (int j = 0; j < cols; j++) {
			celdas[i][j] = Celda();
		}
	}
}

void Tablero::destruye() {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			celdas[i][j].destruye();
		}
	}
	filas = 0;
	columnas = 0;
}

int Tablero::num_filas() const{
	return filas;
}

int Tablero::num_columnas() const{
	return columnas;
}

bool Tablero::es_valida(int fila, int columna) const {
	return (fila >= 0 and fila <= MAX_FILS and columna >= 0 and columna <= MAX_COLS);
}

Celda Tablero::dame_celda(int fila, int columna) const {
	return celdas[fila][columna];
}

void Tablero::poner_celda(int fila, int columna, const Celda& celda) {
	celdas[fila][columna] = celda;
}