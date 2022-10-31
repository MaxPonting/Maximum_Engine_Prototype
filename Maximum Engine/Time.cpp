#include "Time.h"
#include "Log.h"

uint32_t MaximumEngine::Time::deltaTime = 0;
uint32_t MaximumEngine::Time::lastTickTime = 0;
uint32_t MaximumEngine::Time::currentDeltaTime = 0;
uint32_t MaximumEngine::Time::renderTime = 0;
uint32_t MaximumEngine::Time::updateTime = 0;
uint32_t MaximumEngine::Time::miscTime = 0;
int MaximumEngine::Time::fps = 0;

//METHODS
void MaximumEngine::Time::updateOverallTime()
{
	uint32_t tickTime = SDL_GetTicks();
	deltaTime = tickTime - lastTickTime;
	lastTickTime = tickTime;
	if (deltaTime != 0) { fps = 1000 / deltaTime; }
	else { fps = 1000; }
}
void MaximumEngine::Time::updateMiscTime()
{
	uint32_t timeTaken = SDL_GetTicks() - lastTickTime;
	miscTime = timeTaken;
	currentDeltaTime = timeTaken;
}
void MaximumEngine::Time::updateUpdateTime()
{
	uint32_t timeTaken = SDL_GetTicks() - lastTickTime - currentDeltaTime;
	updateTime = timeTaken;
	currentDeltaTime += timeTaken;
}
void MaximumEngine::Time::updateRenderTime()
{
	uint32_t timeTaken = SDL_GetTicks() - lastTickTime - currentDeltaTime;
	renderTime = timeTaken;
	currentDeltaTime += timeTaken;
}

//GETTERS
float MaximumEngine::Time::getDeltaTimeSeconds()
{
	return (float)deltaTime / 1000;
}
uint32_t MaximumEngine::Time::getDeltaTimeMilliSeconds()
{
	return deltaTime;
}
int MaximumEngine::Time::getFps()
{
	return fps;
}
uint32_t MaximumEngine::Time::getMiscTime()
{
	return miscTime;
}
uint32_t MaximumEngine::Time::getUpdateTime()
{
	return updateTime;
}
uint32_t MaximumEngine::Time::getRenderTime()
{
	return renderTime;
}

