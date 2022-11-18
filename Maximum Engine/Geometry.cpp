#include "Geometry.h"
#include <cmath>
#include <algorithm>
#include "Log.h"
#include "Screen.h"
#include "Algorithm.h"
#include "EngineThreadPool.h"
#include "Timer.h"

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
	tsSetPoints();
}
MaximumEngine::Geometry::Geometry(std::vector<Vector2> vertices, Vector2 pos) :vertices(vertices), position(pos), rotatedVertices(vertices), rotation(0)
{ 
	tsSetPoints(); 
}

//METHODS
void MaximumEngine::Geometry::update()
{
	if (scanlineNeeded == true)
	{
		//Run scanline on thread
		if (EngineThreadPool::enqueue([=] { tsSetPoints(); }));
		else tsSetPoints();
	}
	scanlineNeeded = false;
}
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

	const int size = points.size();
	SDL_FPoint* drawPoints = new SDL_FPoint[size];
	for (int i = 0; i < size; i++)
	{
		drawPoints[i] = { points[i].x + position.x, points[i].y + position.y };
	}
	SDL_RenderDrawPointsF(renderer, drawPoints, size);
	delete[] drawPoints;
}
void MaximumEngine::Geometry::rotate()
{
	rotatedVertices.clear();
	//Rotate each vertice
	for (int i = 0; i < vertices.size(); i++)
	{
		Vector2 rotatedVector;
		rotatedVector.x = vertices[i].x * cos(rotation.getRad()) - sin(rotation.getRad()) * vertices[i].y;
		rotatedVector.y = vertices[i].x * sin(rotation.getRad()) + cos(rotation.getRad()) * vertices[i].y;
		rotatedVertices.push_back(rotatedVector);
	}
}
void MaximumEngine::Geometry::tsSetPoints()
{
	points = Algorithm::fillPolygon(rotatedVertices);
}

//GETTERS
float MaximumEngine::Geometry::getRotation() const
{
	return rotation.getDeg();
}
float MaximumEngine::Geometry::getLargestVertice() const
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
ME_Vector2 MaximumEngine::Geometry::getPosition() const
{
	return position;
}
float MaximumEngine::Geometry::getWidth() const
{
	float maxX = 0; float minX = 0;
	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].x > maxX) maxX = vertices[i].x;
		if (vertices[i].x < minX) minX = vertices[i].x;
	}

	return maxX - minX;
}
float MaximumEngine::Geometry::getHeight() const
{
	float maxY = 0; float minY = 0;
	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].y > maxY) maxY = vertices[i].y;
		if (vertices[i].y < minY) minY = vertices[i].y;
	}

	return maxY - minY;
}
std::vector<ME_Vector2> MaximumEngine::Geometry::getVertices() const
{
	return rotatedVertices;
}
std::vector<ME_Vector2> MaximumEngine::Geometry::getRawVertices() const
{
	return vertices;
}

//SETTERS
void MaximumEngine::Geometry::setPosition(const Vector2 p) 
{
	position = p;
}
void MaximumEngine::Geometry::setVertices(const std::vector<Vector2> verts) 
{
	vertices = verts;
	rotate();
	scanlineNeeded = true;
}
void MaximumEngine::Geometry::setRotation(const float z)
{
	rotation = z;
	rotate();
	scanlineNeeded = true;
}
void MaximumEngine::Geometry::setColour(const Colour c)
{
	colour = c;
}

