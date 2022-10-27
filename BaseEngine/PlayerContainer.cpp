#include "PlayerContainer.hpp"
PlayerContainer::PlayerContainer(Player* p, unsigned int startPos) :
	player(p),
	startPos(startPos) {
	for (auto* c : p->getCounters())
		holder.push_back(c);
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
	
	//if (std::find(player->counters.begin(), player->counters.end(), c) == player->counters.end()) // Zabezpieczenie przed dodaniem pionków spoza udostêpnionych.
	//	return false;

	if (std::find(holder.begin(), holder.end(), c) != holder.end()) // Zabezpieczenie przed dodaniem istniej¹cego pionka.
		return false;

	holder.push_back(c);
	return true;
}
bool PlayerContainer::addToLast(Counter* c, unsigned int offset) {
	if (offset > 6) // Zabezpieczenie przed podaniem zbyt du¿ego przesuniêcia.
		return false;

	//if (std::find(player->counters.begin(), player->counters.end(), c) == player->counters.end()) // Zabezpieczenie przed dodaniem pionków spoza udostêpnionych.
	//	return false;

	for (auto v : last)
		if (std::find(v.begin(), v.end(), c) != v.end())
			return false;

	last[offset].push_back(c);
	return true;
}
bool PlayerContainer::moveOnLast(unsigned int fieldNo, unsigned int offset) {
	if (fieldNo > 5 || offset > 6)// Zabezpiecznie przed zbyt du¿ym offsetem lub wybraniem pionka na koñcu.
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
	return last[5].size() == 4;
}

#ifdef _DEBUG
std::ostream& operator<< (std::ostream& os, const PlayerContainer& e) {
	os << "<PlayerContainer object " << std::hex << std::uppercase << &e << ">:\n{\n" << std::resetiosflags(std::ios_base::basefield);
	os << "  " << *e.player << '\n';
	os << "  Holder size: " << e.holder.size() << '\n';
	os << "  Start position: " << e.startPos << '\n';
	os << "  Counters in last count: [ ";
	for (auto& c : e.last)
		os << c.size() << ' ';
	os << "]\n}\n";

	return os;
}
#endif

PlayerContainer::~PlayerContainer() {
	delete player;
}
