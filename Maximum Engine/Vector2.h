#pragma once

namespace MaximumEngine
{
	struct Vector2
	{
		//CONSTRUCTORS
		Vector2();
		Vector2(float x, float y);
		//OPERATORS
		bool operator==(Vector2 v) const;
		bool operator!=(Vector2 v) const;
		Vector2 operator+(Vector2 v) const;		
		Vector2 operator-(Vector2 v) const;
		float operator*(Vector2 v) const;
		//METHODS
		float getMagnitude() const;
		Vector2 getNormalization() const;
		Vector2 getRotate(float z);
		//VARIABLES
		float x, y;
	};
}

#define ME_Vector2 MaximumEngine::Vector2