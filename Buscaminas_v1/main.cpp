#include "InputOutput.h"

using namespace std;

int main() {
	Juego juego;
	int fila = 0, columna = 0;
	
	if (carga_juego(juego)) {
		mostrar_juego_consola(juego);
		while (!juego.esta_completo() and !juego.mina_explotada()) {
			pedir_pos(fila, columna);
			mostrar_juego_consola(juego);
		}
	}

	return 0;
}