#include "InputOutput.h"
#include "ListaUndo.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main() {
	Juego juego;
	ListaPosiciones lista_pos, ultimoElem;
	ListaUndo lista_undo;
	int fila = 0, columna = 0;

	if (carga_juego(juego)) {
		mostrar_juego_consola(juego);
		while (!juego.esta_completo() and !juego.mina_explotada()) {
			pedir_pos(fila, columna);
			if (fila >= 0 and columna >= 0) {
				if (juego.esta_descubierta(fila, columna)) {
					cout << "La celda ya esta descubierta" << endl;
				}
				else if (juego.esta_marcada(fila, columna)) {
					cout << "La celda esta marcada" << endl;
				}
				else {
					juego.juega(fila, columna, lista_pos);
					system("CLS");
					mostrar_juego_consola(juego);
					lista_undo.insertar_final(lista_pos);
					lista_pos.destruye();
				}
			}

			else {
				if (fila == -1 and columna == -1) {
					cout << "Saliendo del juego" << endl;
					break;
				}
				else if (fila == -2 and columna == -2) {
					cout << "Dame una celda para marcar (o desmarcar en el caso en el que ya lo este)" << endl;
					pedir_pos(fila, columna);
					if (fila >= 0 and columna >= 0) {
						if (!juego.esta_descubierta(fila, columna)) {
							juego.marcar_desmarcar(fila, columna);
							mostrar_juego_consola(juego);
						}
						else {
							cout << "La celda ya esta descubierta" << endl;
						}
					}
				}
				else if (fila == -3 and columna == -3) {
					ultimoElem = lista_undo.ultimo_elemento();
					for (int i = 0; i < ultimoElem.longitud(); i++) {
						juego.ocultar(ultimoElem.dame_posX(i), ultimoElem.dame_posY(i));
					}
					cout << "Se retrocedio una jugada" << endl;
					mostrar_juego_consola(juego);
				}
				else {
					cout << "Instruccion invalida" << endl;
				}
			}
		}
	}

	mostrar_resultado(juego);

	return 0;
}