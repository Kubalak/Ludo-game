#pragma once
#include "Counter.hpp"
#include <vector>

class Tile
{
	std::vector<Counter*> counters;
public:
	// Zmienna okre�laj�ca czy wiele pionk�w mo�e sta� na tym polu.
	const bool manyCanStand;
	// Wektor z ostatnio zbitymi pionkami.
	std::vector<Counter*> lastBeat;
	/* Domy�lny konstruktor klasy.
	* @param manyCanStand - Czy mo�na postawi� wiele pionk�w na danym polu.
	*/
	Tile(bool manyCanStand = false);
	/* S�u�y do dodawania pionka do pola. Je�li podany wska�nik ju� znajduje si� na polu to nic si� nie dzieje.
	* @param c - Wska�nik do obiektu pionka.
	* @return True je�li zosta� zbity pionek lub false je�li nie.
	*/
	bool addToTile(Counter* c);
	/* Usuwa wszystkie pionki danego gracza z pola. UWAGA: Nie aktualizuje to ostatnio zbitych pionk�w!.
	* @param playerId - Identyfikator gracza, kt�rego pionki nale�y usun��.
	*/
	void removePlayerCounters(const unsigned int playerId);
	// @return Wektor z pionkami stoj�cymi na polu.
	std::vector<Counter*> getCounters() { return counters; }
};

