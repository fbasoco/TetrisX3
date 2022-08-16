#include <iostream>
#include "Aplicacion.h"

//using namespace std;

int main(int argc, char* args[])
{
	Aplicacion Tetris;

	if (Tetris.Iniciar() == false)
	{
		return 0;
	}
	else
	{
		if (Tetris.Cargar() == false)
		{
			return 0;
		}
		Tetris.CicloDelJuego();
		Tetris.Cerrar();
	}

	return 0;
}