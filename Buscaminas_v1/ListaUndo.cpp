#include "ListaUndo.h"

ListaUndo::ListaUndo() {
	for (int i = 0; i < MAX_UNDO; i++) {
		lista[i];
	}
	cont = 0;
}

void ListaUndo::destruye() {
	for (int i = 0; i < cont; i++) {
		lista[i].destruye();
	}
	cont = 0;
}

void ListaUndo::insertar_final(const ListaPosiciones& lista_pos) {
	if (cont == MAX_UNDO) {
		for (int i = 0; i < cont - 1; i++) {
			lista[i] = lista[i + 1];
		}
		lista[cont - 1] = lista_pos;
	}
	else {
		lista[cont] = lista_pos;
		cont++;
	}
}

ListaPosiciones ListaUndo::ultimo_elemento() const {
	cont--;									//solo se podria hacer un paso hacia atras sino
	return lista[cont];
}