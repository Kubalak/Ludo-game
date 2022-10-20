#pragma once
#include <array>
#include <vector>
#include "Counter.hpp"

// Klasa do przechowywania informacji o pionkach poza g³ówn¹ czêœci¹ planszy.
class CounterContainer
{
	// Wskazuje w³aœciciela zasobnika z pionkami.
	const unsigned int ownedBy;
	
	// Zawiera wszystkie pionki gracza.
	std::array <Counter*, 4> all;
	// Zasobnik na pionki.
	std::vector<Counter*> holder;
	// Wskazuje na ostatnie pola na planszy.
	std::array <std::vector<Counter*>, 6> last;
public:
	/* Konstruktor
	* @param ownedBy - Identyfikator gracza, do którego nale¿y obiekt.
	*/
	CounterContainer(const unsigned int ownedBy);
	
	/* Zwraca wektor z pionkami na danym polu. Potrzebne do wyœwietlenia pionków w polach na koñcu.
	* @param fieldNo - Numer pola od 0 do 5.
	* @return Referencja do wektora z pionkami na danym polu.
	*/
	const std::vector<Counter*>& getCountersVector(unsigned int fieldNo) { return last[fieldNo]; }
	
	/* Przesuwa wybrany pionek do koñcówki planszy.
	* Je¿eli pionek ju¿ znajduje siê na liœcie, wówczas przeliczane jest jego nowe po³o¿enie.
	* @param counterId - Identyfikator pionka.
	* @param offset - Przesuniêcie pionka wzglêdem pocz¹tku. Np. wylosowanie 5 oczek 3 miejsca przed pocz¹tkiem pól koñcowych daje offset wynosz¹cy 2.
	* @return Czy operacja siê powiod³a (false jeœli pionka nie ma w liœcie last)
	*/
	bool moveToLast(unsigned int counterId, unsigned int offset);

	/* Dodaje wybrany pionek do koñcówki planszy.
	* @param c - WskaŸnik na pionek.
	* @param offset - O ile ma byæ przesuniêty wzglêdem pocz¹tku.
	* @return True jeœli dodawanie siê uda³o, false jeœli pionek znajduje siê ju¿ na liœcie.
	*/
	bool addToLast(Counter* c, unsigned int offset);
	
	/* Dodaje pionek do zasobnika na pionki.
	* @param c - Pionek do dodania.
	* @return True w przypadku powodzenia lub false, jeœli pionek ju¿ dodano, nie nale¿y do gracza lub znajduje siê nim maksymalna liczba pionków.
	*/
	bool addToHolder(Counter* c);

	Counter* holderPop();
	~CounterContainer();

};
/* Zwraca referencjê do pionka o podanym id
	* @param counterId - Identyfikator pionka od 0 do 3.
	* @return Referencja do wybranego pionka
	*/
