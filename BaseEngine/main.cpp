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
	std::cout << std::boolalpha << engine->addPlayer(new Player("Adam"),1) << ' ';
	std::cout << std::boolalpha << engine->addPlayer(new Player("Ewa",1), 3) << '\n';
	engine->start();
	std::cout << engine->getCurrentPlayer().getNick() << ' ' << engine->getCurrentPlayer().getId() << '\n';
	engine->step();
	std::cout << engine->getCurrentPlayer().getNick() << ' ' << engine->getCurrentPlayer().getId() << '\n';
	engine->step();
	std::cout << engine->getCurrentPlayer().getNick() << ' ' << engine->getCurrentPlayer().getId() << '\n';
	
	std::cout << engine->rollDice() << ' ' << engine->rollDice() << ' ' << engine->rollDice() << ' ' << engine->rollDice() << ' ' << engine->rollDice() << '\n';
	/*
	* Jeszcze nie dzia³a
	engine->start();
	while (!engine->finished()) {
		engine->step();
		Player& player = engine->getCurrentPlayer();
		engine->move(player, 0);
	}*/

	delete engine;
	
	
#ifdef _DEBUG
	system("pause");
#endif
	return 0;
}