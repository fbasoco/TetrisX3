#pragma once
#include "Texturas.h"
#include "Texto.h"
#include "Vector2D.h"

class Bloques
{
	public:
		Bloques();
		~Bloques();

		// Actualiza la posicion de los bloques en el ciclo del programa
		void Actualizar(double deltaTime);
		// Dibuja la figura seleccionada aleatoreamente
		void Dibujar();
		// Genera una pieza aleatorea y asigna un color aleatoreo
		void GenerarPieza();

		void SeleccionarPieza(int idPieza);
		// Establecer la posicion del conjunto de bloques
		void Posicion(int X, int Y);
		// Modifica la rotacion o direccion de un bloque
		void Direccion();
		// Calcula en cual de los 3 espacios se encuentra el ultimo bloque colocado
		int EspacioDelUltimoBloqueColocado();
		// Checa si el siguiente espacio en Y esta ocupado, y si es asi el bloque deja de avanzar
		bool ChecarPosicionesY();
		// Checa si el espacio a los lados estan ocopados, si el parametro es true revisa el lado izquierdo,
		// si es false revisa el lado derecho
		bool ChecarPosicionesX(int posiciones);
		// Verifica si una fila esta completada y la destruye, posteriormente recorre hacia abajo los cuadros que estan por encima
		bool ChecarSiLaFilaEstaLlena();
		// Si el bloque es colocado en una columna que no es de su color, se divide en 4 y 2 piezas son cambiadas a otras columnas 
		// de otro color
		bool Penalidad();
		// Elimina un cuadro de penal 
		bool RemoverPenalidad();
		// Devuelve el valor de x
		int X()
		{
			return x;
		}
		// Devuelve el valor de y
		int Y()
		{
			return y;
		}
		// Devuelve las coordenadas del siguiente bloque en aparecer
		int VerBloqueSiguiente();
		// Devuelve el valor del proximo color generado
		int VerColorSiguiente();

		//
		bool Fin();

		int Score()
		{
			return score;
		}

		//
		// AJUSTAR LAS POSICIONES DE CADA BLOQUE DE LA PIEZA DEPENDIENDO DEL GIRO O DIRECCION A LA QUE APUNTA
		//
		// Establece las coordenadas de un solo bloque
		void Bloque();
		// Establece las coordenadas de los bloques para formar una O
		void O();
		// Establece las coordenadas de los bloques para formar una I
		void I();
		// Establece las coordenadas de los bloques para formar una S
		void S();
		// Establece las coordenadas de los bloques para formar una Z
		void Z();
		// Establece las coordenadas de los bloques para formar una L
		void L();
		// Establece las coordenadas de los bloques para formar una J
		void J();
		// Establece las coordenadas de los bloques para formar una T
		void T();

		int velocidad;
		bool salir = false;

	private:
		// Color del bloque
		SDL_Color Rojo = { 255, 128, 128 };
		SDL_Color Verde = { 128, 255, 128 };
		SDL_Color azul = { 128, 128, 255 };
		// indice del color actual
		int color;
		int colorSiguiente;
		// Posicion de los bloques
		int x;
		int y;
		// direccion del bloque del 1 al 2 o del 2 al 4 depende del tipo de pieza
		int direccion;
		int direccionAnterior = 0;

		int score;

	protected:
		// Vector de las posiciones de cada Bloque que conforma la pieza
		Vector2D bloque[4];
		Vector2D ultimoBloqueColocado[4];
		// valor de la siguiente pieza que sera generado
		int bloqueSiguiente;
		bool seleccionarSiguientePieza;
		// Textura del bloque
		Texturas b;
		// Espacios ocupados 
		bool Espacio[36][22];
		// Color de cada espacio lleno
		int colorDelEspacio[36][22];
		// Espacio ocupado por la pieza en movimiento
		bool EspacioDeLaFigura[36][22];
		// Tiempo que transcurre desde que el cuadro se mueve
		double tiempo;
		// Valor que corresponde cada pieza generada
		int tipoDePieza;
		// Al activarse esta condicion se crea una nueva pieza dentro del ciclo principal  
		bool generarPieza = true;

		
};

