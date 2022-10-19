#pragma once

#include "Player.hpp"
#include "Dice.hpp"
#include "Tile.hpp"

class Engine
{
	std::vector<Player> players;
	// TODO: Sprawdziæ ile pól ma plansza do Chiñczyka.
	std::array<Tile,32> counters; 
public:
	Engine();
};

