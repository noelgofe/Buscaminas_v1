#include "Celda.h"

Celda::Celda() {
	descubierta = true; // Default = false
	marcada = false;
	estado = VACIA;
	numero = 0;
}

void Celda::destruye() {
	descubierta = false;
	marcada = false;
	estado = VACIA;
	numero = 0;
}

int Celda::dame_numero() {
	return numero;
}

bool Celda::esta_descubierta() {
	return descubierta;
}

bool Celda::contiene_mina() {
	bool mina = false;
	if (estado == MINA) mina = true;
	return mina;
}

bool Celda::contiene_numero() {
	bool diferentede0 = false;
	if (numero == NUMERO) diferentede0 = true;
	return diferentede0;
}

bool Celda::esta_vacia() {
	bool vacia = false;
	if (estado == VACIA) vacia = true;
	return vacia;
}

bool Celda::esta_marcada() {
	return marcada;
}

void Celda::descubrir_celda() {
	descubierta = true;
}

void Celda::ocultar_celda() {
	descubierta = false;
}

void Celda::poner_mina() {
	estado = MINA;
}

void Celda::poner_numero(int n) {
	if (n != 0) estado = NUMERO;
	numero = n;
}

void Celda::marcar_celda() {
	marcada = true;
}

void Celda::desmarcar_celda() {
	marcada = false;
}