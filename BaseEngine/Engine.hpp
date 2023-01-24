#pragma once
#include <map>
#include "Dice.hpp"
#include "Tile.hpp"
#include "PlayerContainer.hpp"

//TODO: Obs�uga Ctr-C itp. (zabezpieczenie przed niekontrolowanym zamkni�ciem)
//TODO: (WIN) Brak blokowania konsoli po klikni�ciu

/**
* Klasa enum dla stan�w silnika.
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
	Nr aktualnego gracza od 0 do liczby graczy.
	*/
	int currentPlayer;
	/** Obecny stan silnika */
	EngineStates state;
	/** Zbi�r, kt�ry przechowuje graczy w postaci <�wiartka, gracz> */
	std::map<int, PlayerContainer*> players;
	/** Tablica wynik�w */
	std::vector<Player*> top;
	/**
	Podstawowa plansza do Chi�czyka.
	*/
	std::array<Tile, 52> tiles;
	/**
	Kostka do gry.
	*/
	Dice dice;
	/** Zwraca dystans jaki pokona gracz je�li chce przesun�� pionek na wybrane pole.
	* @param c - Kontener z danymi gracza.
	* @param dest - Docelowy kafelek na planszy.
	* @return Odleg�o�� od punktu pocz�tkowego gracza.
	*/
	unsigned int getDistance(PlayerContainer& c, unsigned int dest);
	/**
	* Zwraca aktualny obiekt PlayerContainer.
	* @return Obecny PlayerContainer.
	*/
	PlayerContainer& getCurrentPlayerContainer() { return *std::next(players.begin(), currentPlayer)->second; }
	/**
	* Przesuwa gracza na planszy.
	* @param fieldNo Numer pola na planszy.
	* @return true przy powodzeniu lub false w przeciwnym wypadku.
	*/
	bool moveCounterOnBoard(unsigned int fieldNo);
	/**
	* Przesuwa gracza na ostatnich polach.
	* @param fieldNo Numer pola.
	* @return true przy powodzeniu lub false w przeciwnym wypadku.
	*/
	bool moveCounterOnLast(unsigned int fieldNo);
	/**
	* Dodaje pionek na ko�cowe pola na pozycj� wskazan� przez offset.
	* @param from Numer pola na planszy.
	* @param offset O ile przesun�� pionek na ko�cowych polach.
	* @return true przy powodzeniu lub false w przeciwnym wypadku.
	*/
	bool moveCounterToLast(unsigned int from, unsigned int offset);
	/**
	* Przenosi pionki z kafelka z powrotem do domk�w.
	* @param t Referencja do kafelka, z kt�rego pobrane maj� zosta� zbite pionki.
	* @return true przy powodzeniu lub false w przeciwnym wypadku.
	*/
	bool beatCountersToHolder(Tile& t);
	/**
	Kolejny krok w grze. Aktualizuje informacje o wykonaiu ruchu czy rzucie kostk� oraz zmienia aktywnego gracza.
	@return true przy powodzeniu lub false w przeciwnym wypadku.
	*/
	bool step();

public:
	/**
	Wersja silnika
	*/
	static const std::string _VERSION;
	/**
	Mapa stan�w silnika na ci�g znak�w.
	*/
	static const std::map<EngineStates, std::string> stateStr;
	/**
	Mapa stan�w silnika na warto�� liczbow�.
	*/
	static const std::map<EngineStates, int> stateInt;
	/**
	Mapa warto�ci liczbowej na stan silnika.
	*/
	static const std::map<int, EngineStates> intState;

	/**
	* Domy�lny konstruktor klasy Engine
	*/
	Engine();
	/** Tworzy obiekt na bazie przekazanego obiektu JSON.
	* @param obj - Obiekt, na bazie kt�rego ma by� tworzony silnik.
	*/
	Engine(nlohmann::json&);

	/** Pozwala doda� gracza do wybranej �wiartki planszy.
	* @param player - Gracz, kt�ry ma zosta� dodany UWAGA: przekaza� new Player(), poniewa� gracze s� usuwani przy destrukcji obiektu (aby nie mo�na ich by�o u�y� przy nowej grze).
	* @param quarter - �wiartka, w kt�rej gracz mo�e rozpocz�� gr� od 1 do 4.
	*/
	virtual bool addPlayer(Player* player, unsigned int quarter);

	/** Pobiera aktualnego gracza.
	* @return Wska�nik na gracza aktualnie posiadaj�cego ruch lub nullptr je�li pobranie go jest niemo�liwe.
	*/
	Player* getCurrentPlayer() { if (currentPlayer < 0 || players.size() == 0)return nullptr; return std::next(players.begin(), currentPlayer)->second->getPlayerPtr(); }

	/** Inicjuje gr�.
	* Powoduje to zablokowanie mo�liwo�ci dodawnia graczy i ustawia stan rozgrywki.
	* @return true je�li mo�liwe jest uruchomienie gry lub false w przeciwnym wypadku.
	*/
	virtual bool start();

	/** S�u�y do rzucania kostk�.
	* @return Liczba oczek wyrzucona na kostce.
	*/
	virtual unsigned int rollDice();

	/** S�u�y do pobrania liczby oczek wyrzuconych w ostatnim rzucie.
	* @return Liczba oczek wyrzucona na kostce.
	*/
	unsigned int getDice() { return dice.getLast(); }

	/** S�u�y do poruszania pionkiem gracza. Jako gracz poruszaj�cy wybierany jest aktualny gracz.
	* @param fieldNo - Pole, z kt�rego ma ruszy� si� pionek. Dla wystawienia pionka gracza nale�y u�y� warto�ci < 0. Aby ruszy� pionek na ostatnich sze�ciu polach nale�y wybra� warto�ci 101-105 201-205 301-305 401-405
	* @return true je�li ruch si� powiedzie lub false w przeciwnym razie np. pionek nie stoi na danym polu.
	*/
	virtual bool move(int fieldNo);

	/** Informuje, czy wszyscy gracze zako�czyli gr� tj. czy wszystkie ich pionki dotar�y do ostatniego pola.
	* @return Czy nale�y zako�czy� rozgrywk�.
	*/
	bool finished();

	/** Pobiera list� z polami planszy.
	* @return Lista z polami na planszy.
	*/
	std::array<Tile, 52>& getTiles() { return tiles; }
	/** Zwraca list� z liczb� pionk�w dla gracza z danej �wiartki.
	* @return Lista z liczb� pionk�w na ka�dym z p�l.
	*/
	std::array<unsigned int, 6> getLast(unsigned int quarter) { return players[quarter - 1]->getLastCount(); }

	/** Zwraca liczb� pionk�w w domku dla gracza z danej �wiartki.
	* @param quarter - Numer �wiartki, z kt�rej ma zosta� pobrana ilo�� pionk�w w domku.
	* @return Liczba pionk�w w domku dla danej�wiartki.
	*/
	unsigned int getHolderCount(unsigned int quarter) { return players[quarter - 1]->holderCount(); }
	/**
	* Zwraca map� z kluczem b�d�cym �wiartk� planszy a warto�ci� id gracza.
	* @return Mapa okre�laj�ca powi�zania �wiartki z graczem.
	*/
	std::map<unsigned int, unsigned int> getQuarters();

	/**
	* Zwraca referencj� do obiektu PlayerContainer.
	* @param quarter �wiartka, z kt�rej ma zosta� pobrany PlayerContainer.
	* @return Referencja na PlayerContainer z danej �wiartki lub wyj�tek przy podaniu z�ej warto�ci �wiartki.
	*/
	PlayerContainer& getPlayerContainer(unsigned int quarter) { return *players[quarter - 1]; }

	/**
	* Zwraca aktualny stan silnika.
	* @return Klasa enum EngineStates aktualnego stanu.
	*/
	EngineStates getCurrentState() { return state; }
	/** Zwraca wektor z wynikami graczy */
	std::vector<Player*>& getTop() { return top; }

	/**
	* Umo�liwia przekierowanie do strumienia.
	* Wyj�cie w postaci takiej jak metoda json() (bez jej wywo�ywania)
	* @param os Strumie� wyj�ciowy
	* @param e Obiekt silnika, kt�ry ma zosta� wy�wietlony.
	* @return Strumie� os.
	*/
	friend std::ostream& operator<< (std::ostream& os, const Engine& e);
	/**
	* Zwraca reprezentacj� obiektu w bardziej czytelnej postaci
	*/
	std::string str();
	/**
	* Zwraca obiekt w postaci tekstu JSON.
	*/
	std::string json();

	/** Domy�lny destruktor usuwa wszystkich graczy*/
	~Engine();
};


