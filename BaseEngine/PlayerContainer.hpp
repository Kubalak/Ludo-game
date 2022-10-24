#pragma once
#include <vector>
#include "Player.hpp"

class PlayerContainer
{
	Player* player;
	std::array<std::vector<Counter*>, 6>last;
	std::vector<Counter*> holder;
	bool hasFinished;
	bool areAllIn();

public:
	PlayerContainer(Player* p);
	~PlayerContainer();
	Counter* holderPop();
	bool addToHolder(Counter* c);
	bool addToLast(Counter* c, unsigned int offset = 0);
	bool moveOnLast(unsigned int fieldNo, unsigned int offset);
	unsigned int holderCount() { return holder.size(); }
	unsigned int lastCount(unsigned int fieldNo);
	Player& getPlayer() { return *player; }
	bool allIn();

};

