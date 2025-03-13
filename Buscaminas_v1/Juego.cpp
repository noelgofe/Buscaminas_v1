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

int Juego::dame_num_jugadas() const {
	return num_jugadas;
}

int Juego::dame_num_filas() const {
	return tablero.num_filas();
}

int Juego::dame_num_columnas() const {
	return tablero.num_columnas();
}

int Juego::dame_num_minas() const {
	int cont = 0;
	for (int i = 0; i < MAX_FILS; i++) {
		for (int j = 0; j < MAX_COLS; j++) {
			if (tablero.dame_celda(i, j).contiene_mina()) {
				cont++;
			}
		}
	}
	return cont;
}

bool Juego::contiene_mina(int fila, int columna) const {
	return tablero.dame_celda(fila, columna).contiene_mina();
}

bool Juego::esta_completo() const {
	bool completo = true;
	int i = 0, j = 0;
	while (completo and i < tablero.num_filas()) {
		while (completo and j < tablero.num_columnas()) {
			if (!tablero.dame_celda(i, j).contiene_mina() && !tablero.dame_celda(i, j).esta_descubierta()) completo = false;
			else j++;
		}
		if (completo) {
			i++;
			j = 0;
		}
	}
	return completo;
}

bool Juego::mina_explotada() const {
	bool explotada = false;
	int i = 0, j = 0;
	while (!explotada and i < tablero.num_filas()) {
		while (!explotada and j < tablero.num_columnas()) {
			if (tablero.dame_celda(i, j).contiene_mina() and tablero.dame_celda(i, j).esta_descubierta()) explotada = true;
			else j++;
		}
		if(!explotada){
			i++;
			j = 0;
		}
	}
	return explotada;
}

bool Juego::esta_descubierta(int fila, int columna) const {
	return tablero.dame_celda(fila, columna).esta_descubierta();
}

bool Juego::esta_marcada(int fila, int columna) const {
	return tablero.dame_celda(fila, columna).esta_marcada();
}

bool Juego::esta_vacia(int fila, int columna) const {
	return tablero.dame_celda(fila, columna).esta_vacia();
}

bool Juego::contiene_numero(int fila, int columna) const {
	return tablero.dame_celda(fila, columna).contiene_numero();
}

int Juego::dame_numero(int fila, int columna) const {
	return tablero.dame_celda(fila, columna).dame_numero();
}

void Juego::poner_mina(int fila, int columna) {
	if (tablero.es_valida(fila, columna)) {
		Celda celdaTemp = tablero.dame_celda(fila, columna);
		if (!celdaTemp.esta_descubierta() and !celdaTemp.contiene_mina()) {
			celdaTemp.poner_mina();
			tablero.poner_celda(fila, columna, celdaTemp);

			for (int i = -1; i <= 1; ++i) {
				for (int j = -1; j <= 1; ++j) {
					if (tablero.es_valida(fila + i, columna + j) and !(i == 0 and j == 0)) {		//Sumar +1 a las vecinas
						Celda celdaVecina = tablero.dame_celda(fila + i, columna + j);
						if (!celdaVecina.contiene_mina()) {											//si contiene mina no se le suma 1
							celdaVecina.poner_numero(celdaVecina.dame_numero() + 1);
							tablero.poner_celda(fila + i, columna + j, celdaVecina);
						}
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
		tablero.poner_celda(fila, columna, celdaTemp);
	}
}

void Juego::ocultar(int fila, int columna) {
	Celda celdaTemp = tablero.dame_celda(fila, columna);
	if (tablero.es_valida(fila, columna)) {
		if (celdaTemp.esta_descubierta()) {
			celdaTemp.ocultar_celda();
			tablero.poner_celda(fila, columna, celdaTemp);
		}
	}
}

void Juego::juega(int fila, int columna, ListaPosiciones& lista_pos) {
	if (tablero.es_valida(fila, columna)) {
		Celda celdaDescubrir = tablero.dame_celda(fila, columna);
		if (!celdaDescubrir.esta_descubierta() and !celdaDescubrir.esta_marcada()) {
			celdaDescubrir.descubrir_celda();
			tablero.poner_celda(fila, columna, celdaDescubrir);

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
							tablero.poner_celda(nuevaFila, nuevaColumna, celdaVecina);

							if (lista_pos.longitud() < MAX_LISTA) {
								lista_pos.insertar_final(nuevaFila, nuevaColumna);
							}
						}
					}
				}
			}
		}
	}
}