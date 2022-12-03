#include "PlayerContainer.hpp"
#include <algorithm>

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
		last[6 - (fieldNo + offset) % 6].push_back(p);
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

#ifdef _DEBUG
std::ostream& operator<< (std::ostream& os, const PlayerContainer& e) {
	os << "<PlayerContainer object 0x" << std::hex << std::uppercase << &e << ">:\n{\n" << std::resetiosflags(std::ios_base::basefield);
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
