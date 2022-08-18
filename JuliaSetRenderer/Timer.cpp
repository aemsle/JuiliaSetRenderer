#include "Timer.h"

namespace StopWatch {

	Timer* Timer::instance_ = nullptr;

	Timer::Timer()
	{
		Reset();
		delta_time_ = std::chrono::duration<float>(0.f);
	}

	Timer::~Timer()
	{
	}

	Timer* Timer::Instance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new Timer();
		}

		return instance_;
	}

	void Timer::CleanUp()
	{
		delete instance_;
		instance_ = NULL;
	}

	void Timer::Reset()
	{
		start_ = std::chrono::system_clock::now();
	}

	float Timer::getDeltaTime()
	{
		return delta_time_.count();
	}
	void Timer::Tick()
	{
		delta_time_ = std::chrono::system_clock::now() - start_;
	}
}