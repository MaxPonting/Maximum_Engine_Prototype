#include "Timer.h"

MaximumEngine::Timer::Timer(std::string name) : name(name)
{
	m_StartTimePoint = std::chrono::high_resolution_clock::now();
}
MaximumEngine::Timer::~Timer()
{
	auto endTimePoint = std::chrono::high_resolution_clock::now();

	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

	auto duration = end - start;

	double ms = duration * 0.001;

	std::cout << name << std::endl;
	std::cout << duration << "us (" << ms << "ms)\n\n";
}