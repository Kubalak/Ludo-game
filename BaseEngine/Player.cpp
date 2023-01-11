#include "Player.hpp"
// U¿yta do tworzenia UUID
#include "uuid_v4.h"

UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator; // Generator do UUID.

//int Player::currId = 0;

Player::Player() :
	id(static_cast<unsigned int>(uuidGenerator.getUUID().hash())),
	nickname("anonymous") {
	for (int i(0); i < 4; ++i)
		counters[i] = new Counter(id, i);
}

Player::Player(std::string nick) :
	id(static_cast<unsigned int>(uuidGenerator.getUUID().hash())),
	nickname(nick) {
	for (int i(0); i < 4; ++i)
		counters[i] = new Counter(id, i);
}

Player::Player(std::string nick, unsigned int id) :
	id(id),
	nickname(nick) {
	for (int i(0); i < 4; ++i)
		counters[i] = new Counter(id, i);
}

Player::Player(nlohmann::json obj) :
	id(obj["id"].get<unsigned int>()),
	nickname(obj["nick"]) {
	for (int i(0); i < 4; ++i)
		counters[i] = new Counter(id, i);
}

Player::~Player() {
	for (int i(0); i < 4; ++i)
		delete counters[i];
}

std::array<Counter*, 4>& Player::getCounters() {
	return counters;
}


std::string Player::str() {

	std::stringstream ss;
	ss << "<Player object 0x" << std::hex << std::uppercase << this << std::resetiosflags(std::ios_base::basefield) << ">: Nick: " << nickname << " Id: " << id;
	return ss.str();
}

std::ostream& operator<< (std::ostream& os, const Player& e) {

	os << "{\"nick\":\"" << e.nickname << "\",\"id\":" << std::to_string(e.id) << "}";
	return os;
}

std::string Player::json() {
	return "{\"nick\":\"" + nickname + "\",\"id\":" + std::to_string(id) + "}";
}