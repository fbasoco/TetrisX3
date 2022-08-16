#include "Graficos.h"
#include <SDL_ttf.h>


Graficos::Graficos()
{
	window = NULL;
	renderer = NULL;
}


Graficos::~Graficos()
{
	Cerrar();
}

bool Graficos::Iniciar(int Ancho, int Alto)
{
	// Inicia el SDL
	int  iniciar_ok = SDL_Init(SDL_INIT_EVERYTHING);
	if (iniciar_ok != 0)
	{
		return false;
	}
	// Crear ventana
	window = SDL_CreateWindow("Tetris_Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Ancho, Alto, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		return false;
	}
	
	// Mostrar en pantalla
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		return false;
	}
	else
	{
		// Color de fondo
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}

	return true;
}

void Graficos::Cerrar()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Graficos::Limpiar()
{
	SDL_RenderClear(Graficos::renderer);

}
void Graficos::Presentar()
{
	SDL_RenderPresent(renderer);
}
