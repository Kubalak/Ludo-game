#include "Dice.hpp"


Dice::Dice() {
	distribution = std::uniform_int_distribution<int>(1, 6);
	lastRes = distribution(generator);
}
unsigned int Dice::roll() {
	lastRes = distribution(generator);
	return lastRes;
}