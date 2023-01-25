#include "Engine.hpp"
#include <string>
#include <algorithm>
constexpr auto ESRC = "BaseEngine/Engine.cpp";

const std::string Engine::_VERSION = "0.9.0";

const std::map<EngineStates, std::string> Engine::stateStr{
	{ EngineStates::CREATED, "CREATED"},
	{ EngineStates::STARTED, "STARTED"},
	{ EngineStates::DICE_ROLLED,"DICE_ROLLED"},
	{ EngineStates::STEP_MADE,"STEP_MADE"},
	{ EngineStates::MOVE_MADE, "MOVE_MADE"}
};

const std::map<EngineStates, int> Engine::stateInt{
	{ EngineStates::CREATED, 1},
	{ EngineStates::STARTED, 2},
	{ EngineStates::DICE_ROLLED, 3},
	{ EngineStates::STEP_MADE,4},
	{ EngineStates::MOVE_MADE, 5}
};

const std::map<int, EngineStates> Engine::intState{
	{ 1, EngineStates::CREATED},
	{ 2, EngineStates::STARTED},
	{ 3, EngineStates::DICE_ROLLED},
	{ 4, EngineStates::STEP_MADE},
	{ 5, EngineStates::MOVE_MADE}
};

Engine::Engine() :
	currentPlayer(-1),
	state(EngineStates::CREATED) {
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
		tiles[i * 13] = a; // Pola startowe graczy (static_cast przez VS)
		tiles[8 + i * 13] = a; // Pola dodatkowe (static_cast przez VS)
	}
}

Engine::Engine(nlohmann::json& obj) :
	currentPlayer(obj["currentPlayer"].get<int>()),
	state(intState.at(obj["state"].get<int>())) {

	std::map<unsigned int, Player*> pmap; // Mapuje id gracza na obiekt gracza.
	std::vector<Counter*> fcounters; // Zbiera wszystkie pionki razem.
	if (!dice.setLast(obj["diceVal"].get<unsigned int>()))
		throw std::string("Invalid dice value encountered! " + std::string(ESRC) + ":" + std::to_string(__LINE__));
	// Dodawanie graczy.
	for (auto& c : obj["players"]) {
		unsigned int q = c["quarter"].get<unsigned int>();
		if (q > 3)
			throw std::string("Invalid quarter value! " + std::string(ESRC) + ":" + std::to_string(__LINE__));
		if (players.find(q) != players.end())
			throw std::string("Selected quarter is already taken! " + std::string(ESRC) + ":" + std::to_string(__LINE__));
		auto* p = new PlayerContainer(c["playerContainer"]);
		for (auto& pc : players)
			if (pc.second->getPlayer().getId() == p->getPlayer().getId())
				throw std::string("Player alrady exists! " + std::string(ESRC) + ":" + std::to_string(__LINE__));
		pmap[p->getPlayer().getId()] = &p->getPlayer();
		players[q] = p;
		if (q * 13 != players[q]->getStartPos())
			throw std::string("Start position does not match quarter value! " + std::string(ESRC) + ":" + std::to_string(__LINE__));
		for (auto* fc : p->getHolder())
			fcounters.push_back(fc);
		for (auto& f : p->getLast())
			for (auto* fc : f)
				fcounters.push_back(fc);
	}
	auto index = 0u;
	// Dodawanie pionków do pól.
	for (auto& t : obj["tiles"]) {
		tiles[index] = Tile(t["manyCanStand"].get<bool>());
		for (auto& lb : t["lastBeat"]) {

			unsigned int id = lb["id"].get<unsigned int>();
			if (id > 3)
				throw std::string("Invalid counterId encountered! " + std::string(ESRC) + ":" + std::to_string(__LINE__));
			unsigned int owner = lb["ownedBy"].get<unsigned int>();
			if (!std::count_if(pmap.begin(), pmap.end(), [&owner](const auto& p) {return owner == p.second->getId(); }))
				throw std::string("The given owner is invalid! " + std::string(ESRC) + ":" + std::to_string(__LINE__));
			Counter* cp = pmap[owner]->getCounters()[id];
			if (std::count_if(fcounters.begin(), fcounters.end(), [&cp](Counter* cnt) {return cnt == cp; }))
				throw std::string("Counter already on board! " + std::string(ESRC) + ":" + std::to_string(__LINE__));
			fcounters.push_back(cp);
			tiles[index].lastBeat.push_back(cp);
		}
		std::vector<Counter*>::iterator it = tiles[index].lastBeat.begin();
		std::map<unsigned int, PlayerContainer*> mp;
		for (auto& p : players)
			mp[p.second->getPlayer().getId()] = p.second;
		for (; it != tiles[index].lastBeat.end(); it++) {
			if (!mp[(*it)->getOwner()]->addToHolder(*it))
				throw std::string("Error while moving to holder! " + std::string(ESRC) + ":" + std::to_string(__LINE__));
		}
		tiles[index].lastBeat.clear();
		// Dodawanie pionków na planszê.
		for (auto& lb : t["counters"]) {
			unsigned int id = lb["id"].get<unsigned int>();
			if (id > 3)
				throw std::string("Invalid counterId encountered! " + std::string(ESRC) + ":" + std::to_string(__LINE__));
			unsigned int owner = lb["ownedBy"].get<unsigned int>();
			if (!std::count_if(pmap.begin(), pmap.end(), [&owner](const auto& p) {return owner == p.second->getId(); }))
				throw std::string("The given owner is invalid! " + std::string(ESRC) + ":" + std::to_string(__LINE__));
			Counter* cp = pmap[owner]->getCounters()[id];
			if (std::count_if(fcounters.begin(), fcounters.end(), [&cp](Counter* cnt) {return cnt == cp; }))
				throw std::string("Counter already on board! " + std::string(ESRC) + ":" + std::to_string(__LINE__));
			fcounters.push_back(cp);
			tiles[index].getCounters().push_back(cp);
		}
		index++;
	}
	// Testowanie liczby pionków na planszy, gracza oraz stanu silnika do obecnego gracza.
	if (fcounters.size() != 4 * players.size())
		throw std::string("Counters missing! " + std::string(ESRC) + ":" + std::to_string(__LINE__));
	if (currentPlayer > static_cast<int>(players.size()))
		throw std::string("Invalid current player value! " + std::string(ESRC) + ":" + std::to_string(__LINE__));
	if ((currentPlayer < 0 && state != EngineStates::CREATED) || (currentPlayer >= 0 && state == EngineStates::CREATED))
		throw std::string("Current player doesn't match game state! " + std::string(ESRC) + ":" + std::to_string(__LINE__));
	unsigned int p;
	// Budowanie tablicy wyników z JSON.
	for (auto& tp : obj["topPlayers"]) {
		p = tp.get<unsigned int>();
		if (std::count_if(pmap.begin(), pmap.end(), [&p](std::pair<unsigned int, Player*> player) {return player.second->getId() == p; }) == 0)
			throw std::string("Top player with given id doesn't exist! " + std::string(ESRC) + ":" + std::to_string(__LINE__));
		std::pair<unsigned int, PlayerContainer*> pc = *(std::find_if(players.begin(), players.end(), [&p](std::pair<unsigned int, PlayerContainer*> c) {return p == c.second->getPlayer().getId(); }));
		if (!pc.second->allIn())
			throw std::string("This player hasn't finished yet! " + std::string(ESRC) + ":" + std::to_string(__LINE__));
		top.push_back(pmap[p]);

	}

}


Engine::~Engine() {
	for (auto& p : players)
		delete players[p.first];
}

bool Engine::addPlayer(Player* player, unsigned int quarter) {
	if (state != EngineStates::CREATED) return false;
	for (auto& p : players)
		if (p.second->getPlayer().getId() == player->getId() || p.first == quarter - 1) // Sprawdzamy czy gracz lub æwiartka ju¿ nie wystêpuje.
			return false;

	if (quarter == 0 || quarter > 4)
		return false;
	players[quarter - 1] = new PlayerContainer(player, (quarter - 1) * 13);

	return true;
}

bool Engine::start()
{
	if (players.empty() || players.size() < 2) return false;
	if (state == EngineStates::CREATED) {
		currentPlayer = 0;
		state = EngineStates::STARTED;
		return true;
	}
	return false;
}

bool Engine::step() {
	if (finished())
		return true;
	if (state == EngineStates::CREATED) {
#ifdef _DEBUG
		std::cerr << "Nale¿y rozpocz¹æ grê przed wykonaniem kroku!\n";
#endif
		return false;
	}

	if (state == EngineStates::MOVE_MADE) {
		if (dice.getLast() != 6 || getCurrentPlayerContainer().allIn()) // Je¿eli gracz nie wyrzuci³ 6 lub zakoñczy³ grê.
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
	//unsigned int val = dice.roll();
	//dice.setLast( 1 + (val % 2) * 5);
	return dice.roll();
}


bool Engine::beatCountersToHolder(Tile& t) {
	std::vector<Counter*>::iterator it = t.lastBeat.begin();
	std::map<unsigned int, PlayerContainer*> mp;
	for (auto& p : players)
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
	Player* p = getCurrentPlayer();
	if (p == nullptr)return false;
	if (!tiles[fieldNo].hasCounter(*p))
		return false;
	unsigned int offset = dice.getLast();
	bool result = tiles[fieldNo].movePlayerCounter(tiles[(fieldNo + offset) % 52], *p);
	if (result)
		result |= beatCountersToHolder(tiles[(fieldNo + offset) % 52]);
	state = EngineStates::MOVE_MADE;
	return result;
}

//TODO: Sprawdziæ poruszanie siê po ostatnich.
bool Engine::moveCounterOnLast(unsigned int fieldNo) {
	if (fieldNo <= 100 || fieldNo > 406) return false;
	unsigned int Q = fieldNo / 100 - 1;
	if (players.find(Q) == players.end())
		return false;
	PlayerContainer& c = *players[Q];
	Player* p = getCurrentPlayer();
	if (p == nullptr)return false;
	if (c.getPlayer().getId() != p->getId())
		return false;
	unsigned int field = (fieldNo % 100) - 1;
	bool result = c.moveOnLast(field, dice.getLast());
	if (result) {
		if (c.allIn())
			top.push_back(c.getPlayerPtr());
		state = EngineStates::MOVE_MADE;
	}
	return result;
}

bool Engine::moveCounterToLast(unsigned int from, unsigned int offset) {
	std::vector<Counter*>& v = tiles[from].getCounters();
	PlayerContainer& c = getCurrentPlayerContainer();
	std::vector<Counter*>::iterator it = v.begin();
	for (; it != v.end(); it++)
		if ((*it)->getOwner() == c.getPlayer().getId())
		{
			Counter* ct = *it;
			v.erase(it);
			bool result = c.addToLast(ct, offset);
			if (result)
				state = EngineStates::MOVE_MADE;
			else
				tiles[from].getCounters().push_back(ct);
			return result;
		}

	return false;
}


std::map<unsigned int, unsigned int> Engine::getQuarters() {
	std::map<unsigned int, unsigned int> m;
	for (auto& pc : players)
		m[pc.first + 1] = pc.second->getPlayer().getId();

	return m;
}

// 101-106 Q1
// 201-206 Q2
// 301-306 Q3
// 401-406 Q4
//TODO: Sprawdziæ czy dzia³a poprawnie.

bool Engine::move(int fieldNo) {
	if (state != EngineStates::DICE_ROLLED) return false;
	if (!getCurrentPlayerContainer().canMove() && dice.getLast() != 6) {
		state = EngineStates::MOVE_MADE;
		return step();
	}
	if (dice.getLast() == 6 && fieldNo < 0) {
		PlayerContainer& pc = getCurrentPlayerContainer();
		Counter* c;
		if ((c = pc.holderPop()) != nullptr) // Jeœli w domku by³ pionek.
		{
#ifdef _DEBUG
			std::cout << "Popping from holder " << *c << '\n';
#endif
			if (tiles[pc.getStartPos()].addToTile(c)) { // Z za³o¿enia wiele pionków mo¿e staæ na polu startowym dodanie jest zawsze bezpieczne.
				state = EngineStates::MOVE_MADE;
				return step();
			}
			else pc.addToHolder(c);
			return false;
		}
	}
	else if (fieldNo < 52 && fieldNo >= 0) {
		unsigned int distance_start = getDistance(getCurrentPlayerContainer(), fieldNo);
		unsigned int distance = getDistance(getCurrentPlayerContainer(), fieldNo + dice.getLast());
#ifdef _DEBUG
		std::cout << "Calculated distance is " << distance << " start is  " << distance_start << '\n';
#endif
		if (distance < 51 && distance_start < distance) {
#ifdef _DEBUG
			std::cout << "Moving on board to " << fieldNo + dice.getLast() << '\n';
#endif
			if (moveCounterOnBoard(fieldNo))
				return step();
			return false;
		}
		else {
			unsigned int dest = 0;
			if (distance > distance_start)
				dest = distance - 51;
			else dest = 51 - distance_start;
#ifdef _DEBUG
			std::cout << "Moving to last on " << dest << '\n';
#endif
			if (moveCounterToLast(fieldNo, dest))
				return step();
			return false;
		}
	}
	else if (fieldNo > 100) {
#ifdef _DEBUG
		std::cout << "Moving on last " << fieldNo << '\n';
#endif
		if (moveCounterOnLast(fieldNo))
			return step();
		return false;
	}
	return false;
}

bool Engine::finished() {
	if (players.empty())return false;
	for (auto& p : players) {
		if (!p.second->allIn())
			return false;
	}
	return true;
}


unsigned int Engine::getDistance(PlayerContainer& c, unsigned int dest) {
	if (c.getStartPos() <= dest)
		return dest - c.getStartPos();
	return 52 + dest - c.getStartPos();
}


std::ostream& operator<< (std::ostream& os, const Engine& e) {
	os << "{\"version\":\"" << Engine::_VERSION << "\",";
	os << "\"state\":" << Engine::stateInt.at(e.state) << ',';
	os << "\"diceVal\":" << e.dice << ',';
	os << "\"currentPlayer\":" << e.currentPlayer << ',';
	os << "\"players\":[";
	auto it = e.players.begin();
	while (it != e.players.end()) {
		os << "{\"quarter\":" << (*it).first << ",\"playerContainer\":" << *((*it).second) << '}';
		it++;
		if (it != e.players.end())
			os << ',';
	}
	os << "],\"topPlayers\":[";
	auto pit = e.top.begin();
	while (pit != e.top.end()) {
		os << (*pit)->getId();
		pit++;
		if (pit != e.top.end())
			os << ',';
	}
	os << "],\"tiles\":[";
	auto tit = e.tiles.begin();
	while (tit != e.tiles.end()) {
		os << *tit;
		tit++;
		if (tit != e.tiles.end())
			os << ',';
	}
	os << "]}";

	return os;
}

std::string Engine::str() {
	std::stringstream ss;
	ss << "<Engine object 0x" << std::hex << std::uppercase << this << std::resetiosflags(std::ios_base::basefield) << " (v" << Engine::_VERSION << ")>:\n";
	ss << "Current state: " << std::boolalpha << stateStr.at(state) << std::resetiosflags(std::ios_base::basefield) << '\n';
	ss << "PlayerContainers:\n\n";
	for (auto& p : players)
		ss << p.second->str() << "\n";
	ss << "\n";
	ss << "Top players:\n";
	for (auto* p : top)
		ss << p->getNick() << " (" << p->getId() << ")\n";
	ss << "\nTiles:\n";
	unsigned int index = 0;
	for (auto& i : tiles)
		ss << '[' << index++ << "]: " << i.str() << '\n';
	return ss.str();
}

std::string Engine::json() {
	std::stringstream ss;
	ss << "{\"version\":\"" << Engine::_VERSION << "\",";
	ss << "\"state\":" << Engine::stateInt.at(state) << ',';
	ss << "\"diceVal\":" << dice.getLast() << ',';
	ss << "\"currentPlayer\":" << currentPlayer << ',';
	ss << "\"players\":[";
	auto it = players.begin();
	while (it != players.end()) {
		ss << "{\"quarter\":" << (*it).first << ",\"playerContainer\":" << (*it).second->json() << '}';
		it++;
		if (it != players.end())
			ss << ',';
	}
	ss << "],\"topPlayers\":[";
	auto pit = top.begin();
	while (pit != top.end()) {
		ss << (*pit)->getId();
		pit++;
		if (pit != top.end())
			ss << ',';
	}
	ss << "],\"tiles\":[";
	auto tit = tiles.begin();
	while (tit != tiles.end()) {
		ss << (*tit).json();
		tit++;
		if (tit != tiles.end())
			ss << ',';
	}
	ss << "]}";

	return ss.str();
}