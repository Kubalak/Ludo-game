#pragma once
class Counter
{
	const unsigned int ownedBy;
	const unsigned int id;
	unsigned int movesNo;

public:
	// Domy�lny konstruktor pionka
	Counter(unsigned int ownedBy, unsigned int id) :
		ownedBy(ownedBy),
		id(id),
		movesNo(0) {
	}
	// @return Identyfikator pionka.
	const unsigned int getId() { return id; }
	// @return W�a�ciciel pionka.
	const unsigned int getOwner() { return ownedBy; }
	// @return Liczba ruch�w pionka od punktu startu.
	const unsigned int getMoves() { return movesNo; }

	/* Funkcja do zmiany licznika po�o�enia pionka.
	* @param moves - Liczba, o kt�r� nale�y zmieni� aktualn� pozycj�.
	*/
	void move(int moves);

};

