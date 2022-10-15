#include "Engine.h"

//INIT STATIC MEMBERS
SDL_Renderer* MaximumEngine::Engine::renderer = NULL;
SDL_Window* MaximumEngine::Engine::window = NULL;
MaximumEngine::Engine::EngineState MaximumEngine::Engine::engineState = Null;
std::vector<MaximumEngine::GameObject*> MaximumEngine::Engine::gameObjects;
std::vector<MaximumEngine::Collider*> MaximumEngine::Engine::colliders;

void MaximumEngine::Engine::init() 
{
	//Load SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { ME_Error_Log(SDL_GetError()); }
	//Set EngineState
	engineState = Initialized;
}

void MaximumEngine::Engine::start()
{
	//Return If EngineState Is Not Initialized
	if (engineState != Initialized) { ME_Error_Log("Engine Not Initialized"); return; }

	//Create Window And Renderer
	window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ME_GetResolution().x, ME_GetResolution().y, SDL_WINDOW_SHOWN);
	if (window == NULL) { ME_Error_Log(SDL_GetError()); }
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) { ME_Error_Log(SDL_GetError()); }
	
	//Start loop
	engineLoop();
}

void MaximumEngine::Engine::start(int width, int height)
{
	//Set Resolution
	ME_SetResolution(width, height);
	start();
}

void MaximumEngine::Engine::engineLoop()
{
	//Return If EngineState Is Not Initialized
	if (engineState != Initialized) { ME_Error_Log("Engine Not Initialized"); return; }

	//Engine Loop
	engineState = Running;
	while (engineState == Running)
	{		
		Time::updateTime();
		events();
		Input::updateInput();
		update();
		render();
	}

	//Clean up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void MaximumEngine::Engine::update()
{
	//Call update in all GameObjects
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update();
	}
}

void MaximumEngine::Engine::render()
{	
	SDL_SetRenderDrawColor(renderer, ME_Screen_Colour.getR(), ME_Screen_Colour.getG(), ME_Screen_Colour.getB(), ME_Screen_Colour.getA());
	SDL_RenderClear(renderer);

	//Render FPS
	Time::logFPS();

	//Call render in all GameObjects
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->render(renderer);
	}

	SDL_RenderPresent(renderer);
}

void MaximumEngine::Engine::events()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			engineState = Null;
		}
	}
}