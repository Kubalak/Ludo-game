#pragma once
#include <string>
#include <array>
#include "Counter.hpp"

/** Klasa do obs�ugi gracza 
* @author Jakub Jach &copy; 2022 
*/
class Player {
	static int currId;
	unsigned int id;
	std::string nickname;
	std::array<Counter*,4> counters;
public:
	/**
	* Tworzy obiekt gracza z domy�lnymi ustawieniami.
	*/
	Player();
	/** Tworzy obiekt gracza z wybranym nickiem.
	* @param nick - Nick gracza.
	*/
	Player(std::string nick);
	/** Tworzy obiekt gracza z wybranym nickiem i identyfikatorem (zalecane u�ycie w wersji online).
	* @param nick - Nick gracza.
	* @param id - Identyfikator gracza.
	*/
	Player(std::string nick, unsigned int id);
	/** Metoda do pobrania id gracza.
	* @return Identyfikator gracza.
	*/
	unsigned int getId() { return id; }
	/** Metoda zwraca nazw� gracza.
	* @return Nick gracza.
	*/
	std::string getNick() { return nickname; }
	/** Zwraca zasobnik z pionkami dla gracza.
	* @return Referencja do zasobnika z pionkami.
	*/
	std::array<Counter*,4>& getCounters();
	/* Pozwala na wykonanie ruchu przez gracza.
	* @return Czy ruch zako�czono powodzeniem.
	*
	bool move(unsigned int countNo);*/

#ifdef _DEBUG
	/**
	* Umo�liwia przekierowanie do strumienia.
	*/
	friend std::ostream& operator<< (std::ostream& os, const Player& e);
#endif

	~Player();
};