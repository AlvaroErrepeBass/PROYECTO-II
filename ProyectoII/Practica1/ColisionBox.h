#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
class ColisionBox :
	public Componente
{
public:
	ColisionBox(ObjetoJuego* ent);
	ColisionBox(ObjetoJuego* ent, SDL_Rect const & newRect, bool mov);
	virtual ~ColisionBox();
	//Atributos--------------------------------------
	
	//Metodos----------------------------------------
	virtual void update();
	virtual void draw();
	virtual void setMovible(bool mov){ movible = mov; }
	virtual bool getMovible(){ return movible; }
	virtual SDL_Rect getRectBox(){ return boxRect; }
private:
	//Atributos-------------------------------------------------------
	bool movible;
	ObjetoPG* pObj;
	SDL_Rect boxRect;
};

