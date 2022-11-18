#include "Angle.h"
#include <cmath>

MaximumEngine::Angle::Angle() :m_degrees(0) {}
MaximumEngine::Angle::Angle(float angle) :m_degrees(std::fmodf(angle, 360)) {}

void MaximumEngine::Angle::operator=(float angle) 
{
	//Set angle to between 0 and 360
	m_degrees = std::fmodf(angle, 360);
}

MaximumEngine::Angle MaximumEngine::Angle::operator+(float degrees)
{
	//Set angle to between 0 and 360
	return std::fmodf(m_degrees + degrees, 360);
}

bool MaximumEngine::Angle::operator==(Angle angle)
{
	return m_degrees == angle.getDeg();
}

float MaximumEngine::Angle::getDeg() const
{
	return m_degrees;
}

float MaximumEngine::Angle::getRad() const
{
	return m_degrees * (3.14159265359 / 180);
}