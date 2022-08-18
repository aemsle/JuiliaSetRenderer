//Credit
//https://www.youtube.com/watch?v=Vyt-dM8gTRQ&t

#pragma once

#include <chrono>

namespace StopWatch
{
	class Timer
	{
	public:
		Timer();
		~Timer();

		static Timer* Instance();
		static void CleanUp();

		void Reset();
		float getDeltaTime();
		void Tick();

	private:
		static Timer* instance_;
		std::chrono::system_clock::time_point start_;
		std::chrono::duration<float> delta_time_;
	};
}
