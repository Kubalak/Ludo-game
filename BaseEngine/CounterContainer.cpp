#include "CounterContainer.hpp"

CounterContainer::CounterContainer(const unsigned int ownedBy):
	ownedBy(ownedBy) {
	for (int a = 0; a < 4;++a)
		all[a] = new Counter(ownedBy,a);

	for (auto* s : all)
		holder.push_back(s);
}

bool CounterContainer::moveToLast(unsigned int fieldNo, unsigned int offset) {
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

bool CounterContainer::addToLast(Counter* c, unsigned int offset) {
	if (offset > 6) // Zabezpieczenie przed podaniem zbyt du¿ego przesuniêcia.
		return false;

	if (std::find(all.begin(), all.end(), c) == all.end()) // Zabezpieczenie przed dodaniem pionków spoza udostêpnionych.
		return false;

	for (auto v : last)
		if (std::find(v.begin(), v.end(), c) != v.end())
			return false;

	last[offset].push_back(c);
	return true;
}

bool CounterContainer::addToHolder(Counter* c) {
	if (holder.size() == 4) // Jeœli pe³ny
		return false;

	if (std::find(all.begin(), all.end(), c) == all.end()) // Zabezpieczenie przed dodaniem pionków spoza udostêpnionych.
		return false;

	if (std::find(holder.begin(), holder.end(), c) != holder.end()) // Zabezpieczenie przed dodaniem istniej¹cego pionka.
		return false;

	holder.push_back(c);
	return true;
}

Counter* CounterContainer::holderPop() {
	if (holder.empty())
		return NULL;
	Counter* c = holder.back();
	holder.pop_back();

	return c;
}

CounterContainer::~CounterContainer() {
	for (auto* p : all)
		delete p;
}


