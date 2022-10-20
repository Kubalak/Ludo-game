#pragma once
#include <array>
#include <vector>
#include "Counter.hpp"

// Klasa do przechowywania informacji o pionkach poza g��wn� cz�ci� planszy.
class CounterContainer
{
	// Wskazuje w�a�ciciela zasobnika z pionkami.
	const unsigned int ownedBy;
	
	// Zawiera wszystkie pionki gracza.
	std::array <Counter*, 4> all;
	// Zasobnik na pionki.
	std::vector<Counter*> holder;
	// Wskazuje na ostatnie pola na planszy.
	std::array <std::vector<Counter*>, 6> last;
public:
	/* Konstruktor
	* @param ownedBy - Identyfikator gracza, do kt�rego nale�y obiekt.
	*/
	CounterContainer(const unsigned int ownedBy);
	
	/* Zwraca wektor z pionkami na danym polu. Potrzebne do wy�wietlenia pionk�w w polach na ko�cu.
	* @param fieldNo - Numer pola od 0 do 5.
	* @return Referencja do wektora z pionkami na danym polu.
	*/
	const std::vector<Counter*>& getCountersVector(unsigned int fieldNo) { return last[fieldNo]; }
	
	/* Przesuwa wybrany pionek do ko�c�wki planszy.
	* Je�eli pionek ju� znajduje si� na li�cie, w�wczas przeliczane jest jego nowe po�o�enie.
	* @param counterId - Identyfikator pionka.
	* @param offset - Przesuni�cie pionka wzgl�dem pocz�tku. Np. wylosowanie 5 oczek 3 miejsca przed pocz�tkiem p�l ko�cowych daje offset wynosz�cy 2.
	* @return Czy operacja si� powiod�a (false je�li pionka nie ma w li�cie last)
	*/
	bool moveToLast(unsigned int counterId, unsigned int offset);

	/* Dodaje wybrany pionek do ko�c�wki planszy.
	* @param c - Wska�nik na pionek.
	* @param offset - O ile ma by� przesuni�ty wzgl�dem pocz�tku.
	* @return True je�li dodawanie si� uda�o, false je�li pionek znajduje si� ju� na li�cie.
	*/
	bool addToLast(Counter* c, unsigned int offset);
	
	/* Dodaje pionek do zasobnika na pionki.
	* @param c - Pionek do dodania.
	* @return True w przypadku powodzenia lub false, je�li pionek ju� dodano, nie nale�y do gracza lub znajduje si� nim maksymalna liczba pionk�w.
	*/
	bool addToHolder(Counter* c);

	Counter* holderPop();
	~CounterContainer();

};
/* Zwraca referencj� do pionka o podanym id
	* @param counterId - Identyfikator pionka od 0 do 3.
	* @return Referencja do wybranego pionka
	*/
