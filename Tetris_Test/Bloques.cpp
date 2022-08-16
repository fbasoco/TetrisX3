#include "Bloques.h"
#include <time.h>

Bloques::Bloques()
{
	// Crear un arreglo de Vectores que guaradan la posicion de cada bloque de una pieza
	/*bloque = new Vector2D[4];
	ultimoBloqueColocado = new Vector2D[4];*/

	// Se genera aleatoreamente el tipo de pieza que aparecera
	srand(time(NULL));
	tipoDePieza = rand() % 7;
	bloqueSiguiente = 0;
	colorSiguiente = 0;

	seleccionarSiguientePieza = false;
	// Cargar la textura qe usara el bloque
	b.Cargar("Imagenes/Bloque.bmp", 32, 32);

	// Direccion del bloque comienza por 1
	direccion = 1;
	//Velocidad de desplazamiento del bloque hacia abajo 
	velocidad = 1;
	tiempo = 0;

	// Establecer en False todos los espacios ocupados por la figura actual
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 22; j++)
		{
			EspacioDeLaFigura[i][j] = false;
		}
	}

	score = 0;

	// Establecer en False todos los espacios
	for (int i = 0; i < 36; i++)
	{
		for (int j = 1; j < 22; j++)
		{
			Espacio[i][j] = false;
		}

	}
	// Establece en true los espacios de las paredes Horizontales
	for (int i = 0; i < 36; i++)
	{
		Espacio[i][0] = true;
		Espacio[i][21] = true;
	}
	
	// Establece en true los espacios de las paredes Verticales
	for (int j = 1; j < 21; j++)
	{
		Espacio[0][j] = true;
		Espacio[11][j] = true;
		Espacio[12][j] = true;
		Espacio[23][j] = true;
		Espacio[24][j] = true;
		Espacio[35][j] = true;
	}

	// Establece los colores de cada espacio
	for (int i = 0; i < 36; i++)
	{
		for (int j = 0; j < 22; j++)
		{

			if (Espacio[i][j] == false)
			{
				b.Posicion(i, j);

				if (i >= 0 && i <= 11)
					colorDelEspacio[i][j] = 0;
				if (i >= 12 && i <=23)
					colorDelEspacio[i][j] = 1;
				if (i >= 24 && i <= 36)
					colorDelEspacio[i][j] = 2;
			}

		}
	}

	generarPieza = false;
}

Bloques::~Bloques()
{
}

void Bloques::Actualizar(double DeltaTime)
{
	tiempo += DeltaTime;

	// Resetea todos los espacios a false, para volver a ser calculados cuando se actualizen las piezas
	for (int i = 0; i < 36; i++)
	{
		for (int j = 0; j < 22; j++)
		{
			EspacioDeLaFigura[i][j] = false;
		}
	}

	// Se genera una nueva pieza
	GenerarPieza();
	// se seleeciona  una pieza dependiendo del valor que se ingrese
	SeleccionarPieza(tipoDePieza);

	if (ChecarSiLaFilaEstaLlena())
	{
		score += 100;
		RemoverPenalidad();
	}

	if (velocidad != 10)
	{
		if (score >= 1000)
		{
			velocidad = 2;
		}
		if (score >= 2000)
		{
			velocidad = 3;
		}
		if (score >= 3000)
		{
			velocidad = 4;
		}
		if (score >= 4000)
		{
			velocidad = 5;
		}
	}
	// so el tiempo es mayor al indicado checa los bloques
	if (tiempo > 250 / velocidad)
	{
		// Si no hace colision con otra pieza abajo, se desplaza una posicion
		if (!ChecarPosicionesY())
		{
			// posicion de y;
			y++;
			// se restablece el contador 
			tiempo = 0;
		}
	}

	// si el tiempo es mayor a 500 se actualizan los espacios vacios y se les asigna un color dependiendo del color de la pieza
	if (tiempo > 500)
	{
		// se actualizan los nuevos espacios ocupados cuando la pieza termina de caer
		for (int w = 0; w < 4; w++)
		{
			Espacio[bloque[w].X()][bloque[w].Y()] = EspacioDeLaFigura[bloque[w].X()][bloque[w].Y()];
			
			colorDelEspacio[bloque[w].X()][bloque[w].Y()] = color;
			ultimoBloqueColocado[w].Posicion(bloque[w].X(), bloque[w].Y());			
		}

		// Si una pieza de diferente color cae en una posicion incorrecta, se ejecuta la penalidad 
		Penalidad();

		if (Fin())
		{
			return;
		}

		// Flag para generar pieza nueva
		generarPieza = true;

		// Flag para entrar a la funcion de Seleccionar la siguiente pieza
		seleccionarSiguientePieza = true;

		// se resetea el tiempo
		tiempo = 0;
	}
}

void Bloques::Dibujar()
{
	// Dibuja los espacios de las columbas ocupados por los bloques
	for (int i = 0; i < 36; i++)
	{
		for (int j = 0; j < 22; j++)
		{
			if (Espacio[i][j] == true)
			{
				b.Posicion(i, j);
				if (colorDelEspacio[i][j] == 0)
					b.Mostrar(Rojo.r, Rojo.g, Rojo.b);
				if (colorDelEspacio[i][j] == 1)
					b.Mostrar(Verde.r, Verde.g, Verde.b);
				if (colorDelEspacio[i][j] == 2)
					b.Mostrar(azul.r, azul.g, azul.b);
			}
		}
	
	}

	// Dibujar bloques en movimiento
	for (int i = 0; i < 36; i++)
	{
		for (int j = 0; j < 22; j++)
		{
			if (EspacioDeLaFigura[i][j] == true)
			{
				b.Posicion(i, j);
				if (color == 0)
					b.Mostrar(Rojo.r, Rojo.g, Rojo.b);
				if (color == 1)
					b.Mostrar(Verde.r, Verde.g, Verde.b);
				if (color == 2)
					b.Mostrar(azul.r, azul.g, azul.b);
			}
		}
	}
}

void Bloques::GenerarPieza()
{
	// Se genera una nueva pieza
	if (generarPieza)
	{
		if (seleccionarSiguientePieza)
		{
			tipoDePieza = bloqueSiguiente;
			color = colorSiguiente;
			seleccionarSiguientePieza = false;
		}

		// se ajusta el giro de la pieza a 1
		direccion = 1;
		// Genera la siguiente pieza Aleatoreamente
		bloqueSiguiente = rand() % 7;
		// se genera un valor aleatorio para el color
		colorSiguiente = rand() % 3;
		
		// Se establece la posicion inicial de la pieza
		Posicion(17, 2);

		Fin();

		generarPieza = false;
		srand(time(NULL));


	}
}

void Bloques::SeleccionarPieza(int idPieza)
{
	switch (idPieza)
	{
	case 0:
		O();
		break;
	case 1:
		I();
		break;
	case 2:
		S();
		break;
	case 3:
		Z();
		break;
	case 4:
		L();
		break;
	case 5:
		J();
		break;
	case 6:
		T();
		break;
	}

	if (ChecarPosicionesX(0))
	{
		direccion = direccionAnterior;
	}

}

void Bloques::Posicion(int X, int Y)
{
	x = X;
	y = Y;
}

void Bloques::Direccion()
{
	direccionAnterior = direccion;
	switch (tipoDePieza)
	{
	case 0:
		break;
	case 1:
	case 2:
	case 3:
		if (direccion == 1)
		{
			direccion = 2;
		}
		else
		{
			if (direccion == 2)
			{
				direccion = 1;
			}
			else
			{
				direccion = 1;
			}
		}
		break;
	case 4:
	case 5:
	case 6:
		if (direccion == 1)
		{
			direccion = 2;
		}
		else
		{
			if (direccion == 2)
			{
				direccion = 3;
			}
			else
			{
				if (direccion == 3)
				{
					direccion = 4;
				}
				else
				{
					direccion = 1;
				}
			}
		}
		break;
	}
}

int Bloques::EspacioDelUltimoBloqueColocado()
{
	if (ultimoBloqueColocado[0].X() < 12)
	{
		return 0;
	}
	if (ultimoBloqueColocado[0].X() >= 12 && ultimoBloqueColocado[0].X() < 24)
	{
		return 1;
	}
	return 2;
}

bool Bloques::ChecarPosicionesY()
{
	for (int w = 0; w < 4; w++)
	{
		if (EspacioDeLaFigura[bloque[w].X()][bloque[w].Y()] == true && Espacio[bloque[w].X()][bloque[w].Y() + 1] == true)
		{ 
			return true;
		}
	}
	return false;
}

bool Bloques::ChecarPosicionesX( int posiciones)
{
	for (int w = 0; w < 4; w++)
	{
		if (EspacioDeLaFigura[bloque[w].X()][bloque[w].Y()] == true && Espacio[bloque[w].X() + posiciones][bloque[w].Y()] == true)
		{
			return true;
		}
	}
	return false;
}

bool Bloques::ChecarSiLaFilaEstaLlena()
{
	int fila = 1;
	int espacio = 0;
	bool filaLlena = false;
	for (int w = 0; w < 3; w++)
	{
		for (int j = 1; j < 21; j++)
		{
			for (int i = 1; i < 11; i++)
			{
				if (Espacio[i + w * 12][j] && colorDelEspacio[i + w * 12][j] == w)
				{
					fila = j;
					espacio = w;
					filaLlena = true;
				}
				else
				{
					filaLlena = false;
					break;
				}
			}

			if (filaLlena)
			{
				break;
			}
		}
		if (filaLlena)
		{
			break;
		}
	}

	if (filaLlena == true)
	{
		for (int i = 1; i < 11; i++)
		{
			Espacio[i + espacio * 12][fila] = false;
		}

		// Mover los valores en cada espacio hacia abajo hasta llegar a la fila eliminada

		for (int i = 1; i < 11; i++)
		{
			for (int j = fila - 1; j > 1; j--)
			{
				Espacio[i + espacio * 12][j + 1] = Espacio[i + espacio * 12][j];
				colorDelEspacio[i + espacio * 12][j + 1] = colorDelEspacio[i + espacio * 12][j];
			}
		}
		return true;

	}
	return false;
}

bool Bloques::Penalidad()
{
	if (colorDelEspacio[ultimoBloqueColocado[0].X()][ultimoBloqueColocado[0].Y()] != EspacioDelUltimoBloqueColocado())
	{
		for (int w = 0; w < 4; w++)
		{
			Espacio[ultimoBloqueColocado[w].X()][ultimoBloqueColocado[w].Y()] = false;
		}
		
		for (int i = 0; i < 2; i++)
		{
			for (int j = ultimoBloqueColocado[i].Y(); j < 22; j++)
			{
				if (Espacio[ultimoBloqueColocado[i].X()][j + 1] == true)
				{
					Espacio[ultimoBloqueColocado[i].X()][j] = true;
					colorDelEspacio[ultimoBloqueColocado[i].X()][j] = color;
					break;

				}
			}
		}
		
		int posX[2];
		int p = 0;

		for (int w = 0; w < 3; w++)
		{
			if (w != EspacioDelUltimoBloqueColocado())
			{
				posX[p] = 1 + rand() % 10 + w * 12;
				p++;
			}
		}

		for (int i = 0; i < 2; i++)
		{
			for (int j = 1; j < 22; j++)
			{
				if (Espacio[posX[i]][j + 1] == true)
				{
					Espacio[posX[i]][j] = true;
					colorDelEspacio[posX[i]][j] = EspacioDelUltimoBloqueColocado();
					break;
				}
			}
		}

		return true;
	}
	return false;
}

bool Bloques::RemoverPenalidad()
{
	// flag para salir del ciclo do-while
	bool ok = false;
	// Se almacena la posicion del cuadro penalti Encontrado que sera eliminado
	Vector2D PBloque;
	// numero de espacio, columna y fila que se seleccionara
	int u, v, w;

	// establece en true cada posicion de la columna y fila que contenga un cuadro penal
	//bool columna[10];
	//bool fila[20];
	// establece en false cada espacio que contenga un cuadro penal
	bool aux[36][22];
	bool espacio[3];
	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 36; i++)
		{
			for (int j = 0; j < 22; j++)
			{
				aux[i][j] = false;
			}
		}
	}

	espacio[0] = false;
	espacio[1] = false;
	espacio[2] = false;

	// Revisa si existe un cuadro de penalizacion colocado en alguna columna, si es asi, se permite seleccionar uno al azar
	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (colorDelEspacio[i + k * 12 + 1][j + 1] != k)
				{
					aux[i + k * 12 + 1][j + 1] = true;
					espacio[k] = true;
					ok = true;
				}
			}
		}
	}
	
	if (ok)
	{
		ok = false;
		// Genera numeros aleatoreos para seleccionar el cuadro penal que sera retirado
		do
		{
			w = rand() % 3;
			if (espacio[w])
			{
				do
				{
					u = rand() % 10;

					for (int j = 1; j <= 20; j++)
					{
						if (aux[u + w * 12 + 1][j])
						{
							v = j;
							ok = true;
							break;
							
						}
					}
				} while (ok == false);
			}
		} while (espacio[w] == false);

		Espacio[u + w * 12 + 1][v] = false;
		PBloque.Posicion(u + w * 12 + 1, v);
		colorDelEspacio[u + w * 12 + 1][v] = w;

		for (int j = PBloque.Y(); j > 1; j--)
		{
			if (Espacio[PBloque.X()][j - 1] == true)
			{
				Espacio[PBloque.X()][j - 1] = false;
				Espacio[PBloque.X()][j] = true;
				colorDelEspacio[PBloque.X()][j] = w;
			}
			else
			{
				break;
			}
		}
	}
	return false;
}

int Bloques::VerBloqueSiguiente()
{
	return bloqueSiguiente;
}

int Bloques::VerColorSiguiente()
{
	return colorSiguiente;
}

bool Bloques::Fin()
{
	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 10; i++)
		{
			if (Espacio[i + k * 12 + 1][2] == true)
			{
				salir = true;
				return true;
			}
		}
	}

	/*for (int w = 0; w < 4; w++)
	{
		if (Espacio[bloque[w].X()][bloque[w].Y()] == EspacioDeLaFigura[X()][Y()])
		{
			salir = true;
			return true;
		}
	}*/
	return false;
}

void Bloques::Bloque()
{
	bloque[0].Posicion(x, y);
	EspacioDeLaFigura[x][y] = true;
}

void Bloques::O()
{
	bloque[0].Posicion(x, y);
	EspacioDeLaFigura[x][y] = true;

	bloque[1].Posicion(x + 1, y);
	EspacioDeLaFigura[x + 1][y] = true;

	bloque[2].Posicion(x, y + 1);
	EspacioDeLaFigura[x][y + 1] = true;

	bloque[3].Posicion(x + 1, y + 1);
	EspacioDeLaFigura[x + 1][y + 1] = true;
}

void Bloques::I()
{
	if (direccion == 1)
	{
		bloque[0].Posicion(x, y - 1);
		EspacioDeLaFigura[x][y - 1] = true;

		bloque[1].Posicion(x, y);
		EspacioDeLaFigura[x][y] = true;

		bloque[2].Posicion(x, y + 1);
		EspacioDeLaFigura[x][y + 1] = true;

		bloque[3].Posicion(x, y + 2);
		EspacioDeLaFigura[x][y + 2] = true;
	}
	if (direccion == 2)
	{
		bloque[0].Posicion(x - 1, y);
		EspacioDeLaFigura[x - 1][y] = true;

		bloque[1].Posicion(x, y);
		EspacioDeLaFigura[x][y] = true;

		bloque[2].Posicion(x + 1, y);
		EspacioDeLaFigura[x + 1][y] = true;

		bloque[3].Posicion(x + 2, y);
		EspacioDeLaFigura[x + 2][y] = true;
	}
}

void Bloques::S()
{
	if (direccion == 1)
	{
		bloque[0].Posicion(x, y);
		EspacioDeLaFigura[x][y] = true;

		bloque[1].Posicion(x + 1, y);
		EspacioDeLaFigura[x + 1][y] = true;

		bloque[2].Posicion(x, y + 1);
		EspacioDeLaFigura[x][y + 1] = true;

		bloque[3].Posicion(x - 1, y + 1);
		EspacioDeLaFigura[x - 1][y + 1] = true;
	}
	if (direccion == 2)
	{
		bloque[0].Posicion(x, y);
		EspacioDeLaFigura[x][y] = true;

		bloque[1].Posicion(x, y - 1);
		EspacioDeLaFigura[x][y - 1] = true;

		bloque[2].Posicion(x + 1, y);
		EspacioDeLaFigura[x + 1][y] = true;

		bloque[3].Posicion(x + 1, y + 1);
		EspacioDeLaFigura[x + 1][y + 1] = true;
	}
}

void Bloques::Z()
{
	if (direccion == 1)
	{
		bloque[0].Posicion(x - 1, y);
		EspacioDeLaFigura[x - 1][y] = true;

		bloque[1].Posicion(x, y);
		EspacioDeLaFigura[x][y] = true;

		bloque[2].Posicion(x, y + 1);
		EspacioDeLaFigura[x][y + 1] = true;

		bloque[3].Posicion(x + 1, y + 1);
		EspacioDeLaFigura[x + 1][y + 1] = true;
	}
	if (direccion == 2)
	{
		bloque[0].Posicion(x - 1, y);
		EspacioDeLaFigura[x - 1][y] = true;

		bloque[1].Posicion(x, y);
		EspacioDeLaFigura[x][y] = true;

		bloque[2].Posicion(x, y - 1);
		EspacioDeLaFigura[x][y - 1] = true;

		bloque[3].Posicion(x - 1, y + 1);
		EspacioDeLaFigura[x - 1][y + 1] = true;
	}
}

void Bloques::L()
{
	if (direccion == 1)
	{
		bloque[0].Posicion(x, y - 1);
		EspacioDeLaFigura[x][y - 1] = true;

		bloque[1].Posicion(x, y);
		EspacioDeLaFigura[x][y] = true;

		bloque[2].Posicion(x, y + 1);
		EspacioDeLaFigura[x][y + 1] = true;

		bloque[3].Posicion(x + 1, y + 1);
		EspacioDeLaFigura[x + 1][y + 1] = true;
	}
	if (direccion == 2)
	{
		bloque[0].Posicion(x + 1, y);
		EspacioDeLaFigura[x + 1][y] = true;

		bloque[1].Posicion(x, y);
		EspacioDeLaFigura[x][y] = true;

		bloque[2].Posicion(x - 1, y);
		EspacioDeLaFigura[x - 1][y] = true;

		bloque[3].Posicion(x - 1, y + 1);
		EspacioDeLaFigura[x - 1][y + 1] = true;
	}
	if (direccion == 3)
	{
		bloque[0].Posicion(x + 1, y - 1);
		EspacioDeLaFigura[x + 1][y - 1] = true;

		bloque[1].Posicion(x + 1, y);
		EspacioDeLaFigura[x + 1][y] = true;

		bloque[2].Posicion(x + 1, y + 1);
		EspacioDeLaFigura[x + 1][y + 1] = true;

		bloque[3].Posicion(x , y - 1);
		EspacioDeLaFigura[x][y - 1] = true;
	}
	if (direccion == 4)
	{
		bloque[0].Posicion(x + 1, y + 1);
		EspacioDeLaFigura[x + 1][y + 1] = true;

		bloque[1].Posicion(x, y + 1);
		EspacioDeLaFigura[x][y + 1] = true;

		bloque[2].Posicion(x - 1, y + 1);
		EspacioDeLaFigura[x - 1][y + 1] = true;

		bloque[3].Posicion(x + 1, y);
		EspacioDeLaFigura[x + 1][y] = true;
	}

}

void Bloques::J()
{
	if (direccion == 1)
	{
		bloque[0].Posicion(x, y - 1);
		EspacioDeLaFigura[x][y - 1] = true;

		bloque[1].Posicion(x, y);
		EspacioDeLaFigura[x][y] = true;

		bloque[2].Posicion(x, y + 1);
		EspacioDeLaFigura[x][y + 1] = true;

		bloque[3].Posicion(x - 1, y + 1);
		EspacioDeLaFigura[x - 1][y + 1] = true;
	}
	if (direccion == 2)
	{
		bloque[0].Posicion(x - 1, y);
		EspacioDeLaFigura[x - 1][y] = true;

		bloque[1].Posicion(x - 1, y + 1);
		EspacioDeLaFigura[x - 1][y + 1] = true;

		bloque[2].Posicion(x, y + 1);
		EspacioDeLaFigura[x][y + 1] = true;

		bloque[3].Posicion(x + 1, y + 1);
		EspacioDeLaFigura[x + 1][y + 1] = true;
	}
	if (direccion == 3)
	{
		bloque[0].Posicion(x - 1, y - 1);
		EspacioDeLaFigura[x - 1][y - 1] = true;

		bloque[1].Posicion(x - 1, y);
		EspacioDeLaFigura[x - 1][y] = true;

		bloque[2].Posicion(x - 1, y + 1);
		EspacioDeLaFigura[x - 1][y + 1] = true;

		bloque[3].Posicion(x , y - 1);
		EspacioDeLaFigura[x][y - 1] = true;
	}
	if (direccion == 4)
	{
		bloque[0].Posicion(x + 1, y);
		EspacioDeLaFigura[x + 1][y] = true;

		bloque[1].Posicion(x - 1, y);
		EspacioDeLaFigura[x - 1][y] = true;

		bloque[2].Posicion(x, y);
		EspacioDeLaFigura[x][y] = true;

		bloque[3].Posicion(x + 1, y + 1);
		EspacioDeLaFigura[x + 1][y + 1] = true;
	}

}

void Bloques::T()
{ 
	if (direccion == 1)
	{
		bloque[0].Posicion(x, y);
		EspacioDeLaFigura[x][y] = true;

		bloque[1].Posicion(x - 1, y);
		EspacioDeLaFigura[x - 1][y] = true;

		bloque[2].Posicion(x + 1, y);
		EspacioDeLaFigura[x + 1][y] = true;

		bloque[3].Posicion(x, y - 1);
		EspacioDeLaFigura[x][y - 1] = true;
	}
	if (direccion == 2)
	{
		bloque[0].Posicion(x, y);
		EspacioDeLaFigura[x][y] = true;

		bloque[1].Posicion(x, y - 1);
		EspacioDeLaFigura[x][y - 1] = true;

		bloque[2].Posicion(x, y + 1);
		EspacioDeLaFigura[x][y + 1] = true;

		bloque[3].Posicion(x + 1, y);
		EspacioDeLaFigura[x + 1][y] = true;
	}
	if (direccion == 3)
	{
		bloque[0].Posicion(x, y);
		EspacioDeLaFigura[x][y] = true;

		bloque[1].Posicion(x - 1, y);
		EspacioDeLaFigura[x - 1][y] = true;

		bloque[2].Posicion(x + 1, y);
		EspacioDeLaFigura[x + 1][y] = true;

		bloque[3].Posicion(x, y + 1);
		EspacioDeLaFigura[x][y + 1] = true;
	}
	if (direccion == 4)
	{
		bloque[0].Posicion(x, y);
		EspacioDeLaFigura[x][y] = true;

		bloque[1].Posicion(x, y - 1);
		EspacioDeLaFigura[x][y - 1] = true;

		bloque[2].Posicion(x, y + 1);
		EspacioDeLaFigura[x][y + 1] = true;

		bloque[3].Posicion(x - 1, y);
		EspacioDeLaFigura[x - 1][y] = true;
	}
}
