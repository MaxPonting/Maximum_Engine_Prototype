#pragma once
#include <iostream>

namespace MaximumEngine
{
	class Log
	{
	public:
		//METHODS
		static void debugLog(std::string log);
		static void errorLog(std::string log);
	};
}


#define ME_Debug_Log(l) MaximumEngine::Log::debugLog(l)
#define ME_Error_Log(l) MaximumEngine::Log::errorLog(l)

