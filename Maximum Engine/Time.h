#pragma once
#include "SDL.h"

namespace MaximumEngine
{
	class Time
	{
	public:		
		//GETTERS
		static double getDeltaTime();
	private:
		//METHODS
		static void updateTime();
		static void logFPS();
		static uint32_t lastTickTime;
		static uint32_t delta;
		static int fps;
		static bool showFPS;
		//FRIENDS
		friend class Engine;
	};
}

//Returns delta time in seconds
#define ME_DELTA_TIME MaximumEngine::Time::getDeltaTime()



