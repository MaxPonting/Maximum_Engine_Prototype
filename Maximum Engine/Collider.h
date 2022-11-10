#pragma once
#include "Component.h"

namespace MaximumEngine
{
	class CircleCollider;
	class SquareCollider;
	class RectangleCollider;
	class PolygonCollider;
	class Collider : public Component
	{
	public:
		//VARIABLES
		bool renderOutline;
		//GETTERS
		std::vector<Vector2> virtual getVertices();
		const Collider virtual getSelf();
	protected:
		//METHODS	
		void virtual update(std::vector<Component*> comps, std::vector<Collider*> cols);
		void render(SDL_Renderer* renderer);		
		void alertComponents(Collider* collider, std::vector<Component*> comps);
		std::vector<Collider*> getCloseColliders(std::vector<Collider*> cols);
		//COLLISON CHECKING
		bool virtual isCollision(Collider collider);
		bool virtual isCollision(PolygonCollider collider);
		bool virtual isCollision(RectangleCollider collider);
		bool virtual isCollision(SquareCollider collider);
		bool virtual isCollision(CircleCollider collider);
		//GETTERS		
		float virtual getLargestVertice();
	private:
		//METHODS	
		bool doIntersect(Vector2 p1, Vector2 q1, Vector2 p2, Vector2 q2);
		int lineOrientation(Vector2 p, Vector2 q, Vector2 r);
		bool onLineSegment(Vector2 p, Vector2 q, Vector2 r);
	};

	class PolygonCollider : public Collider
	{
	public:
		//GETTERS
		std::vector<Vector2> getVertices();
		//SETTERS
		void setVertices(std::vector<Vector2> v);
	protected:
		//METHODS
		void start();
		void rotate(float z);
		//GETTERS
		float virtual getLargestVertice();
	private:
		//VARIABLES
		std::vector<Vector2> vertices;
		std::vector<Vector2> rotatedVertices;
	};

	class RectangleCollider : public Collider
	{
	public:
		//VARIABLES
		float height, width;
	protected:
		//COLLISON CHECKING
		bool virtual isCollision(Collider collider);
		bool virtual isCollision(PolygonCollider collider);
		bool virtual isCollision(RectangleCollider collider);
		bool virtual isCollision(SquareCollider collider);
		bool virtual isCollision(CircleCollider collider);
	};

	class SquareCollider : public Collider
	{
	public:
		//VARIABLES
		float size;
	protected:
		//COLLISON CHECKING
		bool virtual isCollision(Collider collider);
		bool virtual isCollision(PolygonCollider collider);
		bool virtual isCollision(RectangleCollider collider);
		bool virtual isCollision(SquareCollider collider);
		bool virtual isCollision(CircleCollider collider);
	};

	class CircleCollider : public Collider
	{
	public:
		//VARIABLES
		float radius;
	protected:
		//METHODS
		void start();
		//GETTERS
		float getLargestVertice();
		//COLLISON CHECKING
		bool virtual isCollision(Collider collider);
		bool virtual isCollision(PolygonCollider collider);
		bool virtual isCollision(RectangleCollider collider);
		bool virtual isCollision(SquareCollider collider);
		bool virtual isCollision(CircleCollider collider);
	};
}

