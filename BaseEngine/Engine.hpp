#pragma once

#include "Player.hpp"
#include "Dice.hpp"
#include "Tile.hpp"

class Engine
{
	std::vector<Player> players;
	// TODO: Sprawdzi� ile p�l ma plansza do Chi�czyka.
	std::array<Tile,32> counters; 
public:
	Engine();
};

