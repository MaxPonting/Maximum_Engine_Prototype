#include "Engine.h"
#include "Debug.h"
#include <thread>

//INIT STATIC MEMBERS
SDL_Renderer* MaximumEngine::Engine::renderer = NULL;
SDL_Window* MaximumEngine::Engine::window = NULL;
MaximumEngine::Engine::EngineState MaximumEngine::Engine::engineState = Null;
std::vector<MaximumEngine::GameObject*> MaximumEngine::Engine::gameObjects;
std::vector<MaximumEngine::Collider*> MaximumEngine::Engine::colliders;

void MaximumEngine::Engine::init() 
{
	if (engineState == Initialized) { ME_Error_Log("Engine already initialized!"); return; }
	//Load SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { ME_Error_Log(SDL_GetError()); }
	//Load TTF
	if (TTF_Init() != 0) { ME_Error_Log(TTF_GetError()); }
	//Set EngineState
	engineState = Initialized;
}

void MaximumEngine::Engine::initWithThreading()
{
	if (engineState == Initialized) { ME_Error_Log("Engine already initialized!"); return; }
	init();
	//Init Thread Pool
	EngineThreadPool::init();
}

void MaximumEngine::Engine::start()
{
	//Return If EngineState Is Not Initialized
	if (engineState != Initialized) { ME_Error_Log("Engine Not Initialized"); return; }

	//Create Window And Renderer
	window = SDL_CreateWindow("Maximum Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ME_GetResolution().x, ME_GetResolution().y, SDL_WINDOW_SHOWN);
	if (window == NULL) { ME_Error_Log(SDL_GetError()); }
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (renderer == NULL) { ME_Error_Log(SDL_GetError()); }

	//Start debug
	Debug::start();
	
	//Start engine loop
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
		//Events
		events();

		//Input
		Input::updateInput();

		//Misc Time
		Time::updateMiscTime();

		//Update
		update();
		Time::updateUpdateTime();

		//Render
		render();
		Time::updateRenderTime();

		//Overall Time
		Time::updateOverallTime();
	}

	//Clean up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void MaximumEngine::Engine::update()
{
	//Update debug
	Debug::update();
	
	//Update Gameobject components
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update(colliders);		
	}

	//Update GameObject geometry
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->updateGeometry();
	}

	//Wait for threads
	EngineThreadPool::wait();
}

void MaximumEngine::Engine::render()
{	
	SDL_SetRenderDrawColor(renderer, ME_Screen_Colour.getR(), ME_Screen_Colour.getG(), ME_Screen_Colour.getB(), ME_Screen_Colour.getA());
	SDL_RenderClear(renderer);

	//Call render in all GameObjects
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->render(renderer);
	}

	//Render debug
	Debug::render(renderer);

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

