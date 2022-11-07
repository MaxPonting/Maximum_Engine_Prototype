#pragma once
#include <chrono>
#include <iostream>

namespace MaximumEngine
{
	class Timer
	{
	public:
		Timer(std::string name);
		~Timer();
	private:
		std::string name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
	};
}


