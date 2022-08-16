#pragma once

#include <SDL.h>
#include "Graficos.h"
#include "Bloques.h"
#include "Pared.h"
#include "SigPieza.h"
#include "Texto.h"

class Aplicacion
{
	public:
		// Constructor
		Aplicacion();
		// Destructor, llama al metodo Cerrar
		~Aplicacion();
	
		// Inicia La Ventana grafica
		bool Iniciar();
		// Llama al metodo Cerrar de la clase Graficos 
		void Cerrar();
		// Dibuja los graficos en la ventana
		void Dibujar();
		// Se usa para actualizar cualqier cambio realizado
		void Actualizar(double DeltaTime);
		// Aqui se cargan las imagenes que se usaran en el juego
		bool Cargar();
		// Ciclo principal de la aplicacion
		void CicloDelJuego();

	private:

		//bool Texto(string Texto);

		Graficos graficos;
		SDL_Event* evento;

		// Flag que se usa para salir del ciclo de la aplicacion
		bool salir;

		// Propiedades de la pantalla
		const int Ventana_Ancho = 1344;
		const int Ventana_Alto = 704;

		//
		// Objetos que se usaran en el juego
		//
		
		// Texturas
		//Texturas logo;
		Texturas instrucciones;
		Texturas fondo;
		Texturas FinDelJuego;

		// Creaa los bloques del juego
		Bloques* bloque;
		// Dibuja los bloques que conforman la pared, con su respectivo color
		Pared* pared;
		// muestra la siguiente pieza que sera genereda
		SigPieza* sigPieza;

		Texto score;
		Texto scoreFinal;
};

