#include "Time.h"
#include "Log.h"

std::chrono::time_point<std::chrono::high_resolution_clock> MaximumEngine::Time::lastTickTime = std::chrono::high_resolution_clock::now();
float MaximumEngine::Time::deltaTime = 0;
float MaximumEngine::Time::currentDeltaTime = 0;
float MaximumEngine::Time::renderTime = 0;
float MaximumEngine::Time::updateTime = 0;
float MaximumEngine::Time::miscTime = 0;
int MaximumEngine::Time::fps = 0;

//METHODS
void MaximumEngine::Time::updateOverallTime()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> tickTime = std::chrono::high_resolution_clock::now();
	long duration = std::chrono::time_point_cast<std::chrono::microseconds>(tickTime).time_since_epoch().count() -
    std::chrono::time_point_cast<std::chrono::microseconds>(lastTickTime).time_since_epoch().count();
	deltaTime = duration * 0.001;
	lastTickTime = tickTime;
	if (deltaTime != 0) { fps = 1000 / deltaTime; }
	else { fps = 1000; }
}
void MaximumEngine::Time::updateMiscTime()
{
	long duration = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() -
	std::chrono::time_point_cast<std::chrono::microseconds>(lastTickTime).time_since_epoch().count();
	float timeTaken = duration * 0.001;
	miscTime = timeTaken;
	currentDeltaTime = timeTaken;
}
void MaximumEngine::Time::updateUpdateTime()
{
	long duration = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() -
	std::chrono::time_point_cast<std::chrono::microseconds>(lastTickTime).time_since_epoch().count();
	float timeTaken = duration * 0.001;
	timeTaken -= currentDeltaTime;
	updateTime = timeTaken;
	currentDeltaTime += timeTaken;
}
void MaximumEngine::Time::updateRenderTime()
{
	long duration = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() -
	std::chrono::time_point_cast<std::chrono::microseconds>(lastTickTime).time_since_epoch().count();
	float timeTaken = duration * 0.001;
	timeTaken -= currentDeltaTime;
	renderTime = timeTaken;
	currentDeltaTime += timeTaken;
}

//GETTERS
float MaximumEngine::Time::getDeltaTimeSeconds()
{
	return (float)deltaTime / 1000;
}
float MaximumEngine::Time::getDeltaTimeMilliSeconds()
{
	return deltaTime;
}
int MaximumEngine::Time::getFps()
{
	return fps;
}
float MaximumEngine::Time::getMiscTime()
{
	return miscTime;
}
float MaximumEngine::Time::getUpdateTime()
{
	return updateTime;
}
float MaximumEngine::Time::getRenderTime()
{
	return renderTime;
}

