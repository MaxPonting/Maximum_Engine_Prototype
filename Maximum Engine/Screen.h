#pragma once
#include "SDL.h"
#include "Vector2.h"
#include "Colour.h"

namespace MaximumEngine
{
	class Screen
	{
	public:
		//GETTERS
		static Vector2 getResolution();	
		//SETTERS
		static void setResolution(int x, int y);
		//METHODS
		static bool onScreen(const Vector2* p);
		//VARIABLES
		static Colour colour;
	private:
		//VARIABLES
		static Vector2 resolution;
	};
}

#define ME_SetResolution(x, y) MaximumEngine::Screen::setResolution(x, y)
#define ME_GetResolution() MaximumEngine::Screen::getResolution()
#define ME_OnScreen(p) MaximumEngine::Screen::onScreen(p)
#define ME_Screen_Colour MaximumEngine::Screen::colour

