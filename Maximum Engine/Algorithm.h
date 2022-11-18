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
		static bool isCollisionPolygonCircle(const std::vector<Vector2> vertices, const float radius, const Vector2 p1, const Vector2 p2);
		static bool isCollisionRectangle(const float height1, const float width1, const float height2, const float width2, const Vector2 p1, const Vector2 p2);
		static bool isCollisionRectangleCircle(const float height, const float width, const float radius, const Vector2 p1, const Vector2 p2);
		//Point Line Intersection
		static bool isIntersect(Vector2 p1, Vector2 q1, Vector2 p2, Vector2 q2);
		static int getLineOrientation(Vector2 p, Vector2 q, Vector2 r);
		static bool onLineSegment(Vector2 p, Vector2 q, Vector2 r);
	};
}


