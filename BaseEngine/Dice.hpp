#pragma once

// Klasa do obs�ugi kostki.
class Dice {
	unsigned int lastRes;
public:
	Dice();
	/* Metoda do rzutu kostk�.
	* @return Liczba oczek od 1 do 6.
	*/
	unsigned int roll();
	const unsigned int getLast() { return lastRes; }
};