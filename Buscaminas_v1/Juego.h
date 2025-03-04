#pragma once
#include "Tablero.h"
#include "ListaPosiciones.h"

class Juego {
private:
	Tablero tablero;
	int num_jugadas;
	bool mina_pisada;
	int num_minas;
	int num_descubiertas;

public:
	Juego();
	Juego(int fils, int cols);
	void destruye();
	int dame_num_jugadas();
	int dame_num_filas();
	int dame_num_columnas();
	int dame_num_minas();
	bool contiene_mina(int fila, int columna);
	bool esta_completo();
	bool mina_explotada();
	bool esta_descubierta(int fila, int columna);
	bool esta_marcada(int fila, int columna);
	bool esta_vacia(int fila, int columna);
	bool contiene_numero(int fila, int columna);
	int dame_numero(int fila, int columna);
	void poner_mina(int fila, int columna);
	void marcar_desmarcar(int fila, int columna);
	void ocultar(int fila, int columna);
	void juega(int fila, int columna, ListaPosiciones lista_pos);
};