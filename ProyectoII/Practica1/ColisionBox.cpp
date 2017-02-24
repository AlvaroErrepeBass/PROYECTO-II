#include "ColisionBox.h"


ColisionBox::ColisionBox(ObjetoJuego* ent) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(ent);
	movible = true;
	boxRect.x = pObj->getRect().x +15;
	boxRect.y = pObj->getRect().y + pObj->getRect().h *0.8;
	boxRect.w = pObj->getRect().w*0.4;
	boxRect.h = pObj->getRect().h *0.2;
}
ColisionBox::ColisionBox(ObjetoJuego* ent, SDL_Rect const & newRect, bool mov): Componente(ent){
	pObj = dynamic_cast<ObjetoPG*>(ent);
	boxRect = newRect;
	movible = mov;
}


ColisionBox::~ColisionBox()
{
}
//M�todo que calcula si alguno de los triangulos del vector de triangulos est� colisionando con la posicion a la que nos queremos mover.
bool ColisionBox::isColiding(Punto const & P){
	bool col = false;
	Punto p; p.x = P.x + pObj->getColisionBox().x; p.y = P.y + pObj->getColisionBox().y; //Posici�n de colisionBox + la posici�n a la que nos queremos mover.
	ObjetoPG* ob;
	int i = 0;
	while (i < static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->getVectObj().size() && !col){
		ob = dynamic_cast<ObjetoPG*>(static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->getVectObj()[i]);
		if (ob != pObj){
			if ((ob->getColisionBox().x + ob->getColisionBox().w) < p.x || ob->getColisionBox().x > (p.x + pObj->getColisionBox().w)) col = false;
			else if ((ob->getColisionBox().y + ob->getColisionBox().h) < p.y || ob->getColisionBox().y > (p.y + pObj->getColisionBox().h)) col = false;
			else col = true;
		}
		i++;
	}
	//Comprueba la colision con los bordes
	i = 0;
	if (!col){
		while (i < static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->getVectBordes().size() && !col){
			col = inTriangle(static_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->getVectBordes()[i], p);
			i++;
		}//fin colision con bordes
	}
	return col;
}
//Este m�todo calcula si un punto dado se encuentra dentro del �rea del triangulo.
//Para saber si el punto est� en el �rea: 
/*Calcular la orientaci�n de los tri�ngulos que forma el punto P con los v�rtices del tri�ngulo A1A2A3.

(1)Se calcula la orientaci�n de los tri�ngulos A1A2P, A2A3P, A3A1P.
En el caso de que la orientaci�n del tri�ngulo A1A2A3 sea positiva:
Si las orientaciones de los tres tri�ngulos que tienen como v�rtice el punto P, son positivas el punto est� dentro del tri�ngulo.
En caso contrario el punto est� situado fuera del tri�ngulo

En el caso de que la orientaci�n del tri�ngulo A1A2A3 sea negativa :
Si las orientaciones de los tres tri�ngulos que tri�ngulos que tienen como v�rtice el punto P son negativas, el punto est� dentro del tri�ngulo
En caso contrario el punto est� situado fuera del tri�ngulo.*/

bool ColisionBox::inTriangle(TrianguloBorde tr, Punto const & P){
	int x = triangleOrientation(tr);
	TrianguloBorde auxT;
	if (x >= 0){// Orientaci�n positiva
		auxT.A = tr.A; auxT.B = tr.B; auxT.C = P;
		if (triangleOrientation(auxT) >= 0){
			auxT.A = tr.A; auxT.B = P; auxT.C = tr.C;
			if (triangleOrientation(auxT) >= 0){
				auxT.A = P; auxT.B = tr.B; auxT.C = tr.C;
				if (triangleOrientation(auxT) >= 0){
					return true;
				}
				else return false;
			}
			else return false;
		}
		else return false;

	}
	else {//Orientaci�n negativa
		auxT.A = tr.A; auxT.B = tr.B; auxT.C = P;
		if (triangleOrientation(auxT) < 0){
			auxT.A = tr.A; auxT.B = P; auxT.C = tr.C;
			if (triangleOrientation(auxT) < 0){
				auxT.A = P; auxT.B = tr.B; auxT.C = tr.C;
				if (triangleOrientation(auxT) < 0){
					return true;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
}
//M�todo que calcula la orientaci�n de un triangulo con la f�rmula: (A1.x - A3.x) * (A2.y - A3.y) - (A1.y - A3.y) * (A2.x - A3.x)
//Siendo A1A2A3 el tri�ngulo.
//Si el resultado es mayor o igual que 0, la orientaci�n del tri�ngulo ser� positiva.En caso contrario, la orientaci�n del tri�ngulo ser� negativa.
int ColisionBox::triangleOrientation(TrianguloBorde const & tr){
	TrianguloBorde s;
	return ((tr.A.x - tr.C.x)*(tr.B.y - tr.C.y) - (tr.A.y - tr.C.y)*(tr.B.x - tr.C.x));
}
void ColisionBox::update(){
	boxRect.x = pObj->getRect().x +15;
	boxRect.y = pObj->getRect().y + pObj->getRect().h *0.8;

	if (movible){
		mapX = pObj->getmapX() + 15;
		mapY = pObj->getmapY() + pObj->getRect().h *0.8;
	}
}
void ColisionBox::draw(){ //BORRAR CUANDO NO SEA NECESARIO VER EL BOX COLLIDER;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//std::cout << "Dibujado";
	pObj->getPJuego()->getTextura(TCColision)->draw(pObj->getPJuego()->getRender(), boxRect);
}