/*

Plik wykorzystywany do testów silnika gry.

////////////     ////////////       ////////////
///      ///     ///      ///       ///      ///
///      ///     ///      ///       ///      
////////////     ///      ///       ///
///              ///      ///       ///   //////
///              ///      ///       ///      ///
///              ////////////       ////////////

@author Jakub Jach &copy; 2022
*/


#include <iostream>
#include "Engine.hpp"


int main(int argc, char** argv) {
	Engine* engine = new Engine();
	std::cout << engine->addPlayer(new Player("Adam"),1) << ' ';
	std::cout << engine->addPlayer(new Player("Ewa",1), 3) << '\n';
	engine->start();
	//std::cout << *engine << '\n';
	//std::cout << engine->getCurrentPlayer().getNick() << ' ' << engine->getCurrentPlayer().getId() << '\n';
	//engine->step();
	//std::cout << engine->getCurrentPlayer().getNick() << ' ' << engine->getCurrentPlayer().getId() << '\n';
	//engine->step();
	//std::cout << engine->getCurrentPlayer().getNick() << ' ' << engine->getCurrentPlayer().getId() << '\n';
	//
	//std::cout << engine->rollDice() << ' ' << engine->rollDice() << ' ' << engine->rollDice() << ' ' << engine->rollDice() << ' ' << engine->rollDice() << '\n';
	
	//Jeszcze nie dzia³a
	//engine->start();
	int decision, field;
	while (!engine->finished()) {
		std::cout << "Is dice rolled: " << engine->isDiceRolled() << '\n';
		std::cout << "Is move made: " << engine->isMoveMade() << '\n';
		std::cout << "Dice roll: " << engine->rollDice() << '\n';
		std::cout << "Current player: " << engine->getCurrentPlayer().getNick() << "\nDecision: ";
		std::cin >> field;
		std::cout << "Move: " << engine->move(field) << ' ';
		std::cout << "Step: " << engine->step() << "\n\n";
		for (auto p : engine->getTiles())
			std::cout << p << '\n';
	}
#ifdef _DEBUG
	system("pause");
#endif

	delete engine;
	return 0;
}