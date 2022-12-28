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
#include "OnlineEngine.hpp"
#include "OnlineServer.hpp"


int main(int argc, char** argv) {

	/*OnlineEngine e;
	e.start();*/

	Engine* engine = new Engine();
	engine->addPlayer(new Player("Adam"), 1);
	engine->addPlayer(new Player("Ewa"), 3);
	std::cout << *engine << '\n';
	engine->start();
	std::cout << engine->getCurrentPlayer().json() << '\n';
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
		std::cout << "Adam container\n[";
		for (auto c : engine->getLast(1))
			std::cout << c << ' ';
		std::cout << "]\n";

		std::cout << "Ewa container\n[";
		for (auto c : engine->getLast(3))
			std::cout << c << ' ';
		std::cout << "]\n";
		 
		std::cout << "Current player: " << engine->getCurrentPlayer().getNick() << "\nPole: ";
		std::cin >> field;
		std::cout << "Move: " << engine->move(field) << ' ';
		std::cout << "Step: " << engine->step() << "\n\n";
		int index = 0;
		for (auto& p : engine->getTiles())
			std::cout << '['<< index++ << "]: " << p << '\n';
	 }
	//OnlineEngine engine;
	//std::cout << "Add player: " << engine.addPlayer(new Player("Ewa"), 1) << '\n';
	//std::cout << "Connect: " << engine.connect("tcp://127.0.0.1:2000", "tcp://127.0.0.1:3000") << '\n';
	//OnlineServer engine;
	//auto n = engine.bind("tcp://127.0.0.1:3000", "tcp://127.0.0.1:2000");
	//std::cout << "Bind: " << n << '\n';
	//engine.start();
#ifdef _DEBUG
	system("pause");
#endif

    // delete engine;
	return 0;
}