#pragma once
#include "Bloques.h"
class SigPieza : public Bloques
{
	public:
		SigPieza();
		~SigPieza();

		void Actualizar()
		{
			for (int i = 0; i < 36; i++)
			{
				for (int j = 0; j < 22; j++)
				{
					EspacioDeLaFigura[i][j] = false;
				}
			}

			SeleccionarPieza(pieza);
		}
		void Dibujar()
		{
			for (int i = 0; i < 36; i++)
			{
				for (int j = 0; j < 22; j++)
				{
					if (EspacioDeLaFigura[i][j] == true)
					{
						b.Posicion(i + 5, j);
						if (color == 0)
							b.Mostrar(255, 128, 128);
						if (color == 1)
							b.Mostrar(128, 255, 128);
						if (color == 2)
							b.Mostrar(128, 128, 255);
					}
				}
			}
		}

		// devuelve el valor de la nueva pieza Generada
		void GenerarPiezaSiguiente(int idPieza, int idcolor)
		{
			pieza = idPieza;
			color = idcolor;
		}

	private:
		int pieza;
		int color;
};

