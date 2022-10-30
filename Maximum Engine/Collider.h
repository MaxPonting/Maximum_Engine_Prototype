#pragma once
#include "Component.h"

namespace MaximumEngine
{
	class Collider : public Component
	{
	public:
		//VARIABLES
		bool renderOutline;
	protected:
		//METHODS	
		void virtual update(std::vector<Component*> comps, std::vector<Collider*> cols);
		void render(SDL_Renderer* renderer);
		void alertComponents(Collider* collider, std::vector<Component*> comps);
		std::vector<Collider*> getCloseColliders(std::vector<Collider*> cols);
		//GETTERS
		std::vector<Vector2> virtual getVertices();
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
	};

	class SquareCollider : public Collider
	{
	public:
		//VARIABLES
		float size;
	};

	class CircleCollider : public Collider
	{
	public:
		//VARIABLES
		float radius;
	protected:
		//METHODS
		void update(std::vector<Component*> comps, std::vector<Collider*> cols);
		float getLargestVertice();
	};
}

