#pragma once
#include <string>
#include "CounterContainer.hpp"

// Klasa do obs³ugi gracza
class Player {
	unsigned int id;
	std::string nickname;
	CounterContainer* container;
public:
	/*
	* Tworzy obiekt gracza z domyœlnymi ustawieniami.
	*/
	Player();
	Player(std::string nick);
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
	CounterContainer& getContainer();
	/* Pozwala na wykonanie ruchu przez gracza.
	* @return Czy ruch zakoñczono powodzeniem.
	*/
	bool move(unsigned int countNo);

	~Player();
};