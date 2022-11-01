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
		const GameObject& getGameObject();
		const Geometry& getGeometry();
	protected:
		//METHODS		
		void virtual init(GameObject* obj, Geometry* geo);
		void virtual start() {}
		void virtual update() {}
		void virtual update(std::vector<Component*> comps, std::vector<Collider*> cols) {};
		void virtual render(SDL_Renderer* renderer) {}		
		void virtual onCollision(Collider* collider) {}
		void virtual rotate(float z) {};
		//ACCESS TO GEOMETRY
		//Setters
		void setGPosition(const Vector2 pos);
		void setGRotation(const float z);
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

//SCRIPTING MACROS
#define G_POS MaximumEngine::Component::getGeometry().getPosition()
#define G_ROT MaximumEngine::Component::getGeometry().getRotation()
#define G_VERT MaximumEngine::Component::getGeometry().getVertices()
#define G_RAW_VERT MaximumEngine::Component::getGeometry().getRawVertices()


