#pragma once

#include "Player.hpp"
#include "Dice.hpp"
#include "Tile.hpp"

struct PlayerContainer {
	unsigned int start;
	Player* p;
};

class Engine
{
	int currentPlayer;
	bool gameStarted;
	//Zbiór, który przechowuje graczy w postaci <pierwsza_pozycja,gracz>
	std::vector<PlayerContainer> players;
	// Podstawowa plansza do Chiñczyka.
	std::array<Tile,52> counters;
	// Kostka do gry.
	Dice dice;
public:
	Engine();
	~Engine();
	bool addPlayer(Player* player);
	Player& getCurrentPlayer(){ return *players[currentPlayer].p; }
	void start();
	void step() {}
	bool move(const Player&, unsigned int counterId) { return false; }
};

