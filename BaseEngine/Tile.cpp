#include "Tile.hpp"
#include <algorithm>
Tile::Tile(bool manyCanStand):
	manyCanStand(manyCanStand) {

}

bool Tile::addToTile(Counter* c) {
	lastBeat.clear(); //Czyœæ wektor ostatnio zbitych elementów.
	if (std::find(counters.begin(), counters.end(), c) != counters.end())
		return false;
	if (manyCanStand) 
		counters.push_back(c);
	else {
		std::copy_if(counters.begin(), counters.end(), std::back_inserter(lastBeat), [=](Counter* cn) {return cn->getOwner() != c->getOwner(); });
		counters.erase(std::remove_if(counters.begin(), counters.end(), [=](Counter* cn) {return cn->getOwner() != c->getOwner(); }),counters.end());
		counters.push_back(c);
		return true;
	}
	
	return true;
}

void Tile::removePlayerCounters(const unsigned int playerId) {
	for (std::vector<Counter*>::iterator it = counters.begin(); it != counters.end(); it++)
		if ((*it)->getOwner() == playerId)
		{
			lastBeat.push_back(*it);
			counters.erase(it);
		}
}
bool Tile::hasCounter(Player& player) {
	for (auto* c : counters)
		if (c->getOwner() == player.getId())
			return true;
	return false;
}

std::map<unsigned int, int> Tile::getPlayersCount() {
	std::map<unsigned int, int>playersCount;
	for (auto* c : counters)
		if (playersCount.find(c->getOwner()) == playersCount.end())
			playersCount[c->getOwner()] = 1;
		else playersCount[c->getOwner()] += 1;
	
	return playersCount;
}

bool Tile::movePlayerCounter(Tile& to, Player& whose) {
	std::vector<Counter*>::iterator it = counters.begin();
	for (;it != counters.end();it++)
		if ((*it)->getOwner() == whose.getId())
		{
			bool res = to.addToTile(*it); // Przesuwa na docelowy kafelek.
			if (res)
				counters.erase(it); // Usuwa z obecnego kafelka
			return res;
		}

	return false;
}

Tile Tile::operator=(const Tile& t) {
	lastBeat = t.lastBeat;
	manyCanStand = t.manyCanStand;
	counters = t.counters;
	return *this;
}

#ifdef _DEBUG
std::ostream& operator<< (std::ostream& os, const Tile& t) {
	os << "<Tile object " << std::hex << std::uppercase << &t << ">:\n"<< std::resetiosflags(std::ios_base::basefield);
	os << "Allow many players: " << std::boolalpha << t.manyCanStand << std::resetiosflags(std::ios_base::basefield) << '\n';
	os << "Total number of counters: " << t.counters.size() << '\n';
	for (auto* p : t.counters)
		std::cout << (*p); 
	
	return os;
}
#endif