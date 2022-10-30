#include "Algorithm.h"
#include <algorithm>
#include <thread>
#include <future>

//POLYGON FILL NO THREADS
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

	//Run scanline
	points = scanline(verts, yMin, yMax, xMin, xMax);

	//Add horizontal outlines
	int i = 0;
	int j = verts.size() - 1;
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

//POLYGON FILL WITH THREADS
std::vector<ME_Vector2> MaximumEngine::Algorithm::fillPolygonThreaded(std::vector<Vector2> verts)
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

	//Run scanline with threads
	const int threadCount = std::thread::hardware_concurrency();
	std::vector<std::future<std::vector<Vector2>>> threads;
	float portion = (yMax - yMin) / threadCount;		
	float currentY = yMin;
	for (int i = 0; i < threadCount; i++)
	{
		threads.push_back(std::async(scanline, verts, currentY, currentY + portion, xMin, xMax));
		currentY += portion;
	}
	for (int i = 0; i < threadCount; i++)
	{
		std::vector<Vector2> newPoints = threads[i].get();
		points.insert(points.begin(), newPoints.begin(), newPoints.end());
	}
	

	//Add horizontal outlines
	int i = 0;
	int j = verts.size() - 1;
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

//SCANLINE
std::vector<ME_Vector2> MaximumEngine::Algorithm::scanline(std::vector<Vector2> verts, float yMin, float yMax, float xMin, float xMax)
{
	std::vector<Vector2> points;
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

	return points;
}

