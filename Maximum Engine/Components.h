#pragma once
#include "Vector2.h"
#include <vector>

namespace MaximumEngine
{
	class Engine;
	class GameObject;
	class Geometry;
	class Component
	{
	public:
		//GETTERS
		GameObject* getGameObject();
		Geometry* getGeometry();
	protected:
		//METHODS		
		void virtual start() {}
		void virtual update() {}
		void virtual render() {}		
		//FRIENDS
		friend class GameObject;
	private:
		//METHODS
		void init(GameObject* obj, Geometry* geo);
		//VARIABLES
		GameObject* gameObject;
		Geometry* geometry;
	};

	class Collider : public Component
	{
	protected:
		//METHODS
		void update() override;
		void alertScripts(Collider* collider);
	private:
		//METHODS
		bool doIntersect(Vector2 p1, Vector2 q1, Vector2 p2, Vector2 q2);
		int lineOrientation(Vector2 p, Vector2 q, Vector2 r);
		bool onLineSegment(Vector2 p, Vector2 q, Vector2 r);

	};

	class Script : public Component
	{
	protected:
		//METHODS
		void virtual onCollision(Collider* collider) {}
	private:
		//FRIENDS
		friend class Collider;
	};
}


