#include "Engine.hpp"

Engine::Engine():
	currentPlayer(-1),
	gameStarted(false) { 

}
Engine::~Engine() {
	for (auto p : players)
		delete p.p;
}

bool Engine::addPlayer(Player* player) {
	if (gameStarted) return false;
	for (auto p : players)
		if (p.p->getId() == player->getId())
			return false;
	unsigned int new_pos = 0;
	if (!players.empty())
	    new_pos = players.back().start + 13;
	players.push_back({ new_pos,player });
	
	return true;	
}

void Engine::start()
{
	gameStarted = true;
	currentPlayer = 0;
}
