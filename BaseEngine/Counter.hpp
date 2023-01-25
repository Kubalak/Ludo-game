#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

/** Klasa pionka.
* @author Jakub Jach &copy; 2023
*/
class Counter
{
	/**
	* W³aœciciel pionka (ID Gracza).
	* Referencja zapewnia spójnoœæ na wypadek zmiany ID w³aœciciela.
	*/
	unsigned int& ownedBy;
	/**
	* Identyfikator pionka (nr).
	*/
	const unsigned int id;

public:
	/** Domyœlny konstruktor pionka
	* @param ownedBy - W³aœciciel pionka.
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
	* @return W³aœciciel pionka.
	*/
	const unsigned int getOwner() { return ownedBy; }

	/**
	* Umo¿liwia przekierowanie do strumienia.
	* Wyjœcie w postaci takiej jak metoda json()
	* @param os Strumieñ wyjœciowy
	* @param e Obiekt Counter, który ma zostaæ przekierowany do strumienia.
	* @return Strumieñ os.
	*/
	friend std::ostream& operator<< (std::ostream& os, const Counter& e);
	/**
	* Zwraca reprezentacjê obiektu w bardziej czytelnej postaci.
	* @return Reprezentacja obiektu jako std::string.
	*/
	std::string str();
	/**
	* Zwraca obiekt w postaci tekstu JSON.
	* @return Reprezentacja obiektu w postaci JSON.
	*/
	std::string json();
};



