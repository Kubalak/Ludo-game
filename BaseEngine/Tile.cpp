#include "Tile.hpp"

Tile::Tile(bool manyCanStand):
	manyCanStand(manyCanStand) {

}

bool Tile::addToTile(Counter* c) {
	lastBeat.clear(); //Czyœæ wektor ostatnio zbitych elementów.
	if (manyCanStand) {
		if (std::find(counters.begin(), counters.end(), c) == counters.end())
		   counters.push_back(c);
		return true;
	}
	
	bool hasBeenErased = false;
	for (std::vector<Counter*>::iterator it = counters.begin(); it != counters.end(); it++)
		if ((*it)->getOwner() != c->getOwner())
		{
			lastBeat.push_back(*it);
			counters.erase(it);
			hasBeenErased = true;
		}
	counters.push_back(c);
	return hasBeenErased;
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
	while (it != counters.end())
		if ((*it)->getOwner() == whose.getId())
		{
			counters.erase(it); // Usuwa z obecnego kafelka
			return to.addToTile(*it); // Przesuwa na docelowy kafelek.
		}

	return false;

}