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

	template<typename Unit = ns, typename Rep = double>
	void print_time() const {
		if (typeid(Unit) == typeid(s)) {
			std::cout << " ~ " << elapsed_time<Unit>() << " seconds" << std::endl << std::endl;
		} else if(typeid(Unit) == typeid(ms)) {
			std::cout << " ~ " << elapsed_time<Unit>() << " milliseconds" << std::endl << std::endl;
		}
		else if (typeid(Unit) == typeid(mys)) {
			std::cout << " ~ " << elapsed_time<Unit>() << " microseconds" << std::endl << std::endl;
		}
		else if (typeid(Unit) == typeid(ns)) {
			std::cout << " ~ " << elapsed_time<Unit>() << " nanoseconds" << std::endl << std::endl;
		}
		else {
			std::cout << "+++ ERROR: Could not represent unit +++" << std::endl;
		}
	}

	void reset() {
		m_start_point = Clock::now();
	}
private:
	std::chrono::time_point<Clock> m_start_point;


};

