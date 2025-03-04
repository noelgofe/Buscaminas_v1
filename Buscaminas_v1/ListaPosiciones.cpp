#include "ListaPosiciones.h"

ListaPosiciones::ListaPosiciones() {
	cont = 0;
}

void ListaPosiciones::destruye() {
	cont = 0;
}

void ListaPosiciones::insertar_final(int x, int y) {
	if (cont < MAX_LISTA) {
		lista[cont].posx = x;
		lista[cont].posy = y;
		cont++;
	}
}

int ListaPosiciones::longitud() {
	return cont;
}

int ListaPosiciones::dame_posX(int i) {
	return lista[i].posx;
}

int ListaPosiciones::dame_posY(int i) {
	return lista[i].posy;
}
