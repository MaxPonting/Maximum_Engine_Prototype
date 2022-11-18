#pragma once
namespace MaximumEngine
{
	class Angle
	{
	public:
		//CONSTRUCTOR
		Angle();
		Angle(float angle);
		//OPERATORS
		void operator=(float angle);
		Angle operator+(float degrees);
		bool operator==(Angle angle);
		//GETTERS
		float getDeg() const;
		float getRad() const;
	private:
		//MEMBER
		float m_degrees;
	};
}

