#include "Algorithm.h"
#include <algorithm>
#include <thread>
#include <future>

//POLYGON FILLING
std::vector<ME_Vector2> MaximumEngine::Algorithm::fillPolygon(std::vector<Vector2> verts)
{
	std::vector<Vector2> points;

	//Get max and min y
	float yMax = verts[0].y;
	float yMin = verts[0].y;
	float xMax = verts[0].x;
	float xMin = verts[0].x;
	for (int i = 0; i < verts.size(); i++)
	{
		if (verts[i].y > yMax)
		{
			yMax = verts[i].y;
		}
		if (verts[i].y < yMin)
		{
			yMin = verts[i].y;
		}
		if (verts[i].x > xMax)
		{
			xMax = verts[i].x;
		}
		if (verts[i].x < xMin)
		{
			xMin = verts[i].x;
		}
	}

	std::vector<float> inter;
	int i, j;
	float x;
	//loop each scan line
	for (float currentY = yMin; currentY < yMax; currentY++)
	{
		j = verts.size() - 1;
		for (i = 0; i < verts.size(); i++)
		{
			if ((verts[i].y <= currentY && verts[j].y >= currentY
				|| verts[j].y <= currentY && verts[i].y >= currentY)
				&& (verts[i].y != verts[j].y))
			{
				x = (verts[i].x + (currentY - verts[i].y) / (verts[j].y - verts[i].y) * (verts[j].x - verts[i].x));
				//Check intersection is not on an inward edge
				bool inwardEdge = false;
				if (verts[i].y == currentY)
				{
					if (i == verts.size() - 1)
					{
						if ((verts[0].y >= currentY && verts[j].y >= currentY) || (verts[0].y <= currentY && verts[j].y <= currentY))
						{
							inwardEdge = true;
						}
					}
					else
					{
						if ((verts[i + 1].y >= currentY && verts[j].y >= currentY) || (verts[i + 1].y <= currentY && verts[j].y <= currentY))
						{
							inwardEdge = true;
						}
					}
				}
				else if (verts[j].y == currentY)
				{
					if (j == 0)
					{
						if ((verts[i].y >= currentY && verts[verts.size() - 1].y >= currentY) || (verts[i].y <= currentY && verts[verts.size() - 1].y <= currentY))
						{
							inwardEdge = true;
						}
					}
					else
					{
						if ((verts[i].y >= currentY && verts[j - 1].y >= currentY) || (verts[i].y <= currentY && verts[j - 1].y <= currentY))
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
		for (i = 0; i < inter.size(); i += 2)
		{
			if (i == inter.size() - 1) { break; }
			if (inter[i] >= xMax) { break; }
			if (inter[i + 1] > xMin)
			{
				if (inter[i] < xMin) { inter[i] = xMin; }
				if (inter[i + 1] < xMin) { inter[i + 1] = xMax; }
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
	i = 0;
	j = verts.size() - 1;
	float x1, x2, min, max;
	for (i = 0; i < verts.size(); i++)
	{
		if ((verts[i].y == verts[j].y))
		{
			x1 = verts[i].x; x2 = verts[j].x;
			min = std::min(x1, x2); max = std::max(x1, x2);
			for (int x = min; x <= max; x++)
			{
				points.push_back(Vector2(x, verts[i].y));
			}
		}
		j = i;
	}

	return points;
}
std::vector<ME_Vector2> MaximumEngine::Algorithm::fillPolygonEdgeBucket(std::vector<Vector2> verts)
{
	std::vector<Vector2> points;

	//Get max and min y
	float yMax = verts[0].y;
	float yMin = verts[0].y;
	float xMax = verts[0].x;
	float xMin = verts[0].x;
	for (int i = 0; i < verts.size(); i++)
	{
		if (verts[i].y > yMax)
		{
			yMax = verts[i].y;
		}
		if (verts[i].y < yMin)
		{
			yMin = verts[i].y;
		}
		if (verts[i].x > xMax)
		{
			xMax = verts[i].x;
		}
		if (verts[i].x < xMin)
		{
			xMin = verts[i].x;
		}
	}

	//Scanline
	std::vector<float> inter;
	float otherVerticeY = 0;
	bool isOtherVertice = false;
	int i, j;
	float x;
	//Create edge bucket
	std::vector<Edge> edges;
	j = verts.size() - 1;
	for (i = 0; i < verts.size(); i++)
	{
		edges.push_back(Edge(verts[j], verts[i]));
		j = i;
	}
	//loop each scan line
	for (float currentY = yMin; currentY < yMax; currentY++)
	{
		//Check intersections
		for (auto it = edges.begin(); it != edges.end();)
		{
			if ((it->v1.y <= currentY && it->v2.y >= currentY
			  || it->v2.y <= currentY && it->v1.y >= currentY))			
			{
				x = (it->v1.x + (currentY - it->v1.y) / (it->v2.y - it->v1.y) * (it->v2.x - it->v1.x));
				//Check intersection is not on an inward edge
				bool inwardEdge = false;
				if (it->v1.y == currentY)
				{
					if (isOtherVertice)
					{
						if ((it->v2.y >= currentY && otherVerticeY >= currentY) || (it->v2.y <= currentY && otherVerticeY <= currentY)) inwardEdge = true;
					}
					else
					{
						otherVerticeY = it->v1.y;
						isOtherVertice = true;
						
					}
				}
				else if (it->v2.y == currentY)
				{
					if (isOtherVertice)
					{
						if ((it->v1.y >= currentY && otherVerticeY >= currentY) || (it->v1.y <= currentY && otherVerticeY <= currentY)) inwardEdge = true;
					}
					else
					{
						otherVerticeY = it->v2.y;
						isOtherVertice = true;
						
					}
				}
				if (!inwardEdge)
				{
					bool inside = false;
					for (std::vector<float>::iterator it2 = inter.begin(); it2 != inter.end(); it2++)
					{
						if (*it2 == x) { inside = true; break; }
					}
					if (!inside) { inter.push_back(x); }
				}
				//Add outline points				
				points.push_back(Vector2(x, currentY));
				++it;
			}
			else if (it->v1.y < currentY && it->v2.y < currentY)
			{
				it = edges.erase(it);
			}
			else ++it;
		}		
		//Sort intersections		
		sort(inter.begin(), inter.end());
		//Add points
		for (i = 0; i < inter.size(); i += 2)
		{
			if (i == inter.size() - 1) { break; }
			if (inter[i] >= xMax) { break; }
			if (inter[i + 1] > xMin)
			{
				if (inter[i] < xMin) { inter[i] = xMin; }
				if (inter[i + 1] < xMin) { inter[i + 1] = xMax; }
				for (x = inter[i] + 1; x < inter[i + 1]; x++)
				{
					//Add fill points
					points.push_back(Vector2(x, currentY));
				}
			}
		}
		//Clear intersections;
		inter.clear();
		isOtherVertice = false;
	}

	//Add horizontal outlines
	i = 0;
	j = verts.size() - 1;
	float x1, x2, min, max;
	for (i = 0; i < verts.size(); i++)
	{
		if ((verts[i].y == verts[j].y))
		{
			x1 = verts[i].x; x2 = verts[j].x;
			min = std::min(x1, x2); max = std::max(x1, x2);
			for (int x = min; x <= max; x++)
			{
				points.push_back(Vector2(x, verts[i].y));
			}
		}
		j = i;
	}

	return points;
}

//COLLISION DETECTION
bool MaximumEngine::Algorithm::isCollisionPolygon(const std::vector<Vector2> verts1, const std::vector<Vector2> verts2, const Vector2 p1, const Vector2 p2)
{
	//Checks if any edges intersect
	int j1 = verts1.size() - 1;
	for (int c1 = 0; c1 < verts1.size(); c1++)
	{
		int j2 = verts2.size() - 1;
		for (int c2 = 0; c2 < verts2.size(); c2++)
		{
			Vector2 point1 = p1 + verts1[j1];
			Vector2 point2 = p1 + verts1[c1];
			Vector2 point3 = p2 + verts2[j2];
			Vector2 point4 = p2 + verts2[c2];
			if (isIntersect(point1, point2, point3, point4))
			{
				return true;
			}
			j2 = c2;
		}
		j1 = c1;
	}
	return false;
	//Time Complexity O(n^2)
}
bool MaximumEngine::Algorithm::isCollisionPolygonRectangle(const std::vector<Vector2> vertices, const float height, const float width, const Vector2 p1, const Vector2 p2) { return false; }
bool MaximumEngine::Algorithm::isCollisionPolygonSquare(const std::vector<Vector2> vertices, const float size, const Vector2 p1, const Vector2 p2) { return false; }
bool MaximumEngine::Algorithm::isCollisionPolygonCircle(const std::vector<Vector2> vertices, const float radius, const Vector2 p1, const Vector2 p2) { return false; }
bool MaximumEngine::Algorithm::isCollisionRectangle(const float height1, const float width1, const float height2, const float width2, const Vector2 p1, const Vector2 p2) { return false; }
bool MaximumEngine::Algorithm::isCollisionRectangleSquare(const float height, const float width, const float size, const Vector2 p1, const Vector2 p2) { return false; }
bool MaximumEngine::Algorithm::isCollisionRectangleCircle(const float height, const float width, const float radius, const Vector2 p1, const Vector2 p2) { return false; }
bool MaximumEngine::Algorithm::isCollisionSquare(const float size1, const float size2, const Vector2 p1, const Vector2 p2) { return false; }
bool MaximumEngine::Algorithm::isCollisionSquareCircle(const float size, const float circle, const Vector2 p1, const Vector2 p2) { return false; }

//POINT LINE INTERSECTION
bool MaximumEngine::Algorithm::isIntersect(Vector2 p1, Vector2 q1, Vector2 p2, Vector2 q2)
{
	int o1 = getLineOrientation(p1, q1, p2);
	int o2 = getLineOrientation(p1, q1, q2);
	int o3 = getLineOrientation(p2, q2, p1);
	int o4 = getLineOrientation(p2, q2, q1);

	//General Case
	if (o1 != o2 && o3 != o4) return true;

	//Special Cases
	if (o1 == 0 && onLineSegment(p1, p2, q1)) return true;
	if (o2 == 0 && onLineSegment(p1, q2, q1)) return true;
	if (o3 == 0 && onLineSegment(p2, p1, q2)) return true;
	if (o4 == 0 && onLineSegment(p2, q1, q2)) return true;

	return false;
}
int MaximumEngine::Algorithm::getLineOrientation(Vector2 p, Vector2 q, Vector2 r)
{
	int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;

	return (val > 0) ? 1 : 2;
}
bool MaximumEngine::Algorithm::onLineSegment(Vector2 p, Vector2 q, Vector2 r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y)) return true;

	return false;
}