#pragma once
#include "Vector2.h"
#include <vector>

namespace MaximumEngine
{
	class Algorithm
	{
	public:
		static std::vector<Vector2> fillPolygon(std::vector<Vector2> verts);
		static std::vector<Vector2> fillPolygonThreaded(std::vector<Vector2> verts);
	private:
		static std::vector<Vector2> scanline(std::vector<Vector2> verts, float yMin, float yMax, float xMin, float xMax);
	};

}


