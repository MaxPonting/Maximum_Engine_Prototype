#pragma once
#include "SDL.h"
#include <bitset>
#include "Geometry.h"
#include "Vector2.h"
#include "Components.h"

#define MAX_COMPONENTS 12

namespace MaximumEngine
{
	class GameObject
	{
	public:
		//CONSTRUCTOR
		GameObject();			
		//METHODS
		//ECS
		template <class T> T* addComponent()
		{
			if (!std::is_base_of<Component, T>::value) { return nullptr; }
			T* t = new T();
			Component* component = (Component*)(t);
			component->init(this, &geometry);
			if (std::is_base_of<Collider, T>::value)
			{
				MaximumEngine::Engine::colliders.push_back((Collider*)component);
			}
			components.push_back(t);
			return t;
		}
		//VARIABLES
		Geometry geometry;		
	private:
		//METHODS
		void render(SDL_Renderer* renderer);	
		void update();
		void rotateComponents(float z);
		//VARIABLES
		std::vector<Component*> components;
		//FRIENDS
		friend class Engine;
		friend class Collider;
	};
}

#define ME_GameObject MaximumEngine::GameObject

