#include "EngineThreadPool.h"
#include <iostream>
#include <atomic>

//STATIC MEMBERS
std::vector<std::thread> MaximumEngine::EngineThreadPool::mThreads;
std::vector<bool> MaximumEngine::EngineThreadPool::mIsThreadActive;
std::condition_variable MaximumEngine::EngineThreadPool::mEventVar;
std::mutex MaximumEngine::EngineThreadPool::mEventMutex;
std::condition_variable MaximumEngine::EngineThreadPool::mMainVar;
std::mutex MaximumEngine::EngineThreadPool::mMainMutex;
std::queue<MaximumEngine::EngineThreadPool::Function> MaximumEngine::EngineThreadPool::mFunctions;
bool MaximumEngine::EngineThreadPool::mStopping = false;
bool MaximumEngine::EngineThreadPool::mInitalized = false;
bool MaximumEngine::EngineThreadPool::mMainWaiting = false;

//INIT
void MaximumEngine::EngineThreadPool::init()
{
	for (int i = 0; i < std::thread::hardware_concurrency(); i++)
	{
		mIsThreadActive.emplace_back(std::atomic<bool>(false));
		mThreads.emplace_back(std::thread(runThread, mThreads.size()));
	}
	mInitalized = true;
}
//ENQUEUE
bool MaximumEngine::EngineThreadPool::enqueue(Function func)
{
	if (!mInitalized) return false;
	{
		std::unique_lock<std::mutex> lock{ mEventMutex };
		mFunctions.emplace(std::move(func));
	}

	mEventVar.notify_one();

	return true;
}
//STOP
void MaximumEngine::EngineThreadPool::stop()
{
	{
		std::unique_lock<std::mutex> lock{ mMainMutex };
		mMainVar.wait(lock, [] { return !isWaiting(); });
	}	

	{
		std::unique_lock<std::mutex> lock{ mEventMutex };
		mStopping = true;
	}

	mEventVar.notify_all();

	for (int i = 0; i < mThreads.size(); i++)
	{
		if (mThreads[i].joinable()) mThreads[i].join();
	}

	mThreads.clear();
	mIsThreadActive.clear();
	mInitalized = false;
	mStopping = false;
}
//RESET
void MaximumEngine::EngineThreadPool::wait()
{
	if (!mInitalized) return;
	if (!isWaiting()) return;

	{
		std::unique_lock<std::mutex> lock{ mMainMutex };
		mMainWaiting = true;
		mMainVar.wait(lock, [] { return !isWaiting(); });
		mMainWaiting = false;
	}
}
//IS FINISHED
bool MaximumEngine::EngineThreadPool::isWaiting()
{
	if (!mFunctions.empty()) return true;
	for (int i = 0; i < mIsThreadActive.size(); i++)
	{
		if (mIsThreadActive[i]) return true;
	}
	return false;
}
//RUN THREAD
void MaximumEngine::EngineThreadPool::runThread(const int threadNum)
{
	while (true)
	{
		Function func;
		{
			//Lock and wait until new function
			std::unique_lock<std::mutex> lock(mEventMutex);
			mEventVar.wait(lock, [=] { return mStopping || !mFunctions.empty(); });
			//Set thread to active
			mIsThreadActive[threadNum] = true;
			//Break if pool is stopping
			if (mStopping) { mIsThreadActive[threadNum] = false; break; }
			//Get next function from queue
			func = std::move(mFunctions.front());
			mFunctions.pop();			
		}
		
		//Run function
		func();
		
		{
			//Lock
			std::unique_lock<std::mutex> lock(mEventMutex);
			//Set thread to unactive
			mIsThreadActive[threadNum] = false;
			if (mMainWaiting && !isWaiting())
			{
				mMainVar.notify_one();
			}
		}
	}
}




