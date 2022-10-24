#include "PlayerContainer.hpp"
PlayerContainer::PlayerContainer(Player* p) :
	player(p),
	hasFinished(false) {
}

bool PlayerContainer::areAllIn() {
	hasFinished = last[5].size() == 4;
	return hasFinished;
}

Counter* PlayerContainer::holderPop() {
	if (holder.empty())
		return NULL;
	Counter* c = holder.back();
	holder.pop_back();

	return c;
}
bool PlayerContainer::addToHolder(Counter* c) {
	if (holder.size() == 4) // Je�li pe�ny
		return false;
	
	//if (std::find(player->counters.begin(), player->counters.end(), c) == player->counters.end()) // Zabezpieczenie przed dodaniem pionk�w spoza udost�pnionych.
	//	return false;

	if (std::find(holder.begin(), holder.end(), c) != holder.end()) // Zabezpieczenie przed dodaniem istniej�cego pionka.
		return false;

	holder.push_back(c);
	return true;
}
bool PlayerContainer::addToLast(Counter* c, unsigned int offset) {
	if (offset > 6) // Zabezpieczenie przed podaniem zbyt du�ego przesuni�cia.
		return false;

	//if (std::find(player->counters.begin(), player->counters.end(), c) == player->counters.end()) // Zabezpieczenie przed dodaniem pionk�w spoza udost�pnionych.
	//	return false;

	for (auto v : last)
		if (std::find(v.begin(), v.end(), c) != v.end())
			return false;

	last[offset].push_back(c);
	return true;
}
bool PlayerContainer::moveOnLast(unsigned int fieldNo, unsigned int offset) {
	if (fieldNo > 5 || offset > 6)// Zabezpiecznie przed zbyt du�ym offsetem lub wybraniem pionka na ko�cu.
		return false;

	std::vector<Counter*> v = last[fieldNo];

	if (v.empty()) // Zabezpieczenie przed pustym polem
		return false;

	Counter* p = v.back();
	v.pop_back();

	if (fieldNo + offset > 5)
		last[6 - (fieldNo + offset) % 7].push_back(p);
	else
		last[fieldNo + offset].push_back(p);

	return true;
}

unsigned int PlayerContainer::lastCount(unsigned int fieldNo) {
	if (fieldNo > 5)
		return false;
	return last[fieldNo].size();
}
bool PlayerContainer::allIn() {
	return areAllIn();
}

PlayerContainer::~PlayerContainer() {
	delete player;
}
