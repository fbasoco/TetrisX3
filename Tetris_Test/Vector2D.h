#pragma once
class Vector2D
{
	public:
		Vector2D();
		Vector2D(int x, int y);
		~Vector2D();
	
		// Establece los valores de X y Y
		void Posicion(int X, int Y);
		
		// Devuelve el valor de x
		int X()
		{
			return x;
		}

		// Devuelve el valor de ys
		int Y()
		{
			return y;
		}
	
	private:
		int x;
		int y;
};

