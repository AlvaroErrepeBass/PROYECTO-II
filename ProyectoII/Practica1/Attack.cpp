#include "Attack.h"
#include "ColisionBox.h"

Attack::Attack(ObjetoJuego* entidad) :Componente(entidad)
{
	posicion = { 0, 0 };
	enemigo = dynamic_cast<Enemigo*>(pEntidad);
}


Attack::~Attack()
{
}

void Attack::update(){
	posicion = { (int)(enemigo->getColisionBox().x + enemigo->getColisionBox().w * 0.8) , (enemigo->getColisionBox().y) };
	
	//static_cast<ColisionBox*>(static_cast<Enemigo*>(pEntidad)->dameComponente("ColisionBox"))->isColiding(posicion, info);
	
	if (enemigo->getTarget() != nullptr){
		if (posicion.compruebaRadio(enemigo->getTarget()->getColisionBox(), 35)){

			//Hace la animaci�n
			//El jugador deber� tener algo que lo haga inmune a da�o un ratele despu�s de recibir un ataques
			std::string nombrefacha = enemigo->getTarget()->nombre;
			enemigo->getPJuego()->cambiaVida(-enemigo->damage);
			std::cout << "\n\n\nLa vida de " << nombrefacha << " ha disminuido " << enemigo->damage << " puntos de salud.\n\n";
		}
	}
	
}