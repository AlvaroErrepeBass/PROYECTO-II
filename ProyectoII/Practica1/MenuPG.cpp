#include "MenuPG.h"


MenuPG::MenuPG(juegoPG*jug, int puntos) :EstadoPG(jug, puntos)
{
   //Screen dimension 640 x 480
	et = TMenu;
	play = new Boton(pJuego, 192, 290, TBotonJ,jugar);
	vecObj.push_back(play);
	exit = new Boton(pJuego, 192, 190, TBotonS, salir);
	vecObj.push_back(exit);
	cargarAudio("../sounds/reverb/standrews.wav");
	cargarAssetsAudio("../docs/fxNivel1.txt", 'f');
	cargarAssetsAudio("../docs/mNivel1.txt", 'm');
	reproduceFx("balloon", -100, 0, 0);
}


MenuPG::~MenuPG()
{
	for (unsigned int i = 0; i < vecObj.size(); i++)
		delete vecObj[i];
	vecObj.clear();
}
