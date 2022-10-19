#include "Dice.hpp"
#include <random>
#include <ctime>


Dice::Dice() {
	srand(time(NULL));
}
unsigned int Dice::roll() {
	return 1 + rand() % 6;
}