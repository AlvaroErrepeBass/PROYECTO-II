#pragma once
#include "ObjetoPG.h"
class Caba�aObj :
	public ObjetoPG
{
public:
	Caba�aObj(juegoPG * juego, int px, int py);
	~Caba�aObj();

	virtual void update();
	virtual void draw(); //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	bool compruebaRadio(SDL_Rect target);
	bool cazadorIn();
	bool recolectorIn();

private:
	bool saved;
};

