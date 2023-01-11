#pragma once
#include "Counter.hpp"
#include "Player.hpp"
#include <vector>
#include <map>

/** Klasa do obs³ugi pola planszy.
* @author Jakub Jach &copy; 2022
*/
class Tile
{
	/** Wektor z pionkami stoj¹cymi na danym polu. */
	std::vector<Counter*> counters;
	/** Zmienna okreœlaj¹ca czy wiele pionków mo¿e staæ na tym polu. */
	bool manyCanStand;
public:
	/** Zmienna okreœlaj¹ca czy wiele pionków mo¿e staæ na tym polu. */
	bool allowManyPlayers() { return manyCanStand; }
	/** Wektor z ostatnio zbitymi pionkami. */
	std::vector<Counter*> lastBeat;
	/** Domyœlny konstruktor klasy.
	* @param manyCanStand - Czy mo¿na postawiæ wiele pionków na danym polu.
	*/
	Tile(bool manyCanStand = false);
	/** S³u¿y do dodawania pionka do pola. Jeœli podany wskaŸnik ju¿ znajduje siê na polu to nic siê nie dzieje.
	* Dodaje zbite pionki do zmiennej lastBeat.
	* @param c - WskaŸnik do obiektu pionka.
	* @return True jeœli dodanie pionka powiod³o siê lub false jeœli nie.
	*/
	bool addToTile(Counter* c);
	/** Usuwa wszystkie pionki danego gracza z pola. UWAGA: Nie aktualizuje to ostatnio zbitych pionków!.
	* @param playerId - Identyfikator gracza, którego pionki nale¿y usun¹æ.
	*/
	void removePlayerCounters(const unsigned int playerId);
	/** @return Wektor z pionkami stoj¹cymi na polu. */
	std::vector<Counter*>& getCounters() { return counters; }

	/** Przenosi pionek gracza na inne pole.
	* @param to - Docelowe pole, na którym ma siê znaleŸæ pionek.
	* @param whose - Gracz, którego pionek przenieœæ.
	* @return true jeœli uda³o siê przenieœæ pionek lub false w przeciwnym wypadku.
	*/
	bool movePlayerCounter(Tile& to, Player& whose);
	/** U¿ywane do zmapowania pionków do GUI.
	* @return Mapa z identyfikatorami graczy i iloœci¹ pionków dla ka¿dego z nich.
	*/
	std::map<unsigned int, int>getPlayersCount();

	/**
	* @return Czy pionek gracza stoi na danym polu.
	*/
	bool hasCounter(Player& player);
	/**
	* Operator przypisania.
	* @param t - Pole, którego wartoœæ ma byæ przypisana naszemu polu.
	* @return Referencja bo *this.
	*/
	Tile& operator=(const Tile& t);

	friend std::ostream& operator<< (std::ostream& os, const Tile& t);
	/**
	* Zwraca reprezentacjê obiektu w bardziej czytelnej postaci
	*/
	std::string str();
	/**
	* Zwraca obiekt w postaci tekstu JSON.
	*/
	std::string json();
};

