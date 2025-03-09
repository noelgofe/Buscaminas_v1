#include "InputOutput.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main() {
	Juego juego;
	ListaPosiciones lista_pos;
	int fila = 0, columna = 0;
	
	if (carga_juego(juego)) {
		mostrar_juego_consola(juego);
		while (!juego.esta_completo() and !juego.mina_explotada()) {
			pedir_pos(fila, columna);
			if(fila >= 0 and columna >= 0 ){
				if (juego.esta_descubierta(fila, columna)) {
					cout << "La celda ya está descubierta" << endl;
				}
				else if (juego.esta_marcada(fila, columna)) {
					cout << "La celda está marcada" << endl;
				}
				else {
					juego.juega(fila, columna, lista_pos);
					system("CLS");
					mostrar_juego_consola(juego);
				}
			}

			else {
				if (fila == -1 and columna == -1) {
					cout << "Saliendo del juego" << endl; // No funciona
					break;
				}
				else if (fila == -2 and columna == -2) {
					cout << "Dame una celda para marcar (o desmarcar en el caso en el que ya lo este)" << endl;
					pedir_pos(fila, columna);
					if (fila >= 0 and columna >= 0) {
						if (juego.esta_descubierta(fila, columna)) {
							cout << "La celda ya esta descubierta" << endl;
						}
						else {
							juego.marcar_desmarcar(fila, columna);
							mostrar_juego_consola(juego);
						}
						mostrar_juego_consola(juego);
					}
				}
				else if (fila == -3 and columna == -3) {
					//TODO: Implementar la funcion de undo
				}
			}
		}
	}

	mostrar_resultado(juego); //TODO: si lo terminas no se muestra si has ganado

	return 0;
}