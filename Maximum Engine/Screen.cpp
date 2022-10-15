#include "Screen.h"

//INIT STATIC MEMBERS
ME_Colour MaximumEngine::Screen::colour = ME_Colour(0, 0, 0, 255);
ME_Vector2 MaximumEngine::Screen::resolution = ME_Vector2(640, 320);

//GETTERS
ME_Vector2 MaximumEngine::Screen::getResolution()
{
	return resolution;
}

//SETTERS
void MaximumEngine::Screen::setResolution(int x, int y)
{
	resolution = ME_Vector2(x, y);
}

//METHODS
bool MaximumEngine::Screen::onScreen(const Vector2* p)
{
	if (p->x < 0 || p->x > resolution.x) return false;
	if (p->y < 0 || p->y > resolution.y) return false;
	return true;
}