#include "Texturas.h"

Texturas::Texturas()
{
	// se establece la posicion y dimensiones de la imagen
	x = 0;
	y = 0;

	textura = NULL;
}

Texturas::~Texturas()
{
}

bool Texturas::Cargar(string Archivo, int Ancho, int Alto)
{
	ancho = Ancho;
	alto = Alto;

	SDL_Surface* surface = SDL_LoadBMP(Archivo.c_str());

	if (surface == NULL)
	{
		return false;
	}

	textura = SDL_CreateTextureFromSurface(SDL_GetRenderer(SDL_GetWindowFromID(1)), surface);

	SDL_FreeSurface(surface);

	if (textura == NULL)
	{
		return false;
	}
	return true;
}

void Texturas::Mostrar(int R, int G, int B)
{
	// Rectangulo Destino en donde se dibuja la textura
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.h = alto;
	rect.w = ancho;
	
	SDL_SetTextureColorMod(textura, R, G, B);
	SDL_RenderCopyEx(SDL_GetRenderer(SDL_GetWindowFromID(1)), textura, NULL, &rect, 0, 0, SDL_FLIP_NONE);
}


void Texturas::Posicion(float X, float Y)
{
	x = X * ancho;
	y = Y * alto;
}

SDL_Texture* Texturas::Textura()
{
	if (textura != NULL)
	{
		return textura;
	}
	else
	{
		return NULL;
	}
}

int Texturas::X()
{
	return x;
}

int Texturas::Y()
{
	return y;
}

void Texturas::Eliminar()
{
	SDL_DestroyTexture(textura);
}
