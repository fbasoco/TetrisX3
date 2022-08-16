#pragma once
#include <SDL.h>
#include <string>
#include "Graficos.h"

using namespace std;

class Texturas
{
	public:
		Texturas();
		~Texturas();
		
		// Carga un archivo bmp y le asigna un tamaño a la textura
		bool Cargar(string Archivo, int Ancho, int Alto);
		// Muestra en la pantalla la textura cargada
		void Mostrar(int R, int G, int B);
		// Ajusta la posicion de la textura en funcion del ancho y alto de la imagen
		void Posicion(float X, float Y);
		// Devuelve el valor del miembro de la textura
		SDL_Texture* Textura();
		
		int X();
		int Y();


		void Eliminar();

	private:
		// Textura del bloque
		SDL_Texture* textura;

		// Dimensiones de la imagen y posicion de la textura
		int x;
		int y;
		int ancho;
		int alto;
};