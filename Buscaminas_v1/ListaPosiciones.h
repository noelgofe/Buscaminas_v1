#pragma once

const int MAX_LISTA = 50;

class ListaPosiciones {
private:
	typedef struct {
		int posx;
		int posy;
	} Posicion;
	int cont;
	Posicion lista[MAX_LISTA];
public:
	ListaPosiciones();
	void destruye();
	void insertar_final(int x, int y);
	int longitud();
	int dame_posX(int i);
	int dame_posY(int i);
};

