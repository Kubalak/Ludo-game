#include "Player.hpp"

int Player::currId = 0;

Player::Player():
	id(Player::currId++),
	nickname("anonymous")	{
	for (int i(0); i < 4; ++i)
		counters[i] = new Counter(getId(), i);
}

Player::Player(std::string nick):
	id(Player::currId++),
	nickname(nick) {
	for (int i(0); i < 4; ++i)
		counters[i] = new Counter(getId(), i);
}

Player::Player(std::string nick, unsigned int id):
	id(id),
	nickname(nick) {
	for (int i(0); i < 4; ++i)
		counters[i] = new Counter(getId(), i);
}

Player::~Player() {
	for (int i(0); i < 4; ++i)
		delete counters[i];
}

std::array<Counter*, 4>& Player::getCounters() {
	return counters;
}

#ifdef _DEBUG
std::ostream& operator<< (std::ostream& os, const Player& e) {
	os << "<Player object 0x" << std::hex << std::uppercase << &e << std::resetiosflags(std::ios_base::basefield) << ">: Nick: " << e.nickname << " Id: " << e.id;
	
	return os;
}
#endif
std::string Player::json() {
	return "{\"nick\":\"" + nickname + "\",\"id\":" + std::to_string(id) + "}";
}