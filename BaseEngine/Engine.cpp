#include "Engine.hpp"

Engine::Engine():
	currentPlayer(-1),
	gameStarted(false) { 

}
Engine::~Engine() {
	for (auto p : players)
		delete players[p.first];
}

bool Engine::addPlayer(Player* player, unsigned int quarter) {
	if (gameStarted) return false;
	for (auto p : players)
		if (p.second->getId() == player->getId())
			return false;
	
	if (quarter == 0 || quarter > 4)
		return false;
	players[quarter - 1] = player;
	
	return true;	
}

void Engine::start()
{
	gameStarted = true;
	currentPlayer = (*players.begin()).first;
}
