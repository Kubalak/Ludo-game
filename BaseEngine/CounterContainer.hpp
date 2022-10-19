#pragma once
#include <array>
#include <vector>
#include "Counter.hpp"

// Klasa do przechowywania informacji o pionkach poza g��wn� cz�ci� planszy.
class CounterContainer
{
	// Wskazuje w�a�ciciela zasobnika z pionkami.
	const unsigned int ownedBy;
	// Wskazuje na 4 ostatnie pola na planszy.
	std::array <std::vector<Counter*>, 4> last;
	// Zawiera wszystkie pionki gracza.
	std::array <Counter*, 4> all;
	// Zasobnik na pionki.
	std::vector<Counter*> holder;
public:
	/* Konstruktor
	* @param ownedBy - Identyfikator gracza, do kt�rego nale�y obiekt.
	*/
	CounterContainer(const unsigned int ownedBy);
	/* Zwraca referencj� do pionka o podanym id
	* @param counterId - Identyfikator pionka od 0 do 3.
	* @return Referencja do wybranego pionka
	*/
	Counter& getCounter(unsigned int counterId);
	/* Przesuwa wybrany pionek do ko�c�wki planszy.
	* Je�eli pionek ju� znajduje si� na li�cie, w�wczas przeliczany jest jego nowe po�o�enie.
	* @param counterId - Identyfikator pionka.
	* @param offset - Przesuni�cie pionka wzgl�dem pocz�tku. Np. wylosowanie 5 oczek 3 miejsca przed pocz�tkiem p�l ko�cowych daje offset wynosz�cy 2.
	* @return Ilo�� p�l, o kt�re musi cofn�� si� pionek na planszy.
	*/
	unsigned int moveToLast(unsigned int counterId, unsigned int offset);
	
	/* Dodaje pionek do zasobnika na pionki.
	* @param c - Pionek do dodania.
	* @return True w przypadku powodzenia lub false, je�li pionek ju� dodano, nie nale�y do gracza lub znajduje si� nim maksymalna liczba pionk�w.
	*/
	bool addToHolder(Counter* c);
	~CounterContainer();

};

