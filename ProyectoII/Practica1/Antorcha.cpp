#include "Antorcha.h"


Antorcha::Antorcha(ObjetoJuego* ent, Nivel1* nivel) : Componente(ent)
{
	pObj = dynamic_cast<ObjetoPG*>(ent);
	time = 2000;
	alpha = 125;
	contFrames = 0;
	level = nivel;
	level->setAlpha(100);
	able = false;
}


Antorcha::~Antorcha()
{
}
void Antorcha::update(){
	if (able){
		contFrames++;
		if(contFrames%18 == 0 && alpha <255) alpha++;
		level->setAlpha(alpha);
	}
	if (contFrames >= time){
		level->dropTorch();
		swAble();
	}
	if (!able && pObj->getPJuego()->input.abajo){
		level->getTorch();
		swAble();
	}
}
void Antorcha::swAble(){
	if (able){
		contFrames = 0;
		level->setAlpha(255);
		alpha = 125;
		able = false;
	}
	else{
		able = true;
		level->setAlpha(alpha);
	}
}
void Antorcha::draw(){
	if (able) pObj->getPJuego()->getTextura(TAntorcha)->draw(pObj->getPJuego()->getRender(), level->getCamara());
}