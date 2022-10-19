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
#include "Player.hpp"


int main(int argc, char** argv) {
	Player* player = new Player("Player");
	std::cout << player->getNick() << '\n';
	Counter& c = player->getContainer().getCounter(0);
	std::cout << c.getId() << '\n';
	
	delete player;
#ifdef _DEBUG
	system("pause");
#endif
	return 0;
}