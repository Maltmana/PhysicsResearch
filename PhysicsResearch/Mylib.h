#pragma once
#include <chrono>
#include <cmath>

////////////////////////////////////////  Clock
////////////////////////////////////////
////////////////////////////////////////

template <typename T = std::chrono::steady_clock>
class Clock
{
	typename T::time_point last;

public:
	// Sets timepoint at construction.
	Clock()
		: last(T::now())
	{}

	// Returns time since last tick or construction.
	typename T::duration elapsed() const
	{
		return T::now() - last;
	}

	// Returns duration since last tick or construction and sets timepoint to now.
	typename T::duration tick()
	{
		auto now = T::now();
		auto elapsed = now - last;
		last = now;
		return elapsed;
	}

	// Freshly reconstructs object
	void reset()
	{
		*this = Clock();
	}
};

////////////////////////////////////////  RNG
////////////////////////////////////////
////////////////////////////////////////

#include <random>
#include <cassert>
#include <type_traits>

class RNG
{
	std::mt19937 mt;

public:

	RNG()
		: mt{ std::random_device{}() }
	{
		mt.discard(700000);
	}

	template <typename NumberType>
	NumberType rand(NumberType min, NumberType max)
	{
		assert(min < max);

		if constexpr (std::is_floating_point<NumberType>())
		{
			std::uniform_real_distribution<float> ud(min, max);
			return ud(mt);
		}
		else if constexpr (std::is_integral<NumberType>())
		{
			std::uniform_int_distribution<NumberType> ud(min, max);
			return ud(mt);
		}
		else
		{
			assert(false);
		}
	}

	bool flip(float oddsOfTrue)
	{
		std::bernoulli_distribution distribution(oddsOfTrue);
		return distribution(mt);
	}
};