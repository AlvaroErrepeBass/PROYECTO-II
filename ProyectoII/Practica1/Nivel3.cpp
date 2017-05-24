#include "Nivel3.h"
#include "Huella.h"

Nivel3::Nivel3(juegoPG*jug, std::string map, std::string objetos, Punto posRec, Punto posCaz, std::string act, bool firstT) : Nivel1(jug, map, objetos, posRec, posCaz, act, firstT)
{
	level = "Nivel3";
	firsTime = true;
	change = false;
	visible = true;

	cargaTriggers();
	cargaObj(objetos);
	animNieve1.w = animNieve1.h = animNieve2.w = animNieve2.h = 0;
	static_cast<Huella*>(pCazador->dameComponente("Huella"))->swAble();
	static_cast<Huella*>(pRecolector->dameComponente("Huella"))->swAble();

	huellasCamino.resize(0);
}

void Nivel3::cargaTriggers(){
	vecTriggers.resize(0);
}

Nivel3::~Nivel3()
{
}
void Nivel3::update(){
	Nivel1::update();
	if (change){
		saveFile();
		std::ofstream f;
		f.open(pJuego->getPath() + "\\Galiakberova\\partidaGuardada\\infoTriggers.txt");
		f.close();
		Nivel1::fadeOut(40);
		EstadoJuego* borrar = pJuego->estados.top();
		pJuego->estados.pop();
		Punto rec; rec.x = 0; rec.y = 0; Punto caz; caz.x = 6925; caz.y = 10260;
		//CAMBIAR AL NIVEL SIGUIENTE
		//pJuego->estados.push(new Tutorial2(pJuego, "../docs/mapa1.txt", "../docs/objetosTutorial.txt", rec, caz));
		delete borrar;
	}
}
void Nivel3::callback(){
	change = true;

}