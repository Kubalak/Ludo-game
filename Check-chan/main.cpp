#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include "Game.h"
#include <thread>

//#include "Player.hpp"

//int main(int argc, char** argv, char** env) {
//	try {
//		std::ifstream f("sample.json");
//		nlohmann::json data = nlohmann::json::parse(f);
//		std::cout << data["quiz"]["sport"]["q1"]["question"] << '\n'; // Which one is correct team name in NBA?
//	}
//	catch (std::exception& e) {
//		std::cerr << e.what() << '\n';
//		return 1;
//	}
//#ifdef _DEBUG 
//	system("pause"); // Stop konsole before program exits.
//#endif
//	return 0;
//}
bool engineStop;

void doEngine(Engine* engine) {
	engine->addPlayer(new Player("Adam"), 1);
	engine->addPlayer(new Player("Ewa"), 3);
	engine->start();
	int field;
	while (!engine->finished() && !engineStop) {
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
			std::cout << '[' << index++ << "]: " << p << '\n';
	}
}

int main()
{
	Engine engine;
    Game myGame(engine);
	std::thread a(doEngine, &engine);
	myGame.run();
	a.join();
    return 0;
}