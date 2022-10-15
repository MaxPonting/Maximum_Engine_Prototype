#pragma once

namespace MaximumEngine
{
	class Colour
	{
	public:
		//CONSTRUCTORS
		Colour();
		Colour(int r, int g, int b, int a);
		//GETTERS
		int getR(), getG(), getB(), getA();
	private:
		//VARIABLES
		int r, g, b, a;
	};
}

#define ME_Colour MaximumEngine::Colour


