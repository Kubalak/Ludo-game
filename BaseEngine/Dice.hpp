#pragma once
#include <random>
#include <iostream>

/** Klasa do obs³ugi kostki.
* @author Jakub Jach &copy; 2022
*/
class Dice {
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;
	unsigned int lastRes;
public:
	/**
	* Domyœlny konstruktor. U¿ywa ziarna time(NULL);
	*/
	Dice();
	/** Konstruktor z ziarnem dla generatora.
	* @param seed Ziarno generatora.
	*/
	Dice(unsigned int seed);
	/** Metoda do rzutu kostk¹.
	* @return Liczba oczek od 1 do 6.
	*/
	unsigned int roll();
	/**
	* @return Wynik ostatniego rzutu.
	*/
	const unsigned int getLast() { return lastRes; }

	/** Pozwala ustawiæ wartoœæ kostki. U¿ywane do silnika online.
	* @param value - Wartoœæ jaka ma byæ nadana kostce.
	* @return true w przypadku powodzenia lub false w przypadku podania b³êdnej wartoœci.
	*/
	bool setLast(unsigned int);
	/**
	* Umo¿liwia przekierowanie do strumienia.
	* @param os Strumieñ wyjœciowy
	* @param dice Kostka, której wartoœæ ma zostac przekierowana do strumienia.
	* @return Strumieñ os.
	*/
	friend std::ostream& operator<<(std::ostream& os, const Dice& dice);
};