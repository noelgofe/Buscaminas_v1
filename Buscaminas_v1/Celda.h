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
	int dame_numero() const;
	bool esta_descubierta() const;
	bool contiene_mina() const;
	bool contiene_numero() const;
	bool esta_vacia() const;
	bool esta_marcada() const;
	void descubrir_celda();
	void ocultar_celda();
	void poner_mina();
	void poner_numero(int n);
	void marcar_celda();
	void desmarcar_celda();
};