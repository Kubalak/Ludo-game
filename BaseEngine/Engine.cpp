#include "Engine.hpp"
#include <iostream>

const std::string Engine::_VERSION = "0.1.0";

Engine::Engine():
	currentPlayer(-1),
	state(Engine::EngineStates::CREATED) {
	/*
	*			|
	*	*4*		|	 *1*
	*			|
	*-----------|----------
	*			|
	*	*3*		|	 *2*
	*			|
	*/
	Tile a(true);
	for (int i = 0; i < 4; ++i) {
		tiles[i * 13] = a; // Pola startowe graczy
		tiles[8 + i * 13] = a; // Pola dodatkowe
	}
}
Engine::~Engine() {
	for (auto p : players)
		delete players[p.first];
}

bool Engine::addPlayer(Player* player, unsigned int quarter) {
	if (state != EngineStates::CREATED) return false;
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
	if(state == EngineStates::CREATED) {
		currentPlayer = 0;
		state = EngineStates::STARTED;
	}
}

bool Engine::step() {
	if (finished())
		return true;
	if (state == EngineStates::CREATED) {
		std::cerr << "Nale¿y rozpocz¹æ grê przed wykonaniem kroku!\n";
		return false;
	}

	if (state == EngineStates::MOVE_MADE) {
		if(dice.getLast() != 6 || getCurrentPlayerContainer().allIn()) // Je¿eli gracz nie wyrzuci³ 6 lub zakoñczy³ grê.
			do {
				currentPlayer += 1;
				currentPlayer %= players.size();
			} while (getCurrentPlayerContainer().allIn());
		
		state = EngineStates::STEP_MADE;
		
		return true;
	}
	return false;
}

unsigned int Engine::rollDice() {
	if (state == EngineStates::DICE_ROLLED || state == EngineStates::MOVE_MADE)
		return dice.getLast();
	state = EngineStates::DICE_ROLLED;
	return  dice.roll();
}

//FIXME: B³¹d z iteratorem.
bool Engine::beatCountersToHolder(Tile& t) {
	std::vector<Counter*>::iterator it = t.lastBeat.begin();
	std::map<unsigned int, PlayerContainer*> mp;
	for (auto p : players)
		mp[p.second->getPlayer().getId()] = p.second;
	for (; it != t.lastBeat.end(); it++) {
		if (!mp[(*it)->getOwner()]->addToHolder(*it))
			return false;
	}
	t.lastBeat.clear();
	return t.lastBeat.size() == 0;
}

//~FIXME~: Naprawiæ b³¹d podczas przechodzeia na pocz¹tek planszy.
bool Engine::moveCounterOnBoard(unsigned int fieldNo) {
	Player& p = getCurrentPlayer();

	if (!tiles[fieldNo].hasCounter(p))
		return false;

	unsigned int offset = dice.getLast();
	bool result = tiles[fieldNo].movePlayerCounter(tiles[(fieldNo + offset) % 52], p);
	if (result)
		result |= beatCountersToHolder(tiles[(fieldNo + offset) % 52]);
	state = EngineStates::MOVE_MADE;
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
	state = EngineStates::MOVE_MADE;
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
			state = EngineStates::MOVE_MADE;
			return c.addToLast(ct, offset);
		}
	
	return false;
}



// 101-106 Q1
// 201-206 Q2
// 301-306 Q3
// 401-406 Q4

//~TODO~: Poprawiæ metodê move() tak, by korzysta³a z nowych w³aœciwoœci Tile.

//bool Engine::move(unsigned int fieldNo) {
//
//	if (state != EngineStates::DICE_ROLLED) return false;
//	if (!getCurrentPlayerContainer().canMove() && dice.getLast() != 6) {
//		std::cout << "Cannot move!\n";
//		state = EngineStates::MOVE_MADE;
//		return false;
//	}
//	else if (dice.getLast() == 6) {
//		PlayerContainer& c = getCurrentPlayerContainer();
//		tiles[c.getStartPos()].addToTile(c.holderPop());
//		std::cout << "6 hit!\n";
//		state = EngineStates::MOVE_MADE;
//		return true;
//	}
//	if (fieldNo < 54)
//	{
//		std::cout << "Normal field!\n";
//		unsigned int distance = getDistance(getCurrentPlayerContainer(), dice.getLast());
//		if (distance > 52) 
//			return moveCounterToLast(fieldNo, distance - 52);
//		return moveCounterOnBoard(fieldNo);
//	}
//	else if(fieldNo > 100) {
//		std::cout << "Player special!\n";
//		return moveCounterOnLast(fieldNo);
//	}
//	return false;
//}

//TODO: Sprawdziæ czy dzia³a poprawnie.
//FIXME: Naprawiæ b³¹d podczas przechodzenia na pocz¹tek planszy.
bool Engine::move(unsigned int fieldNo) {
	if (state != EngineStates::DICE_ROLLED) return false;
	if (!getCurrentPlayerContainer().canMove() && dice.getLast() != 6) {
		state = EngineStates::MOVE_MADE;
		return false;
	}
	if (dice.getLast() == 6 && fieldNo == getCurrentPlayerContainer().getStartPos()) {
		PlayerContainer& pc = getCurrentPlayerContainer();
		Counter* c;
		if ((c = pc.holderPop()) != nullptr) // Jeœli w domku by³ pionek.
		{
			bool result = tiles[pc.getStartPos()].addToTile(c);// Z za³o¿enia wiele pionków mo¿e na nim staæ.
			if (result)
				state = EngineStates::MOVE_MADE;
			return  result; 
		}
	}
	if (fieldNo < 52) {
		unsigned int distance = getDistance(getCurrentPlayerContainer(), dice.getLast());
		if (distance < 50)
			return moveCounterOnBoard(fieldNo);
		return moveCounterToLast(fieldNo, distance - 50);
	}
	else if (fieldNo > 100)
		return moveCounterOnLast(fieldNo);
	return false;
}

bool Engine::finished() { 
	for (auto p : players) {
		if (!p.second->allIn())
			return false;
	}
	return true;
}


unsigned int Engine::getDistance(PlayerContainer& c, unsigned int dest) {
	if (c.getStartPos() < dest)
		return dest - c.getStartPos();
	return 54 - c.getStartPos() + dest;
}



#ifdef _DEBUG
std::string Engine::stateToStr(Engine::EngineStates state) {
	switch (state) {
		case EngineStates::CREATED: return "CREATED";
		case EngineStates::STARTED: return "STARTED";
		case EngineStates::DICE_ROLLED: return "DICE_ROLLED";
		case EngineStates::STEP_MADE: return "STEP_MADE";
		case EngineStates::MOVE_MADE: return "MOVE_MADE";
		default: return "<UNKNOWN>";
	}
}
std::ostream& operator<< (std::ostream& os, const Engine& e) {
	std::cout << "<Engine object " << std::hex << std::uppercase << &e << std::resetiosflags(std::ios_base::basefield) << " v"<< Engine::_VERSION << ">:\n";
	os << "Current state: " << std::boolalpha << Engine::stateToStr(e.state) << std::resetiosflags(std::ios_base::basefield) << '\n';
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