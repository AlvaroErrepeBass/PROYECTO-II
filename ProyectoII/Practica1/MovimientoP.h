#pragma once
#include "Componente.h"
#include "ObjetoPG.h"
class MovimientoP :
	public Componente
{
public:
	MovimientoP(ObjetoJuego* ent);
	virtual ~MovimientoP();

	//M�todos--------------------------------------------------
	virtual void update();

	ObjetoPG *pObj;
};

