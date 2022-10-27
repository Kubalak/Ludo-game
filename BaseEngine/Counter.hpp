#pragma once
#ifdef _DEBUG
	#include <iostream>
	#include <iomanip>
#endif
class Counter
{
	const unsigned int ownedBy;
	const unsigned int id;

public:
	// Domyœlny konstruktor pionka
	Counter(unsigned int ownedBy, unsigned int id) :
		ownedBy(ownedBy),
		id(id) {
	}
	// @return Identyfikator pionka.
	const unsigned int getId() { return id; }
	// @return W³aœciciel pionka.
	const unsigned int getOwner() { return ownedBy; }

#ifdef _DEBUG
	friend std::ostream& operator<< (std::ostream& os,const Counter& e);
#endif
};



