#pragma once
#include "Counter.hpp"
#include "Player.hpp"
#include <vector>
#include <map>

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
	std::vector<Counter*>& getCounters() { return counters; }

	/* Przenosi pionek gracza na inne pole.
	* @param to - Docelowe pole, na którym ma siê znaleŸæ pionek.
	* @return true jeœli zbity pionek lub false w przeciwnym wypadku (np. nie uda³o siê przesun¹æ pionka)
	*/
	bool movePlayerCounter(Tile& to, Player& whose);
	/*
	* @return Mapa z identyfikatorami graczy i iloœci¹ pionków.
	*/
	std::map<unsigned int, int>getPlayersCount();

	/*
	* @return Czy pionek gracza stoi na danym polu.
	*/
	bool hasCounter(Player& player);

#ifdef _DEBUG
	friend std::ostream& operator<< (std::ostream& os, const Tile& t);
#endif
};

