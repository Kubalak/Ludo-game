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
	* @param p - WskaŸnik na gracza, dla którego tworzony jest obiekt.
	* @param startPos - Pozycja pocz¹tkowa na planszy.
	*/
	PlayerContainer(Player* p, unsigned int startPos);
	~PlayerContainer();
	/* Usuwa jeden pionek z zasobnika na pionki.
	* @return WskaŸnik na pionek lub nullptr jeœli pusty.
	*/
	Counter* holderPop();
	/* Pozwala na dodanie pionka do zasobnika na pionki.
	* @param c - WskaŸnik na pionek do dodania.
	* @return true jeœli dodanie zakoñczy siê powodzeniem lub false jeœli pionek znajduje siê w zasobniku.
	*/
	bool addToHolder(Counter* c);
	/* Pozwala na dodanie pionka do 6 ostatnich pól na planszy.
	* @param c - WskaŸnik na pionek do dodania.
	* @param offset - Przesuniêcie wzglêdem pocz¹tku (domyœlnie 0).
	* @return true jeœli dodanie siê powiedzie lub false jeœli pionek znajduje siê ju¿ na wybranym polu.
	*/
	bool addToLast(Counter* c, unsigned int offset = 0);
	/* Przesuwa pionek na wybranym polu o wskazan¹ liczbê pól.
	* @param fieldNo - Nr pola, z którego nale¿y przenieœæ pionek.
	* @param offset - Liczba pól, o któr¹ przenoszony jest pionek.
	*/
	bool moveOnLast(unsigned int fieldNo, unsigned int offset);
	/*
	* @return Liczba pionków w zasobniku.
	*/
	unsigned int holderCount() { return holder.size(); }
	/*
	* @param fieldNo - Nr pola, z którego ma pobraæ iloœæ pionków.
	* @return Liczba pionków na polu podanym w parametrze.
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
	* @return Informacja czy gracz zakoñczy³ rozgrywkê.
	*/
	bool allIn();
	/* Zwraca informacjê czy gracz mo¿e siê poruszaæ po planszy.
	* @return Informacja czy pionek znajduje siê na planszy i nie na koñcu.
	*/
	bool canMove() { return holder.size() < 4 && last.size() != 4; }

#ifdef _DEBUG
	friend std::ostream& operator<< (std::ostream& os, const PlayerContainer& e);
#endif

};


