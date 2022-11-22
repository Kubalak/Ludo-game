#include "Engine.hpp"
#include <iostream>

const std::string Engine::_VERSION = "0.1.0";

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
	players[quarter - 1] = new PlayerContainer(player, (quarter - 1) * 13);
	
	return true;	
}

void Engine::start()
{
	if (players.empty() || players.size() < 1) throw std::exception("Nie mo¿na uruchomiæ gry, zbyt ma³a liczba graczy!");
	gameStarted = true;
	currentPlayer = 0;
}

bool Engine::step() {
	if (finished())
		return true;
	if (!gameStarted)
		start();

	if (!moveMade)
		return false;

	do {
		std::cout << currentPlayer << ' ';
		currentPlayer += 1;
		currentPlayer %= players.size();
	} while (getCurrentPlayerContainer().allIn());

	std::cout <<currentPlayer<< " YES\n";
	resetMove();
	return true;
}

unsigned int Engine::rollDice() {
	if (diceRolled)
		return dice.getLast();
	diceRolled = true;
	return  dice.roll();
}

bool Engine::beatCountersToHolder(Tile& t) {
	std::vector<Counter*>::iterator it = t.lastBeat.begin();
	std::map<unsigned int, PlayerContainer*> mp;
	for (auto p : players)
		mp[p.second->getPlayer().getId()] = p.second;
	for (; it != t.lastBeat.end(); it++)
	{
		if (!mp[(*it)->getOwner()]->addToHolder(*it))
			return false;
		t.lastBeat.erase(it);
	}
	return t.lastBeat.size() == 0;
}

bool Engine::moveCounterOnBoard(unsigned int fieldNo) {
	Player& p = getCurrentPlayer();

	if (!tiles[fieldNo].hasCounter(p))
		return false;

	unsigned int offset = dice.getLast();
	bool result = tiles[fieldNo].movePlayerCounter(tiles[fieldNo + offset], p);
	if (result)
		result |= beatCountersToHolder(tiles[fieldNo + offset]);
	moveMade = true;
	return result;
}

bool Engine::moveCounterOnLast(unsigned int fieldNo) {
	if (fieldNo < 100 || fieldNo > 406) return false;
	unsigned int Q = fieldNo / 100 - 1;
	if (players.find(Q) == players.end())
		return false;
	PlayerContainer& c = *players[Q];
	if (c.getPlayer().getId() != getCurrentPlayer().getId())
		return false;
	unsigned int field = fieldNo % 100;
	moveMade = true;
	return c.moveOnLast(field, dice.getLast());
}

bool Engine::moveCounterToLast(unsigned int from, unsigned int offset) {
	std::vector<Counter*>& v = tiles[from].getCounters();
	PlayerContainer& c = getCurrentPlayerContainer();
	std::vector<Counter*>::iterator it = v.begin();
	for(;it!=v.end();it++)
		if ((*it)->getOwner() == c.getPlayer().getId())
		{
			Counter* ct = *it;
			v.erase(it);
			moveMade = true;
			return c.addToLast(ct, offset);
		}
	
	return false;
}



// 101-106 Q1
// 201-206 Q2
// 301-306 Q3
// 401-406 Q4

bool Engine::move(unsigned int fieldNo) {

	if (!diceRolled) return false;
	if (!getCurrentPlayerContainer().canMove() && dice.getLast() != 6) {
		std::cout << "Cannot move!\n";
		moveMade = true;
		return false;
	}
	else if (dice.getLast() == 6) {
		PlayerContainer& c = getCurrentPlayerContainer();
		tiles[c.getStartPos()].addToTile(c.holderPop());
		std::cout << "6 hit!\n";
		moveMade = true;
		return true;
	}
	if (fieldNo < 54)
	{
		std::cout << "Normal field!\n";
		unsigned int distance = getDistance(getCurrentPlayerContainer(), dice.getLast());
		if (distance > 52) 
			return moveCounterToLast(fieldNo, distance - 52);
		return moveCounterOnBoard(fieldNo);
	}
	else if(fieldNo > 100) {
		std::cout << "Player special!\n";
		return moveCounterOnLast(fieldNo);
	}
	return false;
}

bool Engine::finished() { 
	for (auto p : players) {
		if (!p.second->allIn())
			return false;
	}
	return true;
}

void Engine::resetMove() {
	moveMade = false;
	diceRolled = false;
}

unsigned int Engine::getDistance(PlayerContainer& c, unsigned int dest) {
	if (c.getStartPos() < dest)
		return dest - c.getStartPos();
	return 54 - c.getStartPos() + dest;
}

#ifdef _DEBUG
std::ostream& operator<< (std::ostream& os, const Engine& e) {
	std::cout << "<Engine object " << std::hex << std::uppercase << &e << std::resetiosflags(std::ios_base::basefield) << " v"<< Engine::_VERSION << ">:\n";
	os << "Is started: " << std::boolalpha << e.gameStarted << std::resetiosflags(std::ios_base::basefield) << '\n';
	os << "Dice rolled: " << std::boolalpha << e.diceRolled << std::resetiosflags(std::ios_base::basefield) << '\n';
	os << "Move made: " << std::boolalpha << e.moveMade << std::resetiosflags(std::ios_base::basefield) << '\n';
	os << "PlayerContainers:\n[";
	for (auto p : e.players)
		os << *p.second << ", \n";
	os << "]\n";
	os << "Tiles: [\n";
	for (int i = 0; i < 54; ++i)
		os << '[' << i << "]: " << e.tiles[i] << '\n';
	os << "]\n";
	return os;
}
#endif