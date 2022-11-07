#pragma once
#include "Vector2.h"

namespace MaximumEngine
{
	struct Edge
	{
		//CONSTRUCTORS
		Edge();
		Edge(Vector2 v1, Vector2 v2);
		//MEMBERS
		Vector2 v1, v2;
	};
}


