#pragma once
#include "EstadoPG.h"
#include "Mochila.h"

class MCrafteo: public EstadoPG
{
	struct coords {
		std::string name; int x; int y;
	};
public:
	MCrafteo(juegoPG*jug, int puntos, Mochila* m);
	virtual ~MCrafteo();

	void draw();
	void update() {};
	void onKeyUp(char k);

	void animacionS();
	void animacionA();

	void comprobar(std::vector<coords> const& v);

private:
	SDL_Rect pag1, pag2, sombra, rFondo, ni�os, recuadros, font;
	TexturasSDL * fondo;
	SDL_Color fuente;
	int numPag, aux, acuD, acuI;

	bool derecha, izquierda, flag;
	
	Mochila* mochila;
	std::vector<coords> equipables;
	std::vector<coords> materiales;
};

