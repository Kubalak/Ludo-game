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
#include <chrono>
#include <fstream>
#include "Engine.hpp"
#include "OnlineEngine.hpp"
#include "OnlineServer.hpp"
#include "EventMsg.hpp"


int main(int argc, char** argv) {

	/*OnlineEngine e;
	e.start();*/

	//Engine* engine = new Engine();
	//engine->addPlayer(new Player("Adam"), 1);
	//engine->addPlayer(new Player("Ewa"), 3);
	//std::cout << *engine << '\n';
	//engine->start();
	//std::cout << engine->getCurrentPlayer().json() << '\n';
	////std::cout << *engine << '\n';
	////std::cout << engine->getCurrentPlayer().getNick() << ' ' << engine->getCurrentPlayer().getId() << '\n';
	////engine->step();
	////std::cout << engine->getCurrentPlayer().getNick() << ' ' << engine->getCurrentPlayer().getId() << '\n';
	////engine->step();
	////std::cout << engine->getCurrentPlayer().getNick() << ' ' << engine->getCurrentPlayer().getId() << '\n';
	////
	////std::cout << engine->rollDice() << ' ' << engine->rollDice() << ' ' << engine->rollDice() << ' ' << engine->rollDice() << ' ' << engine->rollDice() << '\n';
	//
	////Jeszcze nie dzia³a
	////engine->start();
	//int field;
	//while (!engine->finished()) {
	//	std::cout << "Dice roll: " << engine->rollDice() << '\n';
	//	std::cout << "Current state: " << Engine::stateToStr(engine->getCurrentState()) << "\n";
	//	std::cout << "Adam container\n[";
	//	for (auto c : engine->getLast(1))
	//		std::cout << c << ' ';
	//	std::cout << "]\n";

	//	std::cout << "Ewa container\n[";
	//	for (auto c : engine->getLast(3))
	//		std::cout << c << ' ';
	//	std::cout << "]\n";
	//	 
	//	std::cout << "Current player: " << engine->getCurrentPlayer().getNick() << "\nPole: ";
	//	std::cin >> field;
	//	std::cout << "Move: " << engine->move(field) << ' ';
	//	std::cout << "Step: " << engine->step() << "\n\n";
	//	int index = 0;
	//	for (auto& p : engine->getTiles())
	//		std::cout << '['<< index++ << "]: " << p << '\n';
	// }
	//OnlineEngine engine;
	//std::cout << "Add player: " << engine.addPlayer(new Player("Ewa"), 1) << '\n';
	//std::cout << "Connect: " << engine.connect("tcp://127.0.0.1:2000", "tcp://127.0.0.1:3000") << '\n';
	//OnlineServer engine;
	//auto n = engine.bind("tcp://127.0.0.1:3000", "tcp://127.0.0.1:2000");
	//std::cout << "Bind: " << n << '\n';
	//engine.start();
	try {
		//Player* p = new Player("{\"id\":235, \"nick\":\"Arnold\"}"_json);
		std::ifstream f("tmp.json");
		auto start = std::chrono::high_resolution_clock::now();
		nlohmann::json js = nlohmann::json::parse(f);
		Engine e(js);
		auto stop = std::chrono::high_resolution_clock::now();
		std::cout << "Ladowanie z JSON zajelo: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()/1000.0 << " ms\n";
		start = std::chrono::high_resolution_clock::now();
		std::string s = e.json();
		stop = std::chrono::high_resolution_clock::now();
		std::cout << "Zrzut do JSON zajal: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()/1000.0 << " ms\n";
		std::cout << s << '\n';
		f.close();
		//PlayerContainer c("{\"startPos\":1,\"playerObj\":{\"nick\":\"Arnold\",\"id\":235},\"holder\":[{\"id\":0,\"ownedBy\":235},{\"id\":1,\"ownedBy\":235}],\"last\":[[],[],[],[{\"id\":3,\"ownedBy\":235},{\"id\":2,\"ownedBy\":235}],[],[]]}"_json);
		//c.addToLast(c.holderPop(), 3);
		//c.addToLast(c.holderPop(), 3);
		/*Engine e;
		e.addPlayer(new Player(std::string("Ewelina")), 1);
		e.addPlayer(new Player(std::string("Arnold Schnitzel")), 3);
		e.start();
		std::cout << e.json() << "\n\n";
		auto start = std::chrono::high_resolution_clock::now();
		auto s = e.json();
		auto stop = std::chrono::high_resolution_clock::now();
		std::cout << s << "\nTime taken: " << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << "ns\n";*/
		if (e.getCurrentState() == EngineStates::CREATED)
			e.start();
		int field;
		while (!e.finished()) {
			
			std::cout << e.str() << "\n\n";
			std::cout << "Current player: " << e.getCurrentPlayer().getNick() << '\n';
			std::cout << "Dice roll: " << e.rollDice() << '\n';
			std::cin >> field;

			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore();
			}

			std::cout << "Move: " << e.move(field) << ' ';
			std::cout << "Step: " << e.step() << "\n\n";
			
		}

		//std::cout << constructMessage(EventType::PLAYER_JOINED, p.json()) << '\n';
	}
	catch (std::exception& e) {
		std::cerr << e.what() << ' ' << __FILE__ << ':' << __LINE__ << '\n';
	}
	catch (std::string& e) {
		std::cerr << e << '\n';
	}
#ifdef _DEBUG
	system("pause");
#endif

	// delete engine;
	return 0;
}