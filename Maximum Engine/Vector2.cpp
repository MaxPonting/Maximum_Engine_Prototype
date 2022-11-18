#include "Vector2.h"
#include <iostream>

//CONSTRUCTORS
MaximumEngine::Vector2::Vector2() { x = 0; y = 0; }
MaximumEngine::Vector2::Vector2(float x, float y) :x(x), y(y) {}

//OPERATORS
bool MaximumEngine::Vector2::operator==(Vector2 v) const
{
	if (x == v.x && y == v.y) { return true; }
	return false;
}
bool MaximumEngine::Vector2::operator!=(Vector2 v) const
{
	return !operator==(v);
}
MaximumEngine::Vector2 MaximumEngine::Vector2::operator+(Vector2 v) const
{
	return Vector2(x + v.x, y + v.y);
}
MaximumEngine::Vector2 MaximumEngine::Vector2::operator-(Vector2 v) const
{
	return Vector2(x - v.x, y - v.y);
}
float MaximumEngine::Vector2::operator*(Vector2 v) const
{
	return x* v.x + y * v.y;
}

//METHODS
float MaximumEngine::Vector2::getMagnitude() const
{
	return sqrt(pow(x, 2) + pow(y, 2));
}
ME_Vector2 MaximumEngine::Vector2::getNormalization() const
{
	float magnitude = getMagnitude();
	if (magnitude == 0) return Vector2(0, 0);
	return Vector2(x * 1 / magnitude, y * 1 / magnitude);
}
ME_Vector2 MaximumEngine::Vector2::getRotate(float z)
{	
	return Vector2(x * cos(z) - sin(z) * y, x * sin(z) + cos(z) * y);
}

