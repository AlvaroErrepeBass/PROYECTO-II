#pragma once
#include "micropather.h"
#include "EstadoPG.h"

class GrafoMapa : public micropather::Graph
{
	std::vector<char> mapa;
	std::vector<int> niveles;
	int aux,nivelAct;
	micropather::MicroPather* pather;
public:
	GrafoMapa()
	{
		niveles.push_back(0);
		nivelAct = aux = 0;
		pather = new micropather::MicroPather(this, 20);	// Use a very small memory block to stress the pather
	}
	
	void solve(void* startState, void* endState, std::vector< void* >* path, float* totalCost)
	{
		pather->Solve(startState, endState, path, totalCost);
	}
	void creaMapa(char c)
	{
		switch (c)
		{
		case 's':
			mapa.push_back('s');
			aux++;
			break;
		case 't':
			mapa.push_back('t');
			aux++;
			break;
		case 'X':
			mapa.push_back('X');
			aux++;
			break;
		case 'L':
			niveles[nivelAct] = aux;
			niveles.push_back(0);
			nivelAct++;
			aux = 0;
			break;

		}
	}
	void actualizaMapa(std::vector<ObjetoJuego*> obj)
	{
		for (ObjetoJuego* o : obj)
		{
			if (static_cast<ObjetoPG*>(o)->encuentraComponente("ColisionBox")){

				SDL_Rect rec = static_cast<ObjetoPG*>(o)->getColisionBox();
				int cuadranteX = rec.x / 122;
				int cuadranteY = rec.y / 62;
				/* ver la posicion del objeto, teniendo en cuenta el offset de la camara:
					x/122 == cuadrante de x en el que esta
					y/62  == cuadrante de y en el que esta
					hallado este cuadrante siguen existiendo cinco posible posiciones finales
					El centro del cuadrante o cualquiera de sus esquinas que pertenecer�an a otro tile

					_____________
					|    / \    |
					|  /     \  |
					|  \     /  |
					|____\_/____|

					*/
				int Px, Py;
				Px = rec.x - cuadranteX * 122;
				Py = rec.y - cuadranteY * 62;
				// Dividimos el cudrante como si fueran 6 triangulos por comodidad si esta en alguno de los dos centrales a�adimos una X al mapa en la posicion del cuadrante
				if (((0 - Px)*(31 - Py) - (31 - Py)*(122 - Px) < 0) && ((122 - Px)*(0 - Py) - (31 - Py)*(61 - Px) < 0) && ((61 - Px)*(31 - Py) - (0 - Py)*(0 - Px) < 0)){
					int aux1 = 0;
					for (int i = 0; i < cuadranteY; i++)
					{
						aux1 += niveles[i];
					}
						mapa[aux1 + cuadranteX] = 'X';
				}
				else if(((0 - Px)*(31 - Py) - (31 - Py)*(122 - Px) < 0) && ((122 - Px)*(62 - Py) - (31 - Py)*(61 - Px) < 0) && ((61 - Px)*(31 - Py) - (62 - Py)*(0 - Px) < 0)){
					int aux1 = 0;
					for (int i = 0; i < cuadranteY; i++)
					{
						aux1 += niveles[i];
					}
						mapa[aux1 + cuadranteX] = 'X';
				}
				// Si la posicion del objeto no esta en ninguno de los dos triangulos centrales comprobamo su x y su y con el centro del cuadrante
				// Si ambas son mayores marcamos la casilla inferior derecha y asi sucesivamente
				else
				{
					int aux1 = 0;
					if (Px >= 61)
					{
						if (Py < 31)
						{
							for (int i = 0; i < cuadranteY - 1; i++)
							{
								aux1 += niveles[i];
							}
								mapa[aux1 + cuadranteX + 1] = 'X';
						}
						else
						{
							for (int i = 0; i < cuadranteY + 1; i++)
							{
								aux1 += niveles[i];
							}
								mapa[aux1 + cuadranteX + 1] = 'X';
						}
					}
					else
					{
						if (Py < 31)
						{
							for (int i = 0; i < cuadranteY - 1; i++)
							{
								aux1 += niveles[i];
							}
							mapa[aux1 + cuadranteX - 1] = 'X';
						}
						else
						{
							for (int i = 0; i < cuadranteY + 1; i++)
							{
								aux1 += niveles[i];
							}
							mapa[aux1 + cuadranteX - 1] = 'X';
						}
					}
				}
			}
		}
	}

	void NodeToXY(void* node, int* x, int* y)
	{
		intptr_t index = (intptr_t)node;
		*y = index / niveles[0];
		*x = index - *y * niveles[0];
	}

	void* XYToNode(int x, int y)
	{
		return (void*)(y*niveles[0] + x);
	}

	/**
	Return the least possible cost between 2 states. For example, if your pathfinding
	is based on distance, this is simply the straight distance between 2 points on the
	map. If you pathfinding is based on minimum time, it is the minimal travel time
	between 2 points given the best possible terrain.
	*/
	virtual float LeastCostEstimate(void* stateStart, void* stateEnd)
	{
		int firstX, firstY, lastX, lastY;
		NodeToXY(stateStart, &firstX, &firstY);
		NodeToXY(stateEnd, &lastX, &lastY);

		int dx = firstX - lastX;
		int dy = firstY - lastY;
		return (float)sqrt((double)(dx*dx) + (double)(dy*dy));
	}

	/**
	Return the exact cost from the given state to all its neighboring states. This
	may be called multiple times, or cached by the solver. It *must* return the same
	exact values for every call to MicroPather::Solve(). It should generally be a simple,
	fast function with no callbacks into the pather.
	*/
	virtual void AdjacentCost(void* state, std::vector< micropather::StateCost > *adjacent)
	{
		micropather::StateCost nodeCost;
		int x, y;
		NodeToXY(state, &x, &y);
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 0:
				if (y > 0){
					if (mapa[(y - 1)*niveles[0] + x] == 'X')
						nodeCost = { XYToNode(x, y - 1), INT_MAX };
					else
						nodeCost = { XYToNode(x, y - 1), 1 };
					adjacent->push_back(nodeCost);
				}
				break;
			case 1:
				if (y > 0 && x < niveles[0]-1){
					if (mapa[(y - 1)*niveles[0] + x + 1] == 'X')
						nodeCost = { XYToNode(x + 1, y - 1), INT_MAX };
					else
						nodeCost = { XYToNode(x + 1, y - 1), 1 };
					adjacent->push_back(nodeCost);
				}
				break;
			case 2:
				if (x < niveles[0]-1){
					if (mapa[(y)*niveles[0] + x + 1] == 'X')
						nodeCost = { XYToNode(x + 1, y), INT_MAX };
					else
						nodeCost = { XYToNode(x + 1, y), 1 };
					adjacent->push_back(nodeCost);
				}
				break;
			case 3:
				if (y < niveles.size()-1 && x < niveles[0] - 1){
					if (mapa[(y + 1)*niveles[0] + x + 1] == 'X')
						nodeCost = { XYToNode(x + 1, y + 1), INT_MAX };
					else
						nodeCost = { XYToNode(x + 1, y + 1), 1 };
					adjacent->push_back(nodeCost);
				}
				break;
			case 4:
				if (y < niveles.size() - 1){
					if (mapa[(y + 1)*niveles[0] + x] == 'X')
						nodeCost = { XYToNode(x, y + 1), INT_MAX };
					else
						nodeCost = { XYToNode(x, y + 1), 1 };
					adjacent->push_back(nodeCost);
				}
				break;
			case 5:
				if (y < niveles.size() - 1 && x > 0){
					if (mapa[(y + 1)*niveles[0] + x - 1] == 'X')
						nodeCost = { XYToNode(x - 1, y + 1), INT_MAX };
					else
						nodeCost = { XYToNode(x - 1, y + 1), 1 };
					adjacent->push_back(nodeCost);
				}
				break;
			case 6:
				if (x > 0){
					if (mapa[(y)*niveles[0] + x - 1] == 'X')
						nodeCost = { XYToNode(x - 1, y), INT_MAX };
					else
						nodeCost = { XYToNode(x - 1, y), 1 };
					adjacent->push_back(nodeCost);
				}
				break;
			case 7:
				if (y > 0 && x > 0){
					if (mapa[(y - 1)*niveles[0] + x - 1] == 'X')
						nodeCost = { XYToNode(x - 1, y - 1), INT_MAX };
					else
						nodeCost = { XYToNode(x - 1, y - 1), 1 };
					adjacent->push_back(nodeCost);
				}
				break;
			}
		}

	}

	/**
	This function is only used in DEBUG mode - it dumps output to stdout. Since void*
	aren't really human readable, normally you print out some concise info (like "(1,2)")
	without an ending newline.
	*/
	virtual void  PrintStateInfo(void* state){}
};