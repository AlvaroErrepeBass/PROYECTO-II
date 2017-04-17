#include "Nivel1.h"
#include "PremioPG.h"
#include "SDL_mixer.h"
#include "GameOver.h"
#include "Arbol.h"
#include <algorithm>
#include "Pausa.h"
#include "Cebo.h"
#include "Cuerda.h"
#include "Enredadera.h"
#include "Hueso.h"
#include "Madera.h"
#include "Piedra.h"
#include "TextCb.h"
#include "Trigger.h"
#include "TrampaCerrada.h"
#include "Yesca.h"
#include "MCrafteo.h"
#include "Lobo.h"
#include "follow.h""
#include "TrampaAbierta.h"
#include "Equipo.h"

Nivel1::Nivel1(juegoPG*jug) : EstadoPG(jug, 0){
	mapa = new GrafoMapa();

	camara.x = camara.y = 0;
	camara.h = pJuego->getScreenHeight(); camara.w = pJuego->getScreenWidth();
	animNieve1.h = animNieve2.h = camara.h+1000; animNieve1.w = animNieve2.w = camara.w+1000;
	animNieve1.x = animNieve2.x = camara.w;
	animNieve1.y = animNieve2.y = camara.h;

	pCazador = new Cazador(pJuego, camara.x + (camara.w / 2), camara.y + (camara.h / 2));
	vecObj.push_back(pCazador);
	pRecolector = new Recolector(pJuego, camara.x + (camara.w / 2) - 300, camara.y + (camara.h / 2));
	vecObj.push_back(pRecolector);

	Trigger *auxTr; auxTr = new Trigger (pJuego, 562, 384, pCazador, pRecolector);
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/dialogo1.txt"));
	vecTriggers.push_back(auxTr);

	auxTr = new Trigger(pJuego, 662, 384, pCazador, pRecolector);
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/dialogo2.txt"));
	vecTriggers.push_back(auxTr);

	auxTr = new Trigger(pJuego, 865, 70, pCazador, pRecolector);
	auxTr->setCallback(new TextCb(auxTr, "../docs/textos/dialogo3.txt"));
	auxTr->setTriggerDim(80, 80);
	vecTriggers.push_back(auxTr);


	vecObj.push_back(new Arbol(pJuego, 180, 60));
	vecObj.push_back(new Arbol(pJuego, 480, 260));
	vecObj.push_back(new Arbol(pJuego, 680, 60));
	vecObj.push_back(new Arbol(pJuego, 750, 365));
	vecObj.push_back(new Arbol(pJuego, 1080, 195));
	vecObj.push_back(new Arbol(pJuego, 480, 60));

	vecObj.push_back(new Cebo(pJuego, 780, 100));
	vecObj.push_back(new Cuerda(pJuego, 880, 100));
	vecObj.push_back(new Enredadera(pJuego, 980, 100));
	vecObj.push_back(new Hueso(pJuego, 880, 200));
	vecObj.push_back(new Madera(pJuego, 880, 300));
	vecObj.push_back(new Piedra(pJuego, 980, 200));
	vecObj.push_back(new TrampaCerrada(pJuego, 980, 300));
	vecObj.push_back(new Yesca(pJuego, 1080, 100));
	vecObj.push_back(new TrampaAbierta(pJuego, 1200, 400));

	cargarAudio("../sounds/reverb/standrews.wav");
	cargarAssetsAudio("../docs/fxNivel1.txt", 'f');
	cargarAssetsAudio("../docs/mNivel1.txt", 'm');
	reproduceFx("balloon", -100, 0, 0);
	//reproduceMusica("music", false);

	activePlayer = "C";

	vecObj.push_back(new Lobo(pJuego, pCazador ,pRecolector, 250, 200));
	
	pCazador->newComponente(new Equipo(pCazador, static_cast<Mochila*>(pRecolector->dameComponente("Mochila"))), "Equipo");
	pRecolector->newComponente(new Equipo(pCazador, static_cast<Mochila*>(pRecolector->dameComponente("Mochila"))), "Equipo");
	pRecolector->newComponente(new follow(pRecolector, pCazador, mapa, true), "follow");

}
bool ordena(ObjetoJuego*p1, ObjetoJuego*p2){
	return(dynamic_cast<ObjetoPG*>(p1)->getColisionBox().y < dynamic_cast<ObjetoPG*>(p2)->getColisionBox().y);
}
void Nivel1::draw(){
	SDL_Rect aux;
	Tile tile;
	//No se si esto iria mejor en el update (??????????????????)
	if (pJuego->input.sw) swPlayer();
	else{
		for (unsigned int i = 0; i < vecTile.size(); i++){
			vecTile[i].x -= camara.x; vecTile[i].y -= camara.y;
			tile = vecTile[i];
			aux.x = tile.x; aux.y = tile.y; aux.w = 122; aux.h = 83;
			pJuego->getTextura(TTileSet)->draw(pJuego->getRender(), tile.rectTileset, aux);
		}
		for (unsigned int i = 0; i < vectBordes.size(); i++){
			vectBordes[i].A.x -= camara.x;
			vectBordes[i].A.y -= camara.y;
			vectBordes[i].B.x -= camara.x;
			vectBordes[i].B.y -= camara.y;
			vectBordes[i].C.x -= camara.x;
			vectBordes[i].C.y -= camara.y;
		}
		std::sort(vecObj.begin(), vecObj.end(), ordena);
		for (ObjetoJuego* ob : vecObj) ob->draw();
		for (ObjetoJuego* trg : vecTriggers) trg->draw();//TIENE QUE SER LO ULTIMO EN DIBUJARSE
	}

	setCamara(0,0); //Se reinicia el offset a 0
	int x = rand() % 100;
	if (x >= 60){
		animNieve1.x--;
		animNieve1.y--;
	}
	if (animNieve1.x <= 0) 
		animNieve1.x = camara.w;
	if (animNieve1.y <= 0) 
		animNieve1.y = camara.h;
	
	if (x >= 70){
		animNieve2.x--;
		animNieve2.y--;
	}
	if (animNieve2.x <= 0) 
		animNieve2.x = camara.w;
	if (animNieve2.y <= 0) 
		animNieve2.y = camara.h;

	pJuego->getTextura(TNieve1)->draw(pJuego->getRender(), animNieve1, camara);
	pJuego->getTextura(TNieve2)->draw(pJuego->getRender(), animNieve2, camara);

	pJuego->getTextura(TLuz)->draw(pJuego->getRender(),pJuego->getNieblaRect() ,camara);
}
void Nivel1::swPlayer(){
	SDL_Rect aux;
	Tile tile;
	if (activePlayer == "C"){
		pCazador->swAble();
		camara.x = -1*(pCazador->getRect().x - pRecolector->getRect().x);
		camara.y = -1*(pCazador->getRect().y - pRecolector->getRect().y);
		activePlayer = "R";
	}
	else if (activePlayer == "R") {
		pRecolector->swAble();
		camara.x = -1*(pRecolector->getRect().x - pCazador->getRect().x);
		camara.y = -1*(pRecolector->getRect().y - pCazador->getRect().y);
		activePlayer = "C";
	}
	for (unsigned int i = 0; i < vecTile.size(); i++){
		vecTile[i].x -= camara.x; vecTile[i].y -= camara.y;
		tile = vecTile[i];
		aux.x = tile.x; aux.y = tile.y; aux.w = 122; aux.h = 83;
		pJuego->getTextura(TTileSet)->draw(pJuego->getRender(), tile.rectTileset, aux);
	}
		
	for (unsigned int i = 0; i < vectBordes.size(); i++){
		vectBordes[i].A.x -= camara.x;
		vectBordes[i].A.y -= camara.y;
		vectBordes[i].B.x -= camara.x;
		vectBordes[i].B.y -= camara.y;
		vectBordes[i].C.x -= camara.x;
		vectBordes[i].C.y -= camara.y;
	}
	std::sort(vecObj.begin(), vecObj.end(), ordena);
	for (ObjetoJuego* ob : vecObj){
		ob->draw();
	}
	for (ObjetoJuego* ob : vecTriggers){ //TIENE QUE SER LO ULTIMO EN DIBUJARSE
		ob->draw();
	}
	
	if (activePlayer == "C") pCazador->swAble();
	else pRecolector->swAble();

}

void Nivel1::onKeyUp(char k) {
	switch (k) {
	case 'q':
		pJuego->estados.push(new MCrafteo(pJuego, contPuntos, static_cast<Mochila*>(pRecolector->dameComponente("Mochila"))));
		break;
	case 's':
		pJuego->estados.push(new Pausa(pJuego,contPuntos));
		break;
	default:
		break;
	}
}

Nivel1::~Nivel1()
{
}

