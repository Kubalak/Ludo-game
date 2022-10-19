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
	for (Counter* c : player->getContainer().all)
		std::cout << c->id << ' ';
	std::cout << '\n';
	
	delete player;
#ifdef _DEBUG
	system("pause");
#endif
	return 0;
}