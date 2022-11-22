#pragma once
#ifdef _DEBUG
	#include <iostream>
	#include <iomanip>
#endif
/** Klasa pionka. */
class Counter
{
	/**
	* W³aœciciel pionka (ID Gracza).
	*/
	const unsigned int ownedBy;
	/**
	* Identyfikator pionka (nr).
	*/
	const unsigned int id;

public:
	/** Domyœlny konstruktor pionka
	* @param ownedBy - W³aœciciel pionka.
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
	* @return W³aœciciel pionka.
	*/
	const unsigned int getOwner() { return ownedBy; }

#ifdef _DEBUG
	/**
	* Umo¿liwia przekierowanie do strumienia.
	*/
	friend std::ostream& operator<< (std::ostream& os,const Counter& e);
#endif
};



