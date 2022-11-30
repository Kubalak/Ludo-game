/**

Plik wykorzystywany do testów silnika gry.

@author Jakub Jach &copy; 2022
*/

////////////     ////////////       ////////////
///      ///     ///      ///       ///      ///
///      ///     ///      ///       ///      
////////////     ///      ///       ///
///              ///      ///       ///   //////
///              ///      ///       ///      ///
///              ////////////       ////////////


#include <iostream>
#include "Engine.hpp"


int main(int argc, char** argv) {
	Engine* engine = new Engine();
	std::cout << engine->addPlayer(new Player("Adam"),1) << ' ';
	std::cout << engine->addPlayer(new Player("Ewa"), 3) << '\n';
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
	int field;
	while (!engine->finished()) {
		std::cout << "Dice roll: " << engine->rollDice() << '\n';
		std::cout << "Current state: " << Engine::stateToStr(engine->getCurrentState()) << "\n";
		std::cout << "Current player: " << engine->getCurrentPlayer().getNick() << "\nPole: ";
		std::cin >> field;
		std::cout << "Move: " << engine->move(field) << ' ';
		std::cout << "Step: " << engine->step() << "\n\n";
		int index = 0;
		for (auto& p : engine->getTiles())
			std::cout << '['<< index++ << "]: " << p << '\n';
	}
#ifdef _DEBUG
	system("pause");
#endif

	delete engine;
	return 0;
}