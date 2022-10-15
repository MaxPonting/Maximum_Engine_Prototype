#include "Time.h"
#include "Log.h"

uint32_t MaximumEngine::Time::delta = 0;
uint32_t MaximumEngine::Time::lastTickTime = 0;
int MaximumEngine::Time::fps = 0;
bool MaximumEngine::Time::showFPS = true;

//METHODS
void MaximumEngine::Time::updateTime()
{
	uint32_t tickTime = SDL_GetTicks();
	delta = tickTime - lastTickTime;
	lastTickTime = tickTime;
	if (delta != 0) { fps = 1000 / delta; }
	else { fps = 1000; }
	
}
void MaximumEngine::Time::logFPS()
{
	if (!showFPS) { return; }
	std::cout << "[Maximum Engine][FPS] " << fps << std::endl;
}

//GETTERS
double MaximumEngine::Time::getDeltaTime()
{
	return (double)delta / 1000;
}

