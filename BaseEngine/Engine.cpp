#include "Engine.hpp"
#include <iostream>
Engine::Engine():
	currentPlayer(-1),
	gameStarted(false),
	moveMade(false),
	diceRolled(false) { 

}
Engine::~Engine() {
	for (auto p : players)
		delete players[p.first];
}

bool Engine::addPlayer(Player* player, unsigned int quarter) {
	if (gameStarted) return false;
	for (auto p : players)
		if (p.second->getPlayer().getId() == player->getId())
			return false;
	
	if (quarter == 0 || quarter > 4)
		return false;
	players[quarter - 1] = new PlayerContainer(player);
	
	return true;	
}

void Engine::start()
{
	if (players.empty() || players.size() < 1) throw std::exception("Nie mo¿na uruchomiæ gry, zbyt ma³a liczba graczy!");
	gameStarted = true;
	currentPlayer = 0;
}

bool Engine::step() {
	if (!gameStarted)
		start();
	
	if (!moveMade)
		return false;

	currentPlayer += 1;
	currentPlayer %= players.size();

	return true;
}

unsigned int Engine::rollDice() {
	if (diceRolled)
		return dice.getLast();
	diceRolled = true;
	return  dice.roll();
}

bool Engine::move(Player& p, unsigned int fieldNo) { 
	if (fieldNo < 51)
	{

	}
	else {

	}
	return false;
}

bool Engine::finished() { 
	return false; 
}
