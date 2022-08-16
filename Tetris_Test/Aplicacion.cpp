#include "Aplicacion.h"

Aplicacion::Aplicacion()
{
	evento = new SDL_Event();

	salir = false;

}

Aplicacion::~Aplicacion()
{
	Cerrar();
}

bool Aplicacion::Iniciar()
{
	if (graficos.Iniciar(Ventana_Ancho, Ventana_Alto))
	{
		if(TTF_Init()<0)
		{
			return false;
		}
		return true;
	}
	return false;
}

void Aplicacion::Cerrar()
{
	fondo.Eliminar();

	graficos.Cerrar();

	score.Cerrar();
}

bool Aplicacion::Cargar()
{
	if (!instrucciones.Cargar("Imagenes/Instrucciones.bmp", 1344, 704))
	{
		return false;
	}
	instrucciones.Posicion(0, 0);

	if (!fondo.Cargar("Imagenes/Fondo.bmp", 1344, 704))
	{
		return false;
	}
	fondo.Posicion(0, 0);

	if (!FinDelJuego.Cargar("Imagenes/Texto_FinDelJuego.bmp", 512, 256))
	{
		return false;
	}
	FinDelJuego.Posicion(.8125, .875);

	bloque = new Bloques();
	bloque->Posicion(17, 2);

	pared = new Pared;

	sigPieza = new SigPieza;
	sigPieza->Posicion(33, 8);
	
	if (!score.Cargar("AnthologY.ttf", 32))
	{
		return false;
	}

	graficos.Limpiar();
	graficos.Presentar();
	SDL_Delay(2000);


	graficos.Limpiar();
	instrucciones.Mostrar(255, 255, 255);
	graficos.Presentar();
	SDL_Delay(5000);

	return true;
}

void Aplicacion::Actualizar(double DeltaTime)
{
	pared->Actualizar();
	bloque->Actualizar(DeltaTime);
	if (bloque->salir)
	{
		salir = true;
	}
	
	sigPieza->Actualizar();

	sigPieza->GenerarPiezaSiguiente(bloque->VerBloqueSiguiente(), bloque->VerColorSiguiente());
}

void Aplicacion::Dibujar()
{
	// Limpiar pantalla antes de renderizar
	graficos.Limpiar();


	// se Dibuja todo el contenido que se encuentre despues de limpiar la pantalla
	fondo.Mostrar(255, 255, 255);

	bloque->Dibujar();
	pared->Dibujar();
	sigPieza->Dibujar();

	score.Imprimir(to_string(bloque->Score()), 1200, 64);


	if (salir)
	{
		FinDelJuego.Mostrar(255, 255, 255);
		
		if (!score.Cargar("AnthologY.ttf", 48))
		{
			return;
		}

		score.Color(0, 0, 0);
		score.Imprimir(to_string(bloque->Score()), 600, 350);

	}

	// Actualiza y dibuja todos los graficos 
	graficos.Presentar();
}
	
void Aplicacion::CicloDelJuego()
{
	// variables para calcular el Tiempo Delta
	Uint64 tiempo_Ahora = SDL_GetPerformanceCounter();
	Uint64 tiempo_Final = 0;
	double deltaTime;

	while (!salir)
	{
		// Tiempo al final del ciclo se iguala tiempo al inicio
		tiempo_Final = tiempo_Ahora;
		// Se vuelve a leer el tiempo actual
		tiempo_Ahora = SDL_GetTicks();
		// La diferencia de los tiempos almacenados es el tiempo delta adel ciclo
		deltaTime = (double)((tiempo_Ahora - tiempo_Final));// / SDL_GetPerformanceFrequency());

		// Si Ocurre algun evento entra al if
		if (SDL_PollEvent(evento) != 0)
		{
			// Salir si el evento es del tipo DSL_QUIT
			if (evento->type == SDL_QUIT)
			{
				salir = true;
			}

			// Se activa si alguna tecla es presionada
			if (evento->type == SDL_KEYDOWN)
			{
				// Se activa si la tecla presionada es la flecha IZQUIERDA
				if (evento->key.keysym.sym == SDLK_LEFT)
				{
					if (!bloque->ChecarPosicionesX(-1))
						bloque->Posicion(bloque->X() - 1, bloque->Y());
				}

				// Se activa si la tecla presionada es la flecha DERECHA
				if (evento->key.keysym.sym == SDLK_RIGHT)
				{
					if (!bloque->ChecarPosicionesX(1))
						bloque->Posicion(bloque->X() + 1, bloque->Y());
				}

				// Se activa si la tecla presionada es la A
				if (evento->key.keysym.sym == SDLK_a)
				{
					if (bloque->X() > 12 && !bloque->ChecarPosicionesX(-12))
						bloque->Posicion(bloque->X() - 12, bloque->Y());
				}

				// Se activa si la tecla presionada es la D
				if (evento->key.keysym.sym == SDLK_d)
				{
					if (bloque->X() < 27 && !bloque->ChecarPosicionesX(12))
						bloque->Posicion(bloque->X() + 12, bloque->Y());
				}

				// Se activa si la tecla presionada es SPACE
				if (evento->key.keysym.sym == SDLK_SPACE)
				{
					bloque->Direccion();
				}

				// Se activa si la tecla presionada es la flecha ABAJO
				if (evento->key.keysym.sym == SDLK_DOWN)
				{
					bloque->velocidad = 10;
				}
			}

			// Se activa si alguna tecla es soltada
			if (evento->type == SDL_KEYUP)
			{
				// Se activa si la tecla soltada es la flecha ABAJO
				if (evento->key.keysym.sym == SDLK_DOWN)
				{
					bloque->velocidad = 1;
				}
			}
		}

		Actualizar(deltaTime);
		Dibujar();
	}

	SDL_Delay(5000);
}
