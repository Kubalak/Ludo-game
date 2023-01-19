#include "Tile.hpp"
#include <algorithm>
Tile::Tile(bool manyCanStand) :
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
		counters.erase(std::remove_if(counters.begin(), counters.end(), [=](Counter* cn) {return cn->getOwner() != c->getOwner(); }), counters.end());
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
	for (; it != counters.end(); it++)
		if ((*it)->getOwner() == whose.getId())
		{
			bool res = to.addToTile(*it); // Przesuwa na docelowy kafelek.
			if (res)
				counters.erase(it); // Usuwa z obecnego kafelka
			return res;
		}

	return false;
}

Tile& Tile::operator=(const Tile& t) {
	lastBeat = t.lastBeat;
	manyCanStand = t.manyCanStand;
	counters = t.counters;
	return *this;
}


std::ostream& operator<< (std::ostream& os, const Tile& t) {
	os << "{ \"manyCanStand\":" << std::boolalpha << t.manyCanStand << std::resetiosflags(std::ios_base::basefield) << ",";
	os << "\"lastBeat\":[";
	auto it = t.lastBeat.begin();
	for (; it != t.lastBeat.end();) {
		os << *(*it);
		++it;
		if (it != t.lastBeat.end())
			os << ",";
	}
	os << "],\"counters\":[";
	it = t.counters.begin();
	for (; it != t.counters.end();) {
		os << *(*it);
		++it;
		if (it != t.counters.end())
			os << ",";
	}
	os << "]}";
	return os;
}

std::string Tile::str() {
	std::stringstream ss;
	ss << "<Tile object 0x" << std::hex << std::uppercase << this << ">:\n" << std::resetiosflags(std::ios_base::basefield);
	ss << "Allow many players: " << std::boolalpha << manyCanStand << std::resetiosflags(std::ios_base::basefield) << '\n';
	ss << "Total number of counters: " << counters.size() << "\nCounters:\n";
	if (!counters.empty())
		ss << "\n ";
	for (auto* p : counters)
		ss << (*p).str() << "\n ";
	return ss.str();
}

std::string Tile::json() {
	std::stringstream ss;
	ss << "{ \"manyCanStand\":" << std::boolalpha << manyCanStand << std::resetiosflags(std::ios_base::basefield) << ",";
	ss << "\"lastBeat\":[";
	auto it = lastBeat.begin();
	for (; it != lastBeat.end();) {
		ss << (*it)->json();
		++it;
		if (it != lastBeat.end())
			ss << ",";
	}
	ss << "],\"counters\":[";
	it = counters.begin();
	for (; it != counters.end();) {
		ss << (*it)->json();
		++it;
		if (it != counters.end())
			ss << ",";
	}
	ss << "]}";
	return ss.str();
}