#include "MovimientoP.h"
#include "EstadoPG.h"
#include "ColisionBox.h"


MovimientoP::MovimientoP(ObjetoJuego* ent) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(pEntidad);
	nextPos.x = nextPos.y = 0;
}


MovimientoP::~MovimientoP()
{
	
}

void MovimientoP::update(){
	//Antes de actualizar la posici�n comprobamos si colisiona con la posici�n siguiente.

	if(framerate % 16 == 0) // se mueve 1 frame cada 16 ms x 16ms
		pObj->changeAnimH();

	framerate++;
	if (pObj->getPJuego()->input.dDS){ //Diagonal Arriba-Derecha
		nextPos.x = 2; nextPos.y = -1;
		if (!static_cast<ColisionBox*>( pObj->dameComponente("ColisionBox"))->isColiding(nextPos)){
			pObj->setRect(nextPos.x, nextPos.y);
			dynamic_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->setCamera(nextPos.x, nextPos.y);
			pObj->changeAnimV(7); // posiciona la 'j' de la matriz de la animacion
		}
	}
	else if (pObj->getPJuego()->input.dDI){//Diagonal Abajo-Derecha
		nextPos.x = 2; nextPos.y = 1;
		if (!static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->isColiding(nextPos)){
			pObj->setRect(nextPos.x, nextPos.y);
			dynamic_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->setCamera(nextPos.x, nextPos.y);
			pObj->changeAnimV(5);
		}

	}
	else if (pObj->getPJuego()->input.dII){//Diagonal Abajo-Izquierda
		nextPos.x = -2; nextPos.y = 1;
		if (!static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->isColiding(nextPos)){
			pObj->setRect(nextPos.x, nextPos.y);
			dynamic_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->setCamera(nextPos.x, nextPos.y);
			pObj->changeAnimV(4);
		}

	}
	else if (pObj->getPJuego()->input.dIS){//Diagonal Arriba-Izquierda
		nextPos.x = -2; nextPos.y = -1;
		if (!static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->isColiding(nextPos)){
			pObj->setRect(nextPos.x, nextPos.y);
			dynamic_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->setCamera(nextPos.x, nextPos.y);
			pObj->changeAnimV(6);
		}

	}
	else if (pObj->getPJuego()->input.arriba){
		nextPos.x = 0; nextPos.y = -2;
		if (!static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->isColiding(nextPos)){
			pObj->setRect(nextPos.x, nextPos.y);
			dynamic_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->setCamera(nextPos.x, nextPos.y);
			pObj->changeAnimV(3);
		}

	}
	else if (pObj->getPJuego()->input.derecha){
		bool o;
		nextPos.x = 2; nextPos.y = 0;
		if (!static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->isColiding(nextPos)){
			pObj->setRect(nextPos.x, nextPos.y);
			dynamic_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->setCamera(nextPos.x, nextPos.y);
			pObj->changeAnimV(2);
		}

	}
	else if (pObj->getPJuego()->input.abajo){
		nextPos.x = 0; nextPos.y = 2;
		if (!static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->isColiding(nextPos)){
			pObj->setRect(nextPos.x, nextPos.y);
			dynamic_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->setCamera(nextPos.x, nextPos.y);
			pObj->changeAnimV(0);
		}

	}
	else if (pObj->getPJuego()->input.izquierda){
		nextPos.x = -2; nextPos.y = 0;
		if (!static_cast<ColisionBox*>(pObj->dameComponente("ColisionBox"))->isColiding(nextPos)){
			pObj->setRect(nextPos.x, nextPos.y);
			dynamic_cast<EstadoPG*>(pObj->getPJuego()->estados.top())->setCamera(nextPos.x, nextPos.y);
			pObj->changeAnimV(1);
		}

	}
}
