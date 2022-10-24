#pragma once
#include <map>
#include "Dice.hpp"
#include "Tile.hpp"
#include "PlayerContainer.hpp"

class Engine
{
	int currentPlayer;
	bool gameStarted;
	bool moveMade;
	bool diceRolled;
	//Zbiór, który przechowuje graczy w postaci <æwiartka,gracz>
	std::map<int,PlayerContainer*> players;
	// Podstawowa plansza do Chiñczyka.
	std::array<Tile,52> tiles;
	// Kostka do gry.
	Dice dice;
	void resetMove();
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
	Player& getCurrentPlayer() { return std::next(players.begin(), currentPlayer)->second->getPlayer(); }

	void start();
	/*
	* @return Informacja o tym czy gra zosta³a zaczêta.
	*/
	bool isStarted() { return gameStarted; }
	/*
	* @return Informacja czy wykonano ruch.
	*/
	bool isMoveMade() { return moveMade; }
	/*
	* @return Czy wykonano rzut kostk¹
	*/
	bool isDiceRolled() { return diceRolled; }
	/*
	* Kolejny krok w grze. Aktualizuje informacje o wykonaiu ruchu czy rzucie kostk¹ oraz zmienia aktywnego gracza.
	*/
	bool step();
	/* S³u¿y do rzucania kostk¹.
	* @return Liczba oczek wyrzucona na kostce.
	*/
	unsigned int rollDice();
	/* S³u¿y do poruszania pionkiem gracza.
	* @param p - Gracz, który ma siê ruszyæ.
	* @param fieldNo - Pole, z którego ma ruszyæ siê pionek.
	* @return true jeœli ruch siê powiedzie lub false w przeciwnym razie np. pionek nie stoi na danym polu.
	*/
	bool move(Player& p, unsigned int fieldNo);
	/* Informuje, czy wszyscy gracze zakoñczyli grê tj. czy wszystkie ich pionki dotar³y do ostatniego pola.
	* @return Czy nale¿y zakoñczyæ rozgrywkê.
	*/
	bool finished();
	/* Pobiera listê z polami planszy.
	* @return Lista z polami na planszy.
	*/
	std::array<Tile, 52>& getTiles() { return tiles; }
};

