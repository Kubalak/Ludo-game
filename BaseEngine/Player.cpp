#include "Player.hpp"

Player::Player():
	id(0),
	nickname("anonymous")	{
	for (int i(0); i < 4; ++i)
		counters[i] = new Counter(getId(), i);
}

Player::Player(std::string nick):
	id(0),
	nickname(nick) {
	for (int i(0); i < 4; ++i)
		counters[i] = new Counter(getId(), i);
}

Player::Player(std::string nick, unsigned int id):
	nickname(nick),
	id(id) {
	for (int i(0); i < 4; ++i)
		counters[i] = new Counter(getId(), i);
}

Player::~Player() {
	for (int i(0); i < 4; ++i)
		delete counters[i];
}

std::array<Counter*, 4> Player::getCounters() {
	return counters;
}

bool Player::move(unsigned int countNo) {
	return true;
}
