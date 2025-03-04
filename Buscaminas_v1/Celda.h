#pragma once

class Celda {
private:
	typedef enum { NUMERO, VACIA, MINA } Estado;
	bool descubierta;
	Estado estado;
	int numero;
	bool marcada;

public:
	Celda();
	void destruye();
	int dame_numero();
	bool esta_descubierta();
	bool contiene_mina();
	bool contiene_numero();
	bool esta_vacia();
	bool esta_marcada();
	void descubrir_celda();
	void ocultar_celda();
	void poner_mina();
	void poner_numero(int n);
	void marcar_celda();
	void desmarcar_celda();
};