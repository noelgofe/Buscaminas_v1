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
	return (estado == MINA);
}

bool Celda::contiene_numero() {
	return (estado == NUMERO);
}

bool Celda::esta_vacia() {
	return (estado == VACIA);
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
	estado = NUMERO;
	numero = n;
}

void Celda::marcar_celda() {
	marcada = true;
}

void Celda::desmarcar_celda() {
	marcada = false;
}