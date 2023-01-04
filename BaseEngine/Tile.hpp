#pragma once
#include "Counter.hpp"
#include "Player.hpp"
#include <vector>
#include <map>

/** Klasa do obs�ugi pola planszy.
* @author Jakub Jach &copy; 2022
*/
class Tile
{
	/** Wektor z pionkami stoj�cymi na danym polu. */
	std::vector<Counter*> counters;
	/** Zmienna okre�laj�ca czy wiele pionk�w mo�e sta� na tym polu. */
	bool manyCanStand;
public:
	/** Zmienna okre�laj�ca czy wiele pionk�w mo�e sta� na tym polu. */
	bool allowManyPlayers() { return manyCanStand; }
	/** Wektor z ostatnio zbitymi pionkami. */
	std::vector<Counter*> lastBeat;
	/** Domy�lny konstruktor klasy.
	* @param manyCanStand - Czy mo�na postawi� wiele pionk�w na danym polu.
	*/
	Tile(bool manyCanStand = false);
	/** S�u�y do dodawania pionka do pola. Je�li podany wska�nik ju� znajduje si� na polu to nic si� nie dzieje.
	* Dodaje zbite pionki do zmiennej lastBeat.
	* @param c - Wska�nik do obiektu pionka.
	* @return True je�li dodanie pionka powiod�o si� lub false je�li nie.
	*/
	bool addToTile(Counter* c);
	/** Usuwa wszystkie pionki danego gracza z pola. UWAGA: Nie aktualizuje to ostatnio zbitych pionk�w!.
	* @param playerId - Identyfikator gracza, kt�rego pionki nale�y usun��.
	*/
	void removePlayerCounters(const unsigned int playerId);
	/** @return Wektor z pionkami stoj�cymi na polu. */
	std::vector<Counter*>& getCounters() { return counters; }

	/** Przenosi pionek gracza na inne pole.
	* @param to - Docelowe pole, na kt�rym ma si� znale�� pionek.
	* @param whose - Gracz, kt�rego pionek przenie��.
	* @return true je�li uda�o si� przenie�� pionek lub false w przeciwnym wypadku.
	*/
	bool movePlayerCounter(Tile& to, Player& whose);
	/** U�ywane do zmapowania pionk�w do GUI.
	* @return Mapa z identyfikatorami graczy i ilo�ci� pionk�w dla ka�dego z nich.
	*/
	std::map<unsigned int, int>getPlayersCount();

	/**
	* @return Czy pionek gracza stoi na danym polu.
	*/
	bool hasCounter(Player& player);
	/**
	* Operator przypisania.
	* @param t - Pole, kt�rego warto�� ma by� przypisana naszemu polu.
	* @return Referencja bo *this.
	*/
	Tile& operator=(const Tile& t);

	friend std::ostream& operator<< (std::ostream& os, const Tile& t);
	/**
	* Zwraca reprezentacj� obiektu w bardziej czytelnej postaci
	*/
	std::string str();
	/**
	* Zwraca obiekt w postaci tekstu JSON.
	*/
	std::string json();
};

