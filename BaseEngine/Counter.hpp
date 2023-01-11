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
	* Właściciel pionka (ID Gracza).
	* Referencja zapewnia spójność na wypadek zmiany ID właściciela.
	*/
	unsigned int& ownedBy;
	/**
	* Identyfikator pionka (nr).
	*/
	const unsigned int id;

public:
	/** Domyślny konstruktor pionka
	* @param ownedBy - Właściciel pionka.
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
	* @return Właściciel pionka.
	*/
	const unsigned int getOwner() { return ownedBy; }

	/**
	* Umożliwia przekierowanie do strumienia.
	*/
	friend std::ostream& operator<< (std::ostream& os, const Counter& e);
	/**
		* Zwraca reprezentację obiektu w bardziej czytelnej postaci
		*/
	std::string str();
	/**
	* Zwraca obiekt w postaci tekstu JSON.
	*/
	std::string json();
};



