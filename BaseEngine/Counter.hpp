#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

/** Klasa pionka.
* @author Jakub Jach &copy; 2022
*/
class Counter
{
	/**
	* W�a�ciciel pionka (ID Gracza).
	* Referencja zapewnia sp�jno�� na wypadek zmiany ID w�a�ciciela.
	*/
	unsigned int& ownedBy;
	/**
	* Identyfikator pionka (nr).
	*/
	const unsigned int id;

public:
	/** Domy�lny konstruktor pionka
	* @param ownedBy - W�a�ciciel pionka.
	* @param id - Identyfikator (nr) pionka.
	*/
	Counter(unsigned int& ownedBy, unsigned int id) :
		ownedBy(ownedBy),
		id(id) {
	}
	/**
	* @return Identyfikator pionka.
	*/
	const unsigned int getId() noexcept { return id; }
	/**
	* @return W�a�ciciel pionka.
	*/
	const unsigned int getOwner() { return ownedBy; }

	/**
	* Umo�liwia przekierowanie do strumienia.
	*/
	friend std::ostream& operator<< (std::ostream& os, const Counter& e);
	/**
		* Zwraca reprezentacj� obiektu w bardziej czytelnej postaci
		*/
	std::string str();
	/**
	* Zwraca obiekt w postaci tekstu JSON.
	*/
	std::string json();
};



