#include "Debug.h"
#include "Log.h"
#include "Time.h"

#define DEBUG_UPDATE_TIME 50

//STATIC VARIABLES
TTF_Font* MaximumEngine::Debug::font = nullptr;
MaximumEngine::Debug::DebugText MaximumEngine::Debug::fps_t = MaximumEngine::Debug::DebugText(2, -4, "");
MaximumEngine::Debug::DebugText MaximumEngine::Debug::delta_t = MaximumEngine::Debug::DebugText(2, 16, "");
MaximumEngine::Debug::DebugText MaximumEngine::Debug::misc_t = MaximumEngine::Debug::DebugText(2, 76, "");
MaximumEngine::Debug::DebugText MaximumEngine::Debug::update_t = MaximumEngine::Debug::DebugText(2, 36, "");
MaximumEngine::Debug::DebugText MaximumEngine::Debug::render_t = MaximumEngine::Debug::DebugText(2, 56, "");
uint32_t MaximumEngine::Debug::lastUpdateTime = DEBUG_UPDATE_TIME;

void MaximumEngine::Debug::start()
{
	//load font
	font = TTF_OpenFont("C:/Fonts/clear-sans.regular.ttf", 18);
	if (font == nullptr) { ME_Error_Log(TTF_GetError()); }
}

void MaximumEngine::Debug::update()
{
	lastUpdateTime += MaximumEngine::Time::getDeltaTimeMilliSeconds();
	if (lastUpdateTime > DEBUG_UPDATE_TIME)
	{
		lastUpdateTime = 0;
		fps_t.text = "FPS:" + std::to_string(MaximumEngine::Time::getFps());
		delta_t.text = "Frame:" + std::to_string(MaximumEngine::Time::getDeltaTimeMilliSeconds()).substr(0, 5) + "ms";
		update_t.text = "Update:" + std::to_string(MaximumEngine::Time::getUpdateTime()).substr(0, 5) + "ms";
		render_t.text = "Render:" + std::to_string(MaximumEngine::Time::getRenderTime()).substr(0, 5) + "ms";
		misc_t.text = "Misc:" + std::to_string(MaximumEngine::Time::getMiscTime()).substr(0, 5) + "ms";
	}
}

void MaximumEngine::Debug::render(SDL_Renderer* renderer)
{
	if (font == nullptr) return;

	fps_t.render(renderer);
	delta_t.render(renderer);
	update_t.render(renderer);
	render_t.render(renderer);
	misc_t.render(renderer);
}

//DEBUG TEXT
MaximumEngine::Debug::DebugText::DebugText(int x, int y, std::string t) :x(x), y(y) , text(t){}

void MaximumEngine::Debug::DebugText::render(SDL_Renderer* renderer)
{
	if (text.size() == 0) { return; }
	const char* outputText = text.c_str();
	SDL_Surface* surface = TTF_RenderText_Solid(font, outputText, SDL_Color{ 0, 255, 0, 255 });
	if (surface == nullptr) { std::cout << TTF_GetError() << std::endl; return; }
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect rect;
	rect.x = x; rect.y = y;
	rect.w = surface->w; rect.h = surface->h;
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}
