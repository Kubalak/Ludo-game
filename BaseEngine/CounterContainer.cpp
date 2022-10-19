#include "CounterContainer.hpp"

CounterContainer::CounterContainer(const unsigned int ownedBy):
	ownedBy(ownedBy){
	for (int a = 0; a < 4;++a)
		all[a] = new Counter(ownedBy,a);

	for (auto* s : all)
		holder.push_back(s);
}

Counter& CounterContainer::getCounter(unsigned int counterId) {

	return *all[counterId]; // Korzystamy z tego ¿e tablica all siê nie zmienia.
}

unsigned int CounterContainer::moveToLast(unsigned int counterId, unsigned int offset) {
	Counter* p = all[counterId]; // WskaŸnik do w³aœciwego pionka
	for (int s(0);s<4;++s)
	{
		std::vector<Counter*>::iterator it;
		it = std::find(last[s].begin(), last[s].end(), p);
		if (it != last[s].end())
		{
			last[s].erase(it);
			if (s + offset >= 4) {
				int remain = 4 - s;
				/*offset = ;*/
			}
			else {
				last[s + offset].push_back(p);
				return 0;
			}
		}
	}

}

bool CounterContainer::addToHolder(Counter* c) {
	if (c->getOwner() != ownedBy)
		return false;
	
	if (holder.size() == 4)
		return false;

	for (Counter* p : holder)
		if (p->getId() == c->getId())
			return false;
	
	holder.push_back(c);
	return true;
}

CounterContainer::~CounterContainer() {
	for (auto* p : all)
		delete p;
}


