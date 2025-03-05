#include "InputOutput.h"
#include <iomanip>
#include <iostream>

using namespace std;

const char CHAR_MINA = '*';  // Mina

void mostrar_separador(Juego& juego);
void mostrar_celda(Juego& juego, int fila, int columna);
void color_numero(int numero);

void color_numero(int numero) {
    switch (numero) {
    case 1: cout << BLUE; break;
    case 2: cout << GREEN; break;
    case 3: cout << RED; break;
    case 4: cout << DBLUE; break;
    case 5: cout << DGREEN; break;
    case 6: cout << DRED; break;
    default:
        break;
    }
}

void mostrar_separador(Juego& juego) { //Funcion de ayuda para el mostrar_juego_consola
    cout << "\t -+";
    for (int col = 0; col < juego.dame_num_columnas(); ++col) {
        cout << setw(N_HUECOS + 1) << setfill('-') << '+' << setfill(' ');
    }
    cout << endl;
}

void mostrar_celda(Juego& juego, int fila, int columna) { //Funcion de ayuda para el mostrar_juego_consola
    if (!juego.esta_descubierta(fila, columna) && !juego.esta_marcada(fila, columna)) {
        cout << BG_GRAY << GRAY << N_HUECOS << setfill(' ') << ' ' << RESET;
    }
    else {
        cout << BG_BLACK << BLACK;
        if (!juego.esta_marcada(fila, columna)) {
            if (juego.contiene_mina(fila, columna)) {
                cout << RED << setw(N_HUECOS) << setfill(' ') << CHAR_MINA << RESET;
            }
            else {
                if (juego.esta_vacia(fila, columna)) {
                    cout << setw(N_HUECOS) << setfill(' ') << ' ' << RESET;
                }
                else {
                    if (juego.contiene_numero(fila, columna)) {
                        int numero = juego.dame_numero(fila, columna);
                        color_numero(numero);
                        cout << setw(N_HUECOS) << setfill(' ') << numero << RESET;
                    }
                    else {
                        cout << BG_RED << RED << setw(N_HUECOS) << setfill(' ') << ' ' << RESET;
                    }
                }
            }
        }
        else {
            cout << BG_ORANGE << ORANGE << setw(N_HUECOS) << setfill(' ') << ' ' << RESET;
        }
    }
}

istream& operator>>(istream& in, Juego& juego) {
    int filas, columnas;
    in >> filas >> columnas;
    int numMinas;
    in >> numMinas;

    juego = Juego(filas, columnas);
    int filaMina, columnaMina;
    for (int i = 0; i < numMinas; i++) {
        in >> filaMina >> columnaMina;
        juego.poner_mina(filaMina, columnaMina);
    }

    return in;
}

void mostrar_cabecera() {
    cout << "Buscaminas" << endl;
    cout << "----------" << endl;
}

void pedir_pos(int fila, int columna) {
    do {
        cout << "Introduce una fila: ";
        cin >> fila;
    } while (fila < -3 and fila > MAX_FILS);

    do {
        cout << "Introduce una columna: ";
        cin >> columna;
    } while (columna < -3 and columna > MAX_COLS);

    // TODO: hay que hacer para -1,-2 y -3
}

void mostrar_resultado(Juego& juego) {
    if (juego.esta_completo() and !juego.mina_explotada()) {
        cout << "Enhorabuena has ganado";
    }
    else if (juego.mina_explotada()) {
        cout << "Has pisado una mina, has perdido";
    }
}

void mostrar_juego_consola(Juego& juego) { // TODO: esto debería ser const Juego& juego

    // mostrar el número de jugadas del juego
    cout << "Llevas " << juego.dame_num_jugadas() << " jugadas" << endl;
    // mostrar cabecera
    mostrar_cabecera();

    cout << "\t  |";
    for (int col = 0; col < juego.dame_num_columnas(); col++) {
        cout << LBLUE << setw(N_HUECOS) << col << RESET << '|';
    }
    cout << endl;

    // mostrar separador
    mostrar_separador(juego);

    // mostrar tablero
    for (int f = 0; f < juego.dame_num_filas(); f++) {
        // mostrar numero de fila
        cout << "\t" << LBLUE << setw(2) << f << RESET << '|';
        // mostrar la fila
        for (int c = 0; c < juego.dame_num_columnas(); c++) {
            mostrar_celda(juego, f, c);
            cout << '|';
        }
        cout << endl;

        mostrar_separador(juego);
    }
    cout << endl;
}

bool carga_juego(Juego& juego) {
    bool carga;
    string nombreArchivo;
    cout << "Ingrese el nombre del fichero (con terminacion .txt): ";
    nombreArchivo = "test0.txt"; // cin >> nombreArchivo;
    cout << endl;

    ifstream archivo;
    archivo.open(nombreArchivo);
    carga = archivo.is_open();
    if (carga) {
        archivo >> juego;
    }
    else {
        cout << "Apertura incorrecta, no se encontro el archivo, asegurate de que esta en la carpeta correcta";
    }

    return carga;
}