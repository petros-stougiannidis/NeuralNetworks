#pragma once
#include <chrono>
#include <atomic>

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::nanoseconds ns;
typedef std::chrono::microseconds mys;
typedef std::chrono::milliseconds ms;
typedef std::chrono::seconds s;

class Timer
{
public:
	Timer() : m_start_point(Clock::now()) {}

	template<typename Unit = ns, typename Rep = double>
	Rep elapsed_time() const {
		std::atomic_thread_fence(std::memory_order_relaxed);
		auto counted_time = std::chrono::duration_cast<Unit>(Clock::now() - m_start_point).count();
		std::atomic_thread_fence(std::memory_order_relaxed);
		return static_cast<Rep>(counted_time);
	}

	void reset() {
		m_start_point = Clock::now();
	}
private:
	std::chrono::time_point<Clock> m_start_point;


};

