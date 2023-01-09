#include "PlayerContainer.hpp"
#include <algorithm>
constexpr auto PSRC = "BaseEngine/PlayerContainer.cpp";

PlayerContainer::PlayerContainer(Player* p, unsigned int startPos) :
	player(p),
	startPos(startPos) {
	for (auto* c : p->getCounters())
		holder.push_back(c);
}

PlayerContainer::PlayerContainer(nlohmann::json obj) :
	startPos(obj["startPos"].get<unsigned int>()),
	player(new Player(obj["playerObj"])) {
	auto it = obj["holder"].begin();
	// Kopiuje pionki do holder.
	for (; it != obj["holder"].end(); ++it) {
		if ((*it)["ownedBy"].get<unsigned int>() != player->getId())
			throw std::string("Invalid owner encountered! " + std::string(PSRC) + ":" + std::to_string(__LINE__));
		unsigned int id = (*it)["id"].get<unsigned int>();
		if (id > 3)
			throw std::string("Invalid counterId encountered! " + std::string(PSRC) + ":" + std::to_string(__LINE__));
		holder.push_back(player->getCounters()[id]);
	}

	// Sprawdza czy nie powtórzy³ siê ju¿ dany pionek.
	auto t = holder.begin();
	for (; t != holder.end(); ++t)
		if (std::count_if(holder.begin(), holder.end(), [&t](Counter* arg) {return (*t)->getId() == arg->getId(); }) != 1)
			throw std::string("Double counter id encountered " + std::string(PSRC) + ":" + std::to_string(__LINE__));

	it = obj["last"].begin();
	unsigned int index = 0;

	// Kopiuje pionki do last i sprawdza czy taki nie zosta³ dodany wczeœniej.
	for (; it != obj["last"].end(); ++it) {
		for (auto lit = (*it).begin(); lit != (*it).end(); ++lit) {
			if ((*lit)["ownedBy"].get<unsigned int>() != player->getId())
				throw std::string("Invalid owner encountered! " + std::string(PSRC) + ":" + std::to_string(__LINE__));
			unsigned int id = (*lit)["id"].get<unsigned int>();
			if (id > 3)
				throw std::string("Invalid counterId encountered! " + std::string(PSRC) + ":" + std::to_string(__LINE__));
			// Sprawdza czy dotychczas nie by³o takiego pionka.
			for (unsigned int i{ 0 }; i <= index; ++i)
				if (std::count_if(last[i].begin(), last[i].end(), [&id](Counter* arg) {return id == arg->getId(); }) != 0)
					throw std::string("Double counter id encountered " + std::string(PSRC) + ":" + std::to_string(__LINE__));
			// Czy nie znajduje siê ju¿ w domku.
			if (std::count_if(holder.begin(), holder.end(), [&id](Counter* arg) {return id == arg->getId(); }) != 0)
				throw std::string("Counter is in holder " + std::string(PSRC) + ":" + std::to_string(__LINE__));
			last[index].push_back(player->getCounters()[id]);
		}
		index++;
	}
}


Counter* PlayerContainer::holderPop() {
	if (holder.empty())
		return nullptr;
	Counter* c = holder.back();
	holder.pop_back();

	return c;
}
bool PlayerContainer::addToHolder(Counter* c) {
	if (holder.size() == 4) // Jeœli pe³ny
		return false;

	if (std::find(player->getCounters().begin(), player->getCounters().end(), c) == player->getCounters().end()) // Zabezpieczenie przed dodaniem pionków spoza udostêpnionych.
		return false;

	if (std::find(holder.begin(), holder.end(), c) != holder.end()) // Zabezpieczenie przed dodaniem istniej¹cego pionka.
		return false;

	holder.push_back(c);
	return true;
}
bool PlayerContainer::addToLast(Counter* c, unsigned int offset) {
	if (offset > 5) // Zabezpieczenie przed podaniem zbyt du¿ego przesuniêcia.
		return false;

	if (std::find(holder.begin(), holder.end(), c) != holder.end()) // Dodanie pionka znajduj¹cego siê w domku.
		return false;

	if (std::find(player->getCounters().begin(), player->getCounters().end(), c) == player->getCounters().end()) // Zabezpieczenie przed dodaniem pionków spoza udostêpnionych.
		return false;

	for (auto v : last)
		if (std::find(v.begin(), v.end(), c) != v.end())
			return false;

	last[offset].push_back(c);
	return true;
}
bool PlayerContainer::moveOnLast(unsigned int fieldNo, unsigned int offset) {
	if (fieldNo > 5 || offset > 6)// Zabezpiecznie przed zbyt du¿ym offsetem lub wybraniem pionka na koñcu.
		return false;

	std::vector<Counter*>& v = last[fieldNo];

	if (v.empty()) // Zabezpieczenie przed pustym polem
		return false;

	Counter* p = v.back();
	v.pop_back();

	if (fieldNo + offset > 5)
		last[6 - (fieldNo + offset) % 5].push_back(p);
	else
		last[fieldNo + offset].push_back(p);

	return true;
}

unsigned int PlayerContainer::lastCount(unsigned int fieldNo) {
	if (fieldNo > 5)
		return false;
	return static_cast<unsigned int>(last[fieldNo].size());
}

std::array<unsigned int, 6> PlayerContainer::getLastCount() {
	std::array<unsigned int, 6> counts{ 0U,0U,0U,0U,0U,0U };
	unsigned int i = 0;
	for (auto c : last)
		counts[i++] = static_cast<unsigned int>(c.size());
	return counts;
}

bool PlayerContainer::allIn() {
	return last[5].size() == 4;
}


std::ostream& operator<< (std::ostream& os, const PlayerContainer& e) {
	os << "{\"startPos\":" << e.startPos << ",";
	os << "\"playerObj\":" << *e.player << ",";
	os << "\"holder\":[";
	auto it = e.holder.begin();
	while (it != e.holder.end()) {
		os << *(*it);
		++it;
		if (it != e.holder.end())
			os << ",";
	}
	os << "],\"last\":[";
	auto lit = e.last.begin();
	while (lit != e.last.end()) {
		os << "[";
		auto c = (*lit).begin();
		while (c != (*lit).end()) {
			os << *(*c);
			++c;
			if (c != (*lit).end())
				os << ",";
		}
		os << "]";
		lit++;
		if (lit != e.last.end())
			os << ",";
	}
	os << "]}";
	return os;
}

std::string PlayerContainer::str() {
	std::stringstream ss;
	ss << "<PlayerContainer object 0x" << std::hex << std::uppercase << this << ">:\n{\n" << std::resetiosflags(std::ios_base::basefield);
	ss << (*player).str() << '\n';
	ss << "Holder size : " << holder.size() << '\n';
	ss << "Start position: " << startPos << '\n';
	ss << "Counters in last count: [ ";
	for (auto& c : last)
		ss << c.size() << ' ';
	ss << "]\n}\n";
	return ss.str();
}

std::string PlayerContainer::json() {
	std::stringstream ss;
	ss << "{\"startPos\":" << startPos << ",";
	ss << "\"playerObj\":" << player->json() << ",";
	ss << "\"holder\":[";
	auto it = holder.begin();
	while (it != holder.end()) {
		ss << (*it)->json();
		++it;
		if (it != holder.end())
			ss << ",";
	}
	ss << "],\"last\":[";
	auto lit = last.begin();
	while (lit != last.end()) {
		ss << "[";
		auto c = (*lit).begin();
		while (c != (*lit).end()) {
			ss << (*c)->json();
			++c;
			if (c != (*lit).end())
				ss << ",";
		}
		ss << "]";
		lit++;
		if (lit != last.end())
			ss << ",";
	}
	ss << "]}";

	return ss.str();
}


PlayerContainer::~PlayerContainer() {
	delete player;
}
