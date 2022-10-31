#pragma once
#include "SDL.h"

namespace MaximumEngine
{
	class Time
	{
	public:		
		//GETTERS
		static float getDeltaTimeSeconds();
		static uint32_t getDeltaTimeMilliSeconds();
		static uint32_t getMiscTime();
		static uint32_t getRenderTime();
		static uint32_t getUpdateTime();
		static int getFps();
	private:
		//METHODS
		static void updateOverallTime();
		static void updateRenderTime();
		static void updateUpdateTime();
		static void updateMiscTime();
		//VARIABLES
		static uint32_t lastTickTime;
		static uint32_t currentDeltaTime;
		static uint32_t renderTime;
		static uint32_t updateTime;
		static uint32_t miscTime;
		static uint32_t deltaTime;
		static int fps;
		//FRIENDS
		friend class Engine;
	};
}

//Returns delta time in seconds
#define ME_DELTA_TIME MaximumEngine::Time::getDeltaTimeSeconds()


