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
	engine->addPlayer(new Player("Nickname"));
	engine->start();
	std::cout << engine->getCurrentPlayer().getNick() << '\n';
	
	delete engine;
	
	
#ifdef _DEBUG
	system("pause");
#endif
	return 0;
}