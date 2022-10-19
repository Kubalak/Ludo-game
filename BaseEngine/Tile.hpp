#pragma once
#include "Counter.hpp"
#include <vector>

class Tile
{
	const bool manyCanStand;
	std::vector<Counter> counters;
public:
	Tile(bool manyCanStand = false);
};

