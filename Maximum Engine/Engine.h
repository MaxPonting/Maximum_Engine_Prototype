#pragma once
#include "SDL.h"
#include "Log.h"
#include "GameObject.h"
#include "Vector2.h"
#include "Screen.h"
#include "Time.h"
#include "Input.h"
#include "Components.h"
#include <vector>

namespace MaximumEngine
{
	class Engine
	{
	public:
		//METHODS
		static void init();
		static void start();
		static void start(int width, int height);
	private:
		//METHODS
		static void engineLoop();		
		static void update();
		static void render();
		static void events();
		//ENUMS
		enum EngineState { Null, Initialized, Running };
		//VARIABLES
		static SDL_Renderer* renderer;
		static SDL_Window* window;
		static EngineState engineState;
		static std::vector<GameObject*> gameObjects;
		static std::vector<Collider*> colliders;
		//FRIENDS
		friend class GameObject;
		friend class Collider;
		friend class CircleCollider;
	};
}

//MACROS
//Methods
#define ME_Engine MaximumEngine::Engine
#define ME_Init() MaximumEngine::Engine::init()
#define ME_Start() MaximumEngine::Engine::start()
#define ME_Start_With_Resolution(w, h) MaximumEngine::Engine::start(w, h)
//Variables
#define ME_ENGINE_COLLIDERS MaximumEngine::Engine::colliders


