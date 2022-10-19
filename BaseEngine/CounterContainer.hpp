#pragma once
#include <array>
#include <vector>
#include "Counter.hpp"

// Klasa do przechowywania informacji o pionkach poza g³ówn¹ czêœci¹ planszy.
class CounterContainer
{
	// Wskazuje w³aœciciela zasobnika z pionkami.
	const unsigned int ownedBy;
	// Wskazuje na 4 ostatnie pola na planszy.
	std::array <std::vector<Counter*>, 4> last;
	// Zawiera wszystkie pionki gracza.
	std::array <Counter*, 4> all;
	// Zasobnik na pionki.
	std::vector<Counter*> holder;
public:
	/* Konstruktor
	* @param ownedBy - Identyfikator gracza, do którego nale¿y obiekt.
	*/
	CounterContainer(const unsigned int ownedBy);
	/* Zwraca referencjê do pionka o podanym id
	* @param counterId - Identyfikator pionka od 0 do 3.
	* @return Referencja do wybranego pionka
	*/
	Counter& getCounter(unsigned int counterId);
	/* Przesuwa wybrany pionek do koñcówki planszy.
	* Je¿eli pionek ju¿ znajduje siê na liœcie, wówczas przeliczany jest jego nowe po³o¿enie.
	* @param counterId - Identyfikator pionka.
	* @param offset - Przesuniêcie pionka wzglêdem pocz¹tku. Np. wylosowanie 5 oczek 3 miejsca przed pocz¹tkiem pól koñcowych daje offset wynosz¹cy 2.
	* @return Iloœæ pól, o które musi cofn¹æ siê pionek na planszy.
	*/
	unsigned int moveToLast(unsigned int counterId, unsigned int offset);
	
	/* Dodaje pionek do zasobnika na pionki.
	* @param c - Pionek do dodania.
	* @return True w przypadku powodzenia lub false, jeœli pionek ju¿ dodano, nie nale¿y do gracza lub znajduje siê nim maksymalna liczba pionków.
	*/
	bool addToHolder(Counter* c);
	~CounterContainer();

};

