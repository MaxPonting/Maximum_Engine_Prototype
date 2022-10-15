#include "Log.h"

void MaximumEngine::Log::debugLog(std::string log)
{
	std::cout << "[Maximum Engine][Debug] " << log << std::endl;
}

void MaximumEngine::Log::errorLog(std::string log)
{
	std::cout << "[Maximum Engine][Error] " << log << std::endl;
}