#pragma once
#include "SDL.h"
#include <bitset>
#include "Geometry.h"
#include "Vector2.h"
#include "Component.h"
#include "Collider.h"

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
				Engine::colliders.push_back((Collider*)component);
			}
			components.push_back(t);
			return t;
		}
	    //GETTERS
		const Geometry& getGeometry();
		//SETTERS
		void setGeometry(const Geometry);
	private:
		//METHODS
		void render(SDL_Renderer* renderer);	
		void update(std::vector<Collider*> cols);
		void updateGeometry();
		//VARIABLES
		Geometry geometry;
		std::vector<Component*> components;
		//FRIENDS
		friend class Engine;
	};
}

#define ME_GameObject MaximumEngine::GameObject

