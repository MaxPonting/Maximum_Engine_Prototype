#pragma once
#include "Vector2.h"
#include <vector>
#include "SDL.h"
#include <typeinfo>

namespace MaximumEngine
{
	class Engine;
	class GameObject;
	class Geometry;
	class Collider;
	class Component
	{
	public:
		//GETTERS
		GameObject* getGameObject();
		Geometry* getGeometry();
	protected:
		//METHODS		
		void virtual init(GameObject* obj, Geometry* geo);
		void virtual start() {}
		void virtual update() {}
		void virtual update(std::vector<Component*> comps, std::vector<Collider*> cols) {};
		void virtual render(SDL_Renderer* renderer) {}		
		void virtual onCollision(Collider* collider) {}
		void virtual rotate(float z) {};
		//VARIABLES
		float rotation;		
	private:
		//VARIABLES
		GameObject* gameObject;
		Geometry* geometry;
		//FRIENDS
		friend class GameObject;
		friend class Collider;
	};

	class Script : public Component
	{
	

	};
}


