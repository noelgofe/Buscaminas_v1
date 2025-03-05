#include "Juego.h"

Juego::Juego() {
	num_jugadas = 0;
	num_minas = 0;
	num_descubiertas = 0;
	mina_pisada = false;
	tablero;
}

Juego::Juego(int fils, int cols) {
	num_jugadas = 0;
	num_minas = 0;
	num_descubiertas = 0;
	mina_pisada = false;
	Tablero temp(fils, cols);
	tablero = temp;
}

void Juego::destruye() {
	num_jugadas = 0;
	num_minas = 0;
	num_descubiertas = 0;
	mina_pisada = false;
	tablero.destruye();
}

int Juego::dame_num_jugadas() {
	return num_jugadas;
}

int Juego::dame_num_filas() {
	return tablero.num_filas();
}

int Juego::dame_num_columnas() {
	return tablero.num_columnas();
}

int Juego::dame_num_minas() {
	int cont = 0;
	Celda celdaTemp;
	for (int i = 0; i < MAX_FILS; i++) {
		for (int j = 0; j < MAX_COLS; j++) {
			celdaTemp = tablero.dame_celda(i, j);
			if (celdaTemp.contiene_mina()) {
				cont++;
			}
		}
	}
	return cont;
}

bool Juego::contiene_mina(int fila, int columna) {
	bool mina = false;
	Celda celdaTemp = tablero.dame_celda(fila, columna);
	if (celdaTemp.contiene_mina()) mina = true;
	return mina;
}

bool Juego::esta_completo() {
	bool completo = false;
	Celda celdaTemp;
	int i = 0, j = 0;
	while (completo and i < MAX_FILS) {
		while (completo and j < MAX_COLS) {
			celdaTemp = tablero.dame_celda(i, j);
			if (celdaTemp.contiene_mina() and !celdaTemp.esta_descubierta()) completo = true;
			else {
				i++;
				j++;
			}
		}
	}
	return completo;
}

bool Juego::mina_explotada() {
	bool explotada = false;
	Celda celdaTemp;
	int i = 0, j = 0;
	while (!explotada and i < MAX_FILS) {
		while (!explotada and j < MAX_COLS) {
			celdaTemp = tablero.dame_celda(i, j);
			if (celdaTemp.contiene_mina() and celdaTemp.esta_descubierta()) explotada = true;
			else {
				i++;
				j++;
			}
		}
	}
	return explotada;
}

bool Juego::esta_descubierta(int fila, int columna) {
	bool descubierta = false;
	Celda celdaTemp = tablero.dame_celda(fila, columna);
	if (celdaTemp.esta_descubierta()) descubierta = true;
	return descubierta;
}

bool Juego::esta_marcada(int fila, int columna) {
	bool marcada = false;
	Celda celdaTemp = tablero.dame_celda(fila, columna);
	if (celdaTemp.esta_marcada()) marcada = true;
	return marcada;
}

bool Juego::esta_vacia(int fila, int columna) {
	bool vacia = false;
	Celda celdaTemp = tablero.dame_celda(fila, columna);
	if (celdaTemp.esta_vacia()) vacia = true;
	return vacia;
}

bool Juego::contiene_numero(int fila, int columna) {
	return tablero.dame_celda(fila, columna).contiene_numero();
}

int Juego::dame_numero(int fila, int columna) {
	Celda celdaTemp = tablero.dame_celda(fila, columna);
	return celdaTemp.dame_numero();
}

void Juego::poner_mina(int fila, int columna) {
	if (tablero.es_valida(fila, columna)) {
		Celda celdaTemp = tablero.dame_celda(fila, columna); //referencia de la que se pone mina
		if (!celdaTemp.contiene_mina()) { // añadir !celdaTemp.esta_descubierta()
			celdaTemp.poner_mina();
			tablero.poner_celda(fila, columna, celdaTemp);
			
			//Es el unico caso en el que se pone numero
			for (int i = -1; i <= 1; ++i) {
				for (int j = -1; j <= 1; ++j) {
					if (tablero.es_valida(fila + i, columna + j) and !(i == 0 and j == 0)) {
						//Sumar +1 a las vecinas
						Celda celdaVecina = tablero.dame_celda(fila + i, columna + j); //Sacamos celda del tablero
						celdaVecina.poner_numero(celdaVecina.dame_numero() + 1);
						tablero.poner_celda(fila + i, columna + j, celdaVecina); //guardamos la celda en el tablero
					}
				}
			}
		}
	}
}

void Juego::marcar_desmarcar(int fila, int columna) {
	if (tablero.es_valida(fila, columna)) {
		Celda celdaTemp = tablero.dame_celda(fila, columna);
		if (!celdaTemp.esta_descubierta()) {
			if (celdaTemp.esta_marcada()) celdaTemp.desmarcar_celda();
			else celdaTemp.marcar_celda();
		}
	}
}

void Juego::ocultar(int fila, int columna) {
	if (tablero.es_valida(fila, columna)) {
		Celda celdaTemp = tablero.dame_celda(fila, columna);
		if (celdaTemp.esta_descubierta()) {
			celdaTemp.descubrir_celda();
		}
	}
}

void Juego::juega(int fila, int columna, ListaPosiciones lista_pos) {
	if (tablero.es_valida(fila, columna)) {
		Celda celdaDescubrir = tablero.dame_celda(fila, columna);
		if (!celdaDescubrir.esta_descubierta() and !celdaDescubrir.esta_marcada()) {
			celdaDescubrir.descubrir_celda();

			if (lista_pos.longitud() < MAX_LISTA) {
				lista_pos.insertar_final(fila, columna);
			}

			if (!celdaDescubrir.contiene_mina() and !celdaDescubrir.contiene_numero()) {
				for (int i = -1; i <= 1; ++i) {
					for (int j = -1; j <= 1; ++j) {
						int nuevaFila = fila + i;
						int nuevaColumna = columna + j;
						if (tablero.es_valida(nuevaFila, nuevaColumna) && !(i == 0 && j == 0)) {
							Celda celdaVecina = tablero.dame_celda(nuevaFila, nuevaColumna);
							celdaVecina.descubrir_celda();
						}
					}
				}
			}
		}
	}
}

