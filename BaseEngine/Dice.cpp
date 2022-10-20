#include "Dice.hpp"
#include <random>
#include <ctime>


Dice::Dice() {
	srand(time(NULL));
	lastRes = 1 + rand() % 6;
}
unsigned int Dice::roll() {
	lastRes = 1 + rand() % 6;
	return lastRes;
}