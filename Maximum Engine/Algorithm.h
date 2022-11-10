#pragma once
#include "Vector2.h"
#include "Edge.h"
#include <vector>

namespace MaximumEngine
{
	class Algorithm
	{
	public:
		//Polygon Filling
		static std::vector<Vector2> fillPolygon(const std::vector<Vector2> verts);
		static std::vector<Vector2> fillPolygonEdgeBucket(const std::vector<Vector2> verts);
		//Collision Detection
		static bool isCollisionPolygon(const std::vector<Vector2> verts1, const std::vector<Vector2> verts2, const Vector2 p1, const Vector2 p2);
		static bool isCollisionPolygonRectangle(const std::vector<Vector2> vertices, const float height, const float width, const Vector2 p1, const Vector2 p2);
		static bool isCollisionPolygonSquare(const std::vector<Vector2> vertices, const float size, const Vector2 p1, const Vector2 p2);
		static bool isCollisionPolygonCircle(const std::vector<Vector2> vertices, const float radius, const Vector2 p1, const Vector2 p2);
		static bool isCollisionRectangle(const float height1, const float width1, const float height2, const float width2, const Vector2 p1, const Vector2 p2);
		static bool isCollisionRectangleSquare(const float height, const float width, const float size, const Vector2 p1, const Vector2 p2);
		static bool isCollisionRectangleCircle(const float height, const float width, const float radius, const Vector2 p1, const Vector2 p2);
		static bool isCollisionSquare(const float size1, const float size2, const Vector2 p1, const Vector2 p2);
		static bool isCollisionSquareCircle(const float size, const float circle, const Vector2 p1, const Vector2 p2);
		//Point Line Intersection
		static bool isIntersect(Vector2 p1, Vector2 q1, Vector2 p2, Vector2 q2);
		static int getLineOrientation(Vector2 p, Vector2 q, Vector2 r);
		static bool onLineSegment(Vector2 p, Vector2 q, Vector2 r);
	private:
		static std::vector<Vector2> scanline(const std::vector<Vector2> verts, const float yMin, const float yMax, const float xMin, const float xMax);
	};
}


