#pragma once
#include <map>
#include "Dice.hpp"
#include "Tile.hpp"
#include "PlayerContainer.hpp"

//TODO: Obs³uga Ctr-C itp. (zabezpieczenie przed niekontrolowanym zamkniêciem)
//TODO: (WIN) Brak blokowania konsoli po klikniêciu

/**
* Klasa enum dla stanów silnika.
*/
enum class EngineStates
{
	CREATED = 0,
	STARTED = 1,
	DICE_ROLLED = 2,
	MOVE_MADE = 3,
	STEP_MADE = 4
};

/** Klasa silnika gry w wersji offline.
* @author Jakub Jach &copy; 2022
*/

class Engine
{

protected:
	/**
	* Nr aktualnego gracza od 0 do liczby graczy.
	*/
	int currentPlayer;

	EngineStates state;
	//Zbiór, który przechowuje graczy w postaci <æwiartka,gracz>
	std::map<int, PlayerContainer*> players;
	/** Tablica wyników */
	std::vector<Player*> top;
	// Podstawowa plansza do Chiñczyka.
	std::array<Tile, 52> tiles;
	// Kostka do gry.
	Dice dice;
	/** Zwraca dystans jaki pokona gracz jeœli chce przesun¹æ pionek na wybrane pole.
	* @param c - Kontener z danymi gracza.
	* @param dest - Docelowy kafelek na planszy.
	* @return Odleg³oœæ od punktu pocz¹tkowego gracza.
	*/
	unsigned int getDistance(PlayerContainer& c, unsigned int dest);
	PlayerContainer& getCurrentPlayerContainer() { return *std::next(players.begin(), currentPlayer)->second; }

	bool moveCounterOnBoard(unsigned int fieldNo);
	bool moveCounterOnLast(unsigned int fieldNo);
	bool moveCounterToLast(unsigned int from, unsigned int offset);
	bool beatCountersToHolder(Tile& t);

public:
	/// Wersja silnika 
	static const std::string _VERSION;
	static const std::map<EngineStates, std::string> stateStr;
	static const std::map<EngineStates, int> stateInt;
	static const std::map<int, EngineStates> intState;

	/***
	* Domyœlny konstruktor klasy Engine
	*/
	Engine();
	/** Tworzy obiekt na bazie przekazanego obiektu JSON.
	* @param obj - Obiekt, na bazie którego ma byæ tworzony silnik.
	*/
	Engine(nlohmann::json&);

	/** Pozwala dodaæ gracza do wybranej æwiartki planszy.
	* @param player - Gracz, który ma zostaæ dodany UWAGA: przekazaæ new Player(), poniewa¿ gracze s¹ usuwani przy destrukcji obiektu (aby nie mo¿na ich by³o u¿yæ przy nowej grze).
	* @param quarter - Æwiartka, w której gracz mo¿e rozpocz¹æ grê od 1 do 4.
	*/
	bool addPlayer(Player* player, unsigned int quarter);

	/** Pobiera aktualnego gracza.
	* @return Gracz aktualnie posiadaj¹cy ruch.
	*/
	Player& getCurrentPlayer() { return std::next(players.begin(), currentPlayer)->second->getPlayer(); }

	/** Inicjuje grê.
	* Powoduje to zablokowanie mo¿liwoœci dodawnia graczy i ustawia stan rozgrywki.
	*/
	void start();

	/** Kolejny krok w grze. Aktualizuje informacje o wykonaiu ruchu czy rzucie kostk¹ oraz zmienia aktywnego gracza.
	*/
	bool step();

	/** S³u¿y do rzucania kostk¹.
	* @return Liczba oczek wyrzucona na kostce.
	*/
	unsigned int rollDice();

	/** S³u¿y do pobrania liczby oczek wyrzuconych w ostatnim rzucie.
	* @return Liczba oczek wyrzucona na kostce.
	*/
	unsigned int getDice() { return dice.getLast(); }

	/** S³u¿y do poruszania pionkiem gracza. Jako gracz poruszaj¹cy wybierany jest aktualny gracz.
	* @param fieldNo - Pole, z którego ma ruszyæ siê pionek. Dla wystawienia pionka gracza nale¿y u¿yæ wartoœci < 0. Aby ruszyæ pionek na ostatnich szeœciu polach nale¿y wybraæ wartoœci 101-105 201-205 301-305 401-405
	* @return true jeœli ruch siê powiedzie lub false w przeciwnym razie np. pionek nie stoi na danym polu.
	*/
	bool move(int fieldNo);

	/** Informuje, czy wszyscy gracze zakoñczyli grê tj. czy wszystkie ich pionki dotar³y do ostatniego pola.
	* @return Czy nale¿y zakoñczyæ rozgrywkê.
	*/
	bool finished();

	/** Pobiera listê z polami planszy.
	* @return Lista z polami na planszy.
	*/
	std::array<Tile, 52>& getTiles() { return tiles; }
	/** Zwraca listê z liczb¹ pionków dla gracza z danej æwiartki.
	* @return Lista z liczb¹ pionków na ka¿dym z pól.
	*/
	std::array<unsigned int, 6> getLast(unsigned int quarter) { return players[quarter - 1]->getLastCount(); }

	/** Zwraca liczbê pionków w domku dla gracza z danej æwiartki.
	* @param quarter - Numer æwiartki, z której ma zostaæ pobrana iloœæ pionków w domku.
	* @return Liczba pionków w domku dla danejæwiartki.
	*/
	unsigned int getHolderCount(unsigned int quarter) { return players[quarter - 1]->holderCount(); }
	/**
	* Zwraca mapê z kluczem bêd¹cym æwiartk¹ planszy a wartoœci¹ id gracza.
	* @return Mapa okreœlaj¹ca powi¹zania æwiartki z graczem.
	*/
	std::map<unsigned int, unsigned int> getQuarters();

	/**
	* Zwraca aktualny stan silnika.
	* @return Klasa enum EngineStates aktualnego stanu.
	*/
	EngineStates getCurrentState() { return state; }
	/** Zwraca wektor z wynikami graczy */
	std::vector<Player*>& getTop() { return top; }

	/**
	* Umo¿liwia przekierowanie do strumienia.
	*/
	friend std::ostream& operator<< (std::ostream& os, const Engine& e);
	/**
	* Zwraca reprezentacjê obiektu w bardziej czytelnej postaci
	*/
	std::string str();
	/**
	* Zwraca obiekt w postaci tekstu JSON.
	*/
	std::string json();

	~Engine();
};


