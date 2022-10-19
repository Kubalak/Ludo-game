#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Player.hpp"

int main(int argc, char** argv, char** env) {
	try {
		std::ifstream f("sample.json");
		nlohmann::json data = nlohmann::json::parse(f);
		std::cout << data["quiz"]["sport"]["q1"]["question"] << '\n'; // Which one is correct team name in NBA?
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		return 1;
	}
#ifdef _DEBUG 
	system("pause"); // Stop konsole before program exits.
#endif
	return 0;
}