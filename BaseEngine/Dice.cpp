#include "Dice.hpp"
#include <ctime>

Dice::Dice():
	distribution(std::uniform_int_distribution<int>(1, 6)) {
	generator.seed(static_cast<unsigned int>(time(NULL)));
	lastRes = distribution(generator);	
}

Dice::Dice(unsigned int seed):
	distribution(std::uniform_int_distribution<int>(1, 6)) {
	generator.seed(seed);
	lastRes = distribution(generator);
}

unsigned int Dice::roll() {
	lastRes = distribution(generator);
	return lastRes;
}

bool Dice::setLast(unsigned int value) {
	if (!value || value > 6)
		return false;
	lastRes = value;
	return true;
}