#pragma once
#include "SDL.h"
#include <chrono>

namespace MaximumEngine
{
	class Time
	{
	public:		
		//GETTERS
		static float getDeltaTimeSeconds();
		static float getDeltaTimeMilliSeconds();
		static float getMiscTime();
		static float getRenderTime();
		static float getUpdateTime();
		static int getFps();
	private:
		//METHODS
		static void updateOverallTime();
		static void updateRenderTime();
		static void updateUpdateTime();
		static void updateMiscTime();
		//VARIABLES
		static std::chrono::time_point<std::chrono::high_resolution_clock> lastTickTime;
		static float currentDeltaTime;
		static float renderTime;
		static float updateTime;
		static float miscTime;
		static float deltaTime;
		static int fps;
		//FRIENDS
		friend class Engine;
	};
}

//Returns delta time in seconds
#define ME_DELTA_TIME MaximumEngine::Time::getDeltaTimeSeconds()


