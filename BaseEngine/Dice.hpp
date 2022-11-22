#pragma once
#include <random>

/** Klasa do obs³ugi kostki. */
class Dice {
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;
	unsigned int lastRes;
public:
	Dice();
	/** Metoda do rzutu kostk¹.
	* @return Liczba oczek od 1 do 6.
	*/
	unsigned int roll();
	/**
	* @return Wynik ostatniego rzutu.
	*/
	const unsigned int getLast() { return lastRes; }
};