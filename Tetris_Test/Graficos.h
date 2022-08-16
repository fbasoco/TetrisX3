#pragma once
#include <SDL.h>

class Graficos
{
	public:
		Graficos();
		~Graficos();
	
		// Inicia la ventana en modo grafico y todos los subsistemas de SDL
		// Parametros
		// Ancho: Longitud horizontal de la ventana
		// Alto: Longitud Vertical de la ventana
		bool Graficos::Iniciar(int ancho, int Alto);
		// Finaliza los subsistemas de SDL
		void Graficos::Cerrar();
		// Limpia la ventana para despues ser renderizada
		void Limpiar();
		// Actualiza la imagen ede la pantalla
		void Presentar();

		SDL_Renderer* Renderer()
		{
			if (renderer != NULL)
			{
				return renderer;
			}
			return NULL;
		}
	
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
};