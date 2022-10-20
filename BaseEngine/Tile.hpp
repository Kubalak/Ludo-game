#pragma once
#include "Counter.hpp"
#include <vector>

class Tile
{
	std::vector<Counter*> counters;
public:
	// Zmienna okreœlaj¹ca czy wiele pionków mo¿e staæ na tym polu.
	const bool manyCanStand;
	// Wektor z ostatnio zbitymi pionkami.
	std::vector<Counter*> lastBeat;
	/* Domyœlny konstruktor klasy.
	* @param manyCanStand - Czy mo¿na postawiæ wiele pionków na danym polu.
	*/
	Tile(bool manyCanStand = false);
	/* S³u¿y do dodawania pionka do pola. Jeœli podany wskaŸnik ju¿ znajduje siê na polu to nic siê nie dzieje.
	* @param c - WskaŸnik do obiektu pionka.
	* @return True jeœli zosta³ zbity pionek lub false jeœli nie.
	*/
	bool addToTile(Counter* c);
	/* Usuwa wszystkie pionki danego gracza z pola. UWAGA: Nie aktualizuje to ostatnio zbitych pionków!.
	* @param playerId - Identyfikator gracza, którego pionki nale¿y usun¹æ.
	*/
	void removePlayerCounters(const unsigned int playerId);
	// @return Wektor z pionkami stoj¹cymi na polu.
	std::vector<Counter*> getCounters() { return counters; }
};

