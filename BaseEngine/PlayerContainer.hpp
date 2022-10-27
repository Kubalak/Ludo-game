#pragma once
#include <vector>
#include "Player.hpp"

class PlayerContainer
{
	Player* player;
	unsigned int startPos;
	std::array<std::vector<Counter*>, 6>last;
	std::vector<Counter*> holder;
public:
	/*
	* @param p - Wska�nik na gracza, dla kt�rego tworzony jest obiekt.
	* @param startPos - Pozycja pocz�tkowa na planszy.
	*/
	PlayerContainer(Player* p, unsigned int startPos);
	~PlayerContainer();
	/* Usuwa jeden pionek z zasobnika na pionki.
	* @return Wska�nik na pionek lub nullptr je�li pusty.
	*/
	Counter* holderPop();
	/* Pozwala na dodanie pionka do zasobnika na pionki.
	* @param c - Wska�nik na pionek do dodania.
	* @return true je�li dodanie zako�czy si� powodzeniem lub false je�li pionek znajduje si� w zasobniku.
	*/
	bool addToHolder(Counter* c);
	/* Pozwala na dodanie pionka do 6 ostatnich p�l na planszy.
	* @param c - Wska�nik na pionek do dodania.
	* @param offset - Przesuni�cie wzgl�dem pocz�tku (domy�lnie 0).
	* @return true je�li dodanie si� powiedzie lub false je�li pionek znajduje si� ju� na wybranym polu.
	*/
	bool addToLast(Counter* c, unsigned int offset = 0);
	/* Przesuwa pionek na wybranym polu o wskazan� liczb� p�l.
	* @param fieldNo - Nr pola, z kt�rego nale�y przenie�� pionek.
	* @param offset - Liczba p�l, o kt�r� przenoszony jest pionek.
	*/
	bool moveOnLast(unsigned int fieldNo, unsigned int offset);
	/*
	* @return Liczba pionk�w w zasobniku.
	*/
	unsigned int holderCount() { return holder.size(); }
	/*
	* @param fieldNo - Nr pola, z kt�rego ma pobra� ilo�� pionk�w.
	* @return Liczba pionk�w na polu podanym w parametrze.
	*/
	unsigned int lastCount(unsigned int fieldNo);
	/*
	* @return Referencja do gracza.
	*/
	Player& getPlayer() { return *player; }
	/*
	* @return Pozycja startowa na planszy.
	*/
	unsigned int getStartPos() { return startPos; }
	/*
	* @return Informacja czy gracz zako�czy� rozgrywk�.
	*/
	bool allIn();
	/* Zwraca informacj� czy gracz mo�e si� porusza� po planszy.
	* @return Informacja czy pionek znajduje si� na planszy i nie na ko�cu.
	*/
	bool canMove() { return holder.size() < 4 && last.size() != 4; }

#ifdef _DEBUG
	friend std::ostream& operator<< (std::ostream& os, const PlayerContainer& e);
#endif

};


