#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include "Vector2.h"

namespace MaximumEngine
{
	class Debug
	{
	private:
		//CLASSES
		class DebugText
		{
		private:
			//METHODS
			DebugText(int x, int y, std::string t);
			void render(SDL_Renderer* renderer);
			//VARIABLES
			int x, y;
			std::string text;
			//FRIENDS
			friend class Debug;
		};
		//METHODS
		static void start();
		static void update();
		static void render(SDL_Renderer* renderer);
		//VARIABLES
		static TTF_Font* font;
		static DebugText fps_t;
		static DebugText delta_t;
		static DebugText misc_t;
		static DebugText update_t;
		static DebugText render_t;
		static uint32_t lastUpdateTime;
		//FRIENDS
		friend class Engine;
	};
}

