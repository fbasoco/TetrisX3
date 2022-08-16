#include "Pared.h"
#include "Vector2D.h"

Pared::Pared()
{
	b.Cargar("Imagenes/Bloque.bmp", 32, 32);
}

void Pared::Actualizar()
{
}

void Pared::Dibujar()
{
	for (int i = 0; i < 36; i++)
	{
		for (int j = 0; j < 22; j++)
		{

			if (Espacio[i][j] == true)
			{
				b.Posicion(i, j);

				if (i >= 0 && i <= 11)
					b.Mostrar(255, 128, 128);
				if (i >= 12 && i <=23)
					b.Mostrar(128, 255, 128);
				if (i >= 24 && i <= 36)
					b.Mostrar(128, 128, 255);
			}
		}
	}
}