#pragma once
#include <thread>
#include <mutex>
#include <functional>
#include <vector>
#include <queue>

namespace MaximumEngine
{
	class EngineThreadPool
	{
	public:
		using Function = std::function<void()>;
		static bool enqueue(Function func);		
	private:
		//METHODS
		static void init();
		static void stop();
		static void wait();
		static bool isWaiting();
		static void runThread(const int threadNum);
		//MEMBERS
		static std::vector<std::thread> mThreads;
		static std::vector<bool> mIsThreadActive;
		static std::condition_variable mEventVar;
		static std::mutex mEventMutex;
		static std::condition_variable mMainVar;
		static std::mutex mMainMutex;
		static std::queue<Function> mFunctions;
		static bool mStopping;
		static bool mInitalized;
		static bool mMainWaiting;
		//FRIENDS
		friend class Engine;
	};
}


