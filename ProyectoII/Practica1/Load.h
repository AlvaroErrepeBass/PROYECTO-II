#pragma once
#include "Nivel1.h"

class Load
{
public:
	Load(Nivel1* n);
	~Load();

	void Cargar();

private:
	Nivel1* nivel;
};

