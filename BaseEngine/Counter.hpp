#pragma once
#ifdef _DEBUG
	#include <iostream>
	#include <iomanip>
#endif
/** Klasa pionka. 
* @author Jakub Jach &copy; 2022 
*/
class Counter
{
	/**
	* Właściciel pionka (ID Gracza).
	*/
	const unsigned int ownedBy;
	/**
	* Identyfikator pionka (nr).
	*/
	const unsigned int id;

public:
	/** Domyślny konstruktor pionka
	* @param ownedBy - Właściciel pionka.
	* @param id - Identyfikator (nr) pionka.
	*/
	Counter(unsigned int ownedBy, unsigned int id) :
		ownedBy(ownedBy),
		id(id) {
	}
	/**
	* @return Identyfikator pionka. 
	*/
	const unsigned int getId() { return id; }
	/**
	* @return Właściciel pionka.
	*/
	const unsigned int getOwner() { return ownedBy; }

#ifdef _DEBUG
	/**
	* Umożliwia przekierowanie do strumienia.
	*/
	friend std::ostream& operator<< (std::ostream& os,const Counter& e);
#endif
};



