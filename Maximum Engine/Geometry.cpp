#include "Geometry.h"
#include <cmath>
#include <algorithm>
#include "Log.h"
#include "Screen.h"
#include "Algorithm.h"


//CONSTRUCTOR
MaximumEngine::Geometry::Geometry() :position(Vector2(10, 10)), rotation(0), colour(Colour())
{
	//No Vertices Specificed 
	//Create Square
	vertices.push_back(Vector2(10, 10));
	vertices.push_back(Vector2(10, -10));
	vertices.push_back(Vector2(-10, -10));
	vertices.push_back(Vector2(-10, 10));
	//Set Rotated Vertices
	rotatedVertices = vertices;
	//Set Points
	setPoints();
}
MaximumEngine::Geometry::Geometry(std::vector<Vector2> vertices, Vector2 pos) :vertices(vertices), position(pos), rotatedVertices(vertices), rotation(0)
{ 
	setPoints(); 
}

//METHODS
void MaximumEngine::Geometry::render(SDL_Renderer* renderer)
{
	//Return if all vertices off screen
	bool onScreen = false;
	for (int i = 0; i < rotatedVertices.size(); i++)
	{
		Vector2 vector = (rotatedVertices[i] + position);
		Vector2* pointer = &vector;
		if (ME_OnScreen(pointer)) { onScreen = true; }
	}
	if (!onScreen) { return; }

	//Set Draw Colour
	SDL_SetRenderDrawColor(renderer, colour.getR(), colour.getG(), colour.getB(), colour.getA());

	//Render points
	const int size = points.size();
	SDL_Point *drawPoints = new SDL_Point[size];
	for (int i = 0; i < size; i++)
	{		
	    drawPoints[i] = { (int)(points[i].x + position.x), (int)(points[i].y + position.y) };		
	}
	SDL_RenderDrawPoints(renderer, drawPoints, size);
	delete[] drawPoints;
}
void MaximumEngine::Geometry::rotate()
{
	rotatedVertices.clear();
	//Rotate each vertice
	for (int i = 0; i < vertices.size(); i++)
	{
		Vector2 rotatedVector;
		rotatedVector.x = vertices[i].x * cos(rotation) - sin(rotation) * vertices[i].y;
		rotatedVector.y = vertices[i].x * sin(rotation) + cos(rotation) * vertices[i].y;
		rotatedVertices.push_back(rotatedVector);
	}
}
void MaximumEngine::Geometry::setRotation(float z) 
{
	float rotationChange = rotation - z;
	rotation = z;
	rotate();
	setPoints();
}
void MaximumEngine::Geometry::setVertices(std::vector<Vector2> v)
{
	vertices = v;
	rotate();
	setPoints();
}
void MaximumEngine::Geometry::setPoints()
{
	//No Threading
	//points = Algorithm::fillPolygon(rotatedVertices);
	//Threading
	points = Algorithm::fillPolygonThreaded(rotatedVertices);
}


//GETTERS
float MaximumEngine::Geometry::getRotation()
{
	return rotation;
}
float MaximumEngine::Geometry::getLargestVertice()
{
	float largest = 0;
	for (int i = 0; i < vertices.size(); i++)
	{
		float current = vertices[i].getMagnitude();
		if (current > largest)
		{
			largest = current;
		}
	}
	return largest;
}

