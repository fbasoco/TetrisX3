#pragma once

#include "Texturas.h"
#include <SDL_ttf.h>
#include <string>
#include <sstream>

class Texto
{
public:
	Texto();
	~Texto();

	// Carga la fuente y el tamaño de la fuente y genera la textura para cada numero del 0 al 9 para desues ser usada 
	bool Cargar(string Fuente, int Tamaño);

	// cierra la fuente cargada
	void Cerrar();

	// Muestra en la pantalla la cadena Escrita
	void Imprimir(string Texto, int X, int Y);
	
	// Establece el color del texto
	void Color(int R, int G, int B);

private:
	int x;
	int y;

	// Tipo de fuente que se usara
	TTF_Font* fuente;

	// Arreglo de texturas en donde se almacena una imagen de cada caracter 
	SDL_Texture* Texture_Texto[3][32];
	// Arreglo de rectangulos para cada textura
	SDL_Rect rect_texto[3][32];
	
	// Color del texto
	SDL_Color color;
};