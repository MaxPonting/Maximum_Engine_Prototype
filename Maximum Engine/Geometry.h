#pragma once
#include "SDL.h"
#include "Vector2.h"
#include "Screen.h"
#include "Colour.h"
#include <math.h>
#include <vector>

namespace MaximumEngine
{
	class Geometry
	{
	public:
		//CONSTRUCTOR
		Geometry();
		Geometry(std::vector<Vector2> vertices, Vector2 pos);
		//METHODS
		void setRotation(float z);
		void setVertices(std::vector<Vector2> v);
		//GETTERS
		float getRotation();
		float getLargestVertice();
		//VARIABLES
		Vector2 position;
		Colour colour;
	private:
		//METHODS
		void render(SDL_Renderer* renderer);		
		void rotate();
		void setPoints();
		//VARIABLES
		std::vector<Vector2> vertices;
		std::vector<Vector2> rotatedVertices;
		std::vector<Vector2> points;
		float rotation;	
		//FRIENDS
		friend class GameObject;
		friend class Collider;
	};
}

#define ME_Geometry MaximumEngine::Geometry
#define ME_Geometry_Rectangle(w, h) { ME_Vector2(w/2, h/2), ME_Vector2(w/2, -h/2), ME_Vector2(-w/2, -h/2), ME_Vector2(-w/2, h/2) }
#define ME_Geometry_Isosceles(w, h) { ME_Vector2(0, -h/2), ME_Vector2(-w/2, h/2), ME_Vector2(w/2, h/2) }