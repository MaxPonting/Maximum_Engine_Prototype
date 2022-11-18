#pragma once
#include "SDL.h"
#include "Vector2.h"
#include "Screen.h"
#include "Colour.h"
#include "Angle.h"
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
		//GETTERS
		float getRotation() const;
		Vector2 getPosition() const;
		float getLargestVertice() const;
		float getWidth() const;
		float getHeight() const;
		std::vector<Vector2> getVertices() const;
		std::vector<Vector2> getRawVertices() const;
		//SETTERS
		void setPosition(const Vector2 p);	
		void setColour(const Colour c);
		void setVertices(const std::vector<Vector2> verts);
		void setRotation(const float z);
	private:
		//METHODS
		void update();
		void render(SDL_Renderer* renderer);		
		void rotate();
		void tsSetPoints();
		//MEMBERS
		std::vector<Vector2> vertices;
		std::vector<Vector2> rotatedVertices;
		std::vector<Vector2> points;
		Angle rotation;	
		Vector2 position;
		Colour colour;
		bool scanlineNeeded;
		//FRIENDS
		friend class GameObject;
	};
}

#define ME_Geometry MaximumEngine::Geometry
#define ME_Geometry_Rectangle(w, h) { ME_Vector2(w/2, h/2), ME_Vector2(w/2, -h/2), ME_Vector2(-w/2, -h/2), ME_Vector2(-w/2, h/2) }
#define ME_Geometry_Isosceles(w, h) { ME_Vector2(0, -h/2), ME_Vector2(-w/2, h/2), ME_Vector2(w/2, h/2) }