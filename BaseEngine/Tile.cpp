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