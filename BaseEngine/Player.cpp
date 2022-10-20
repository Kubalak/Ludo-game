#include "Player.hpp"

unsigned int getPlayerId(void) {
	return 0;
}

Player::Player():
	id(0),
	nickname("anonymous"),
	container(new CounterContainer(id)) {

}

Player::Player(std::string nick):
	id(0),
	nickname(nick),
	container(new CounterContainer(id)) {

}

Player::Player(std::string nick, unsigned int id):
	nickname(nick),
	id(id) ,
	container(new CounterContainer(id)){
}

Player::~Player() {
	delete container;
}

CounterContainer& Player::getContainer() {
	return *container;
}

bool Player::move(unsigned int countNo) {
	return true;
}