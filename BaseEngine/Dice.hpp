#pragma once
#include <random>

/** Klasa do obs�ugi kostki. 
* @author Jakub Jach &copy; 2022 
*/
class Dice {
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;
	unsigned int lastRes;
public:
	/**
	* Domy�lny konstruktor. U�ywa ziarna time(NULL);
	*/
	Dice();
	/** Konstruktor z ziarnem dla generatora.
	* @param seed Ziarno generatora.
	*/
	Dice(unsigned int seed);
	/** Metoda do rzutu kostk�.
	* @return Liczba oczek od 1 do 6.
	*/
	unsigned int roll();
	/**
	* @return Wynik ostatniego rzutu.
	*/
	const unsigned int getLast() { return lastRes; }
};