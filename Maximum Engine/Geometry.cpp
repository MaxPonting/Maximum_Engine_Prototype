#include "Geometry.h"
#include <cmath>
#include <algorithm>
#include "Log.h"
#include "Screen.h"

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
	//Scan line algo
	points.clear();

	//Get max and min y
	float yMax = rotatedVertices[0].y;
	float yMin = rotatedVertices[0].y;
	float xMax = rotatedVertices[0].x;
	float xMin = rotatedVertices[0].x;
	for (int i = 0; i < rotatedVertices.size(); i++)
	{
		if (rotatedVertices[i].y > yMax)
		{
			yMax = rotatedVertices[i].y;
		}
		if (rotatedVertices[i].y < yMin)
		{
			yMin = rotatedVertices[i].y;
		}
		if (rotatedVertices[i].x > xMax)
		{
			xMax = rotatedVertices[i].x;
		}
		if (rotatedVertices[i].x < xMin)
		{
			xMin = rotatedVertices[i].x;
		}
	}

	//List of intersections
	std::vector<float> inter;
	int i, j;
	float x;
	//loop each scan line
	for (float currentY = yMin; currentY < yMax; currentY++)
	{
		j = rotatedVertices.size() - 1;
		for (i = 0; i < rotatedVertices.size(); i++)
		{
			if ((rotatedVertices[i].y <= currentY && rotatedVertices[j].y >= currentY
			|| rotatedVertices[j].y <= currentY && rotatedVertices[i].y >= currentY)
			&& (rotatedVertices[i].y != rotatedVertices[j].y))
			{
				x = (rotatedVertices[i].x + (currentY - rotatedVertices[i].y) / (rotatedVertices[j].y - rotatedVertices[i].y) * (rotatedVertices[j].x - rotatedVertices[i].x));
				//Check intersection is not on an inward edge
				bool inwardEdge = false;
				if (rotatedVertices[i].y == currentY)
				{	
					if (i == rotatedVertices.size() - 1)
					{
						if((rotatedVertices[0].y >= currentY && rotatedVertices[j].y >= currentY) || (rotatedVertices[0].y <= currentY && rotatedVertices[j].y <= currentY))
						{
							inwardEdge = true;
						}
					}
					else
					{
						if ((rotatedVertices[i+1].y >= currentY && rotatedVertices[j].y >= currentY) || (rotatedVertices[i+1].y <= currentY && rotatedVertices[j].y <= currentY))
						{
							inwardEdge = true;
						}
					}						
				}
				else if (rotatedVertices[j].y == currentY)
				{
					if (j == 0)
					{
						if ((rotatedVertices[i].y >= currentY && rotatedVertices[rotatedVertices.size()-1].y >= currentY) || (rotatedVertices[i].y <= currentY && rotatedVertices[rotatedVertices.size() - 1].y <= currentY))
						{
							inwardEdge = true;
						}
					}
					else
					{
						if ((rotatedVertices[i].y >= currentY && rotatedVertices[j-1].y >= currentY) || (rotatedVertices[i].y <= currentY && rotatedVertices[j-1].y <= currentY))
						{
							inwardEdge = true;
						}
					}
				}
				if (!inwardEdge) 
				{ 
					bool inside = false;				
					for (std::vector<float>::iterator it = inter.begin(); it != inter.end(); it++)
					{
						if (*it == x) { inside = true; break; }
					}
					if (!inside) { inter.push_back(x); }			
				}
				//Add outline points
				points.push_back(Vector2(x, currentY));
			}			
			j = i;
		}
		//Sort intersections		
		sort(inter.begin(), inter.end());
		//Add points
		for (i = 0; i < inter.size(); i+=2)
		{		
			if (i          == inter.size() - 1) { break; }
			if (inter[i]   >= xMax) { break; }
			if (inter[i+1] > xMin)
			{
				if (inter[i]   < xMin) { inter[i]   = xMin; }
				if (inter[i+1] < xMin) { inter[i+1] = xMax; }
				for (x = inter[i] + 1; x < inter[i + 1]; x++)
				{
					//Add fill points
					points.push_back(Vector2(x, currentY));
				}
			}
		}
		//Clear intersections;
		inter.clear();
	}

	//Add horizontal outlines
	j = rotatedVertices.size() - 1;
	float x1, x2, min, max;
	for (i = 0; i < rotatedVertices.size(); i++)
	{
		if ((rotatedVertices[i].y == rotatedVertices[j].y))
		{
			x1 = rotatedVertices[i].x; x2 = rotatedVertices[j].x;
			min = std::min(x1, x2); max = std::max(x1, x2);
			for (int x = min; x <= max; x++)
			{
				points.push_back(Vector2(x, rotatedVertices[i].y));
			}
		}
		j = i;
	}
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

