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
private:
	
	int framerate = 0;
	Punto nextPos; 
	//Funciones----------------------------------------------------------------------
	bool isColiding(Punto const & P);
	bool inTriangle(TrianguloBorde  tr, Punto const & P); //Calcula si un punto est� dentro del triangulo.
	int triangleOrientation(TrianguloBorde const &tr);
};

