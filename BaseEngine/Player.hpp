#pragma once
#include <string>
#include <array>
#include "Counter.hpp"

// Klasa do obs³ugi gracza
class Player {
	unsigned int id;
	std::string nickname;
	std::array<Counter*,4> counters;
public:
	/*
	* Tworzy obiekt gracza z domyœlnymi ustawieniami.
	*/
	Player();
	Player(std::string nick);
	Player(std::string nick, unsigned int id);
	/* Metoda do pobrania id gracza.
	* @return Identyfikator gracza.
	*/
	unsigned int getId() { return id; }
	/* Metoda zwraca nazwê gracza.
	* @return Nick gracza.
	*/
	std::string getNick() { return nickname; }
	/* Zwraca zasobnik z pionkami dla gracza.
	* @return Referencja do zasobnika z pionkami.
	*/
	std::array<Counter*,4> getCounters();
	/* Pozwala na wykonanie ruchu przez gracza.
	* @return Czy ruch zakoñczono powodzeniem.
	*/
	bool move(unsigned int countNo);

#ifdef _DEBUG
	friend std::ostream& operator<< (std::ostream& os, const Player& e);
#endif

	~Player();
};