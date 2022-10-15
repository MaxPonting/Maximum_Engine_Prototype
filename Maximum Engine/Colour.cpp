#include "Colour.h"

//CONSTRUCTORS
MaximumEngine::Colour::Colour() :r(255), g(255), b(255), a(255) {}
MaximumEngine::Colour::Colour(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) 
{
	if (r > 255) { r = 255; } if (r < 0) { r = 0; }
	if (g > 255) { g = 255; } if (g < 0) { g = 0; }
	if (b > 255) { b = 255; } if (b < 0) { b = 0; }
	if (a > 255) { a = 255; } if (a < 0) { a = 0; }
}

//GETTERS
int MaximumEngine::Colour::getR()
{
	return r;
}
int MaximumEngine::Colour::getG()
{
	return g;
}
int MaximumEngine::Colour::getB()
{
	return b;
}
int MaximumEngine::Colour::getA()
{
	return a;
}

