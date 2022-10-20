#pragma once
class Counter
{
	const unsigned int ownedBy;
	const unsigned int id;
	unsigned int movesNo;

public:
	// Domyœlny konstruktor pionka
	Counter(unsigned int ownedBy, unsigned int id) :
		ownedBy(ownedBy),
		id(id),
		movesNo(0) {
	}
	// @return Identyfikator pionka.
	const unsigned int getId() { return id; }
	// @return W³aœciciel pionka.
	const unsigned int getOwner() { return ownedBy; }
	// @return Liczba ruchów pionka od punktu startu.
	const unsigned int getMoves() { return movesNo; }

	/* Funkcja do zmiany licznika po³o¿enia pionka.
	* @param moves - Liczba, o któr¹ nale¿y zmieniæ aktualn¹ pozycjê.
	*/
	void move(int moves);

};

