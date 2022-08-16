#include "Texto.h"



Texto::Texto()
{
	x = 100;
	y = 200;
	Color(255, 255, 255);
	
	TTF_Init();
}


Texto::~Texto()
{
	Cerrar();
}

bool Texto::Cargar(string Fuente, int Tamaño)
{
	if (TTF_Init() < 0)
	{
		return false;
	}

	// Abrir un estilo de fuente
	fuente = TTF_OpenFont(Fuente.c_str(), Tamaño);

	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 32; i++)
		{
			SDL_Surface* Surface_texto;

			char c = (i + 32 * (k + 1));
			string s = string(1, c);

			if ((Surface_texto = TTF_RenderText_Solid(fuente, s.c_str(), color)) == NULL)
			{
				return false;
			}

			if ((Texture_Texto[k][i] = SDL_CreateTextureFromSurface(SDL_GetRenderer(SDL_GetWindowFromID(1)), Surface_texto)) == NULL)
			{

				return false;
			}
			else
			{
				if (SDL_QueryTexture(Texture_Texto[k][i], NULL, NULL, &rect_texto[k][i].w, &rect_texto[k][i].h) < 0)
				{
					return false;
				}
			}

			SDL_FreeSurface(Surface_texto);
		}
	}
	 
	TTF_CloseFont(fuente);

	return true;
}

void Texto::Cerrar()
{
	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 32; i++)
		{
			SDL_DestroyTexture(Texture_Texto[k][i]);
		}
	}
	
}

void Texto::Imprimir(string Texto, int X, int Y)
{
	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 32; i++)
		{
			SDL_SetTextureColorMod(Texture_Texto[k][i], color.r, color.g, color.b);
		}
	}

	int pos = 0;
	for (int i = 0; i < (int)Texto.length(); i++)
	{

		int decimal = Texto.at(i);

		for (int k = 0; k < 3; k++)
		{
			if (decimal >= 32 * (k + 1) && decimal < 32 * (k + 2))
			{
				rect_texto[k][decimal - 32 * (k + 1)].x = pos + X;
				rect_texto[k][decimal - 32 * (k + 1)].y = Y;

				pos += rect_texto[k][decimal - 32 * (k + 1)].w;

				SDL_RenderCopy(SDL_GetRenderer(SDL_GetWindowFromID(1)),
					Texture_Texto[k][decimal - 32 * (k + 1)],
					NULL, &rect_texto[k][decimal - 32 * (k + 1)]);
			}
		}
	}
}

void Texto::Color(int R, int G, int B)
{
	color.a = 255;
	color.b = B;
	color.g = G;
	color.r = R;

}