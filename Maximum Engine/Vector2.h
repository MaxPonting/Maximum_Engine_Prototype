#pragma once

namespace MaximumEngine
{
	struct Vector2
	{
		//CONSTRUCTORS
		Vector2();
		Vector2(float x, float y);
		//OPERATORS
		bool operator==(Vector2 v);
		bool operator!=(Vector2 v);
		Vector2 operator+(Vector2 v);
		Vector2 operator+(const Vector2 v) const;
		Vector2 operator-(Vector2 v);
		Vector2 operator-(const Vector2 v) const;
		//METHODS
		float getMagnitude() const;
		//VARIABLES
		float x, y;
	};
}


#define ME_Vector2 MaximumEngine::Vector2