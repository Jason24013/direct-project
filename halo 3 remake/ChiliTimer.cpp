#include "ChiliTimer.h"

using namespace std::chrono;

ChiliTimer::ChiliTimer()
{
	last = steady_clock::now();
}

float ChiliTimer::Mark()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> framTime = last - old;
	return framTime.count();
}

float ChiliTimer::Peek() const
{
	return duration <float>(steady_clock::now() - last).count();
}