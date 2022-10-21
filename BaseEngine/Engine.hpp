#pragma once
#include <map>
#include "Player.hpp"
#include "Dice.hpp"
#include "Tile.hpp"

class Engine
{
	int currentPlayer;
	bool gameStarted;
	//Zbi�r, kt�ry przechowuje graczy w postaci <�wiartka,gracz>
	std::map<int,Player*> players;
	// Podstawowa plansza do Chi�czyka.
	std::array<Tile,52> counters;
	// Kostka do gry.
	Dice dice;
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
	Player& getCurrentPlayer(){ return *players[currentPlayer]; }
	void start();
	void step() {}
	bool move(const Player&, unsigned int counterId) { return false; }
};

