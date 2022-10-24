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
	//Zbi�r, kt�ry przechowuje graczy w postaci <�wiartka,gracz>
	std::map<int,PlayerContainer*> players;
	// Podstawowa plansza do Chi�czyka.
	std::array<Tile,52> tiles;
	// Kostka do gry.
	Dice dice;
	void resetMove();
public:
	// Domy�lny konstruktor klasy Engine
	Engine();
	~Engine();
	/* Pozwala doda� gracza do wybranej �wiartki planszy.
	* @param player - Gracz, kt�ry ma zosta� dodany UWAGA: przekaza� new Player(), poniewa� gracze s� usuwani przy destrukcji obiektu (aby nie mo�na ich by�o u�y� przy nowej grze).
	* @param quarter - �wiartka, w kt�rej gracz mo�e rozpocz�� gr� od 1 do 4.
	*/
	bool addPlayer(Player* player, unsigned int quarter);
	/* Pobiera aktualnego gracza.
	* @return Gracz aktualnie posiadaj�cy ruch.
	*/
	Player& getCurrentPlayer() { return std::next(players.begin(), currentPlayer)->second->getPlayer(); }

	void start();
	/*
	* @return Informacja o tym czy gra zosta�a zacz�ta.
	*/
	bool isStarted() { return gameStarted; }
	/*
	* @return Informacja czy wykonano ruch.
	*/
	bool isMoveMade() { return moveMade; }
	/*
	* @return Czy wykonano rzut kostk�
	*/
	bool isDiceRolled() { return diceRolled; }
	/*
	* Kolejny krok w grze. Aktualizuje informacje o wykonaiu ruchu czy rzucie kostk� oraz zmienia aktywnego gracza.
	*/
	bool step();
	/* S�u�y do rzucania kostk�.
	* @return Liczba oczek wyrzucona na kostce.
	*/
	unsigned int rollDice();
	/* S�u�y do poruszania pionkiem gracza.
	* @param p - Gracz, kt�ry ma si� ruszy�.
	* @param fieldNo - Pole, z kt�rego ma ruszy� si� pionek.
	* @return true je�li ruch si� powiedzie lub false w przeciwnym razie np. pionek nie stoi na danym polu.
	*/
	bool move(Player& p, unsigned int fieldNo);
	/* Informuje, czy wszyscy gracze zako�czyli gr� tj. czy wszystkie ich pionki dotar�y do ostatniego pola.
	* @return Czy nale�y zako�czy� rozgrywk�.
	*/
	bool finished();
	/* Pobiera list� z polami planszy.
	* @return Lista z polami na planszy.
	*/
	std::array<Tile, 52>& getTiles() { return tiles; }
};

