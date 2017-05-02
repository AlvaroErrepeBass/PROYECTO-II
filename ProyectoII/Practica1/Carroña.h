#pragma once
#include "ObjetoPG.h"
#include "ColisionBox.h"
class Carro�a :
	public ObjetoPG
{
public:
	Carro�a(juegoPG * juego, int px, int py);
	virtual ~Carro�a();
	virtual void draw();
	virtual  SDL_Rect getColisionBox() { return static_cast<ColisionBox*> (mapaComponentes.at("ColisionBox"))->getRectBox(); }
};

