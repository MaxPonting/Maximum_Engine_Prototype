#include "Vector2.h"
#include <iostream>

//CONSTRUCTORS
MaximumEngine::Vector2::Vector2() { x = 0; y = 0; }
MaximumEngine::Vector2::Vector2(float x, float y) :x(x), y(y) {}

//OPERATORS
bool MaximumEngine::Vector2::operator==(Vector2 v)
{
	if (x == v.x && y == v.y) { return true; }
	return false;
}
bool MaximumEngine::Vector2::operator!=(Vector2 v)
{
	return !operator==(v);
}
MaximumEngine::Vector2 MaximumEngine::Vector2::operator+(Vector2 v)
{
	return Vector2(x + v.x, y + v.y);
}
MaximumEngine::Vector2 MaximumEngine::Vector2::operator+(const Vector2 v) const
{
	return Vector2(x + v.x, y + v.y);
}
MaximumEngine::Vector2 MaximumEngine::Vector2::operator-(Vector2 v)
{
	return Vector2(x - v.x, y - v.y);
}
MaximumEngine::Vector2 MaximumEngine::Vector2::operator-(const Vector2 v) const
{
	return Vector2(x - v.x, y - v.y);
}

//METHODS
float MaximumEngine::Vector2::getMagnitude()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

