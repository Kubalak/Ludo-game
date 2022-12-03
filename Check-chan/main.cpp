#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
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

int main()
{
    try {
		std::ifstream f("sample.json");
		nlohmann::json data = nlohmann::json::parse(f);
		std::cout << data["quiz"]["sport"]["q1"]["question"] << '\n'; // Which one is correct team name in NBA?
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		return 1;
	}

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    auto image = sf::Image();
    if (!image.loadFromFile("icon.png")) {
        std::cerr << "Nie udalo sie zaladowac pliku!\n";
        exit(-1);
    }
    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    window.setFramerateLimit(60);
    system("title Check chan");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}