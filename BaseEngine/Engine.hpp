#pragma once
#include <map>
#include "Player.hpp"
#include "Dice.hpp"
#include "Tile.hpp"

class Engine
{
	int currentPlayer;
	bool gameStarted;
	//Zbiór, który przechowuje graczy w postaci <æwiartka,gracz>
	std::map<int,Player*> players;
	// Podstawowa plansza do Chiñczyka.
	std::array<Tile,52> counters;
	// Kostka do gry.
	Dice dice;
public:
	// Domyœlny konstruktor klasy Engine
	Engine();
	~Engine();
	/* Pozwala dodaæ gracza do wybranej æwiartki planszy.
	* @param player - Gracz, który ma zostaæ dodany UWAGA: przekazaæ new Player(), poniewa¿ gracze s¹ usuwani przy destrukcji obiektu (aby nie mo¿na ich by³o u¿yæ przy nowej grze).
	* @param quarter - Æwiartka, w której gracz mo¿e rozpocz¹æ grê od 1 do 4.
	*/
	bool addPlayer(Player* player, unsigned int quarter);
	/* Pobiera aktualnego gracza.
	* @return Gracz aktualnie posiadaj¹cy ruch.
	*/
	Player& getCurrentPlayer(){ return *players[currentPlayer]; }
	void start();
	void step() {}
	bool move(const Player&, unsigned int counterId) { return false; }
};

