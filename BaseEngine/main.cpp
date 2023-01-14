/**

Plik wykorzystywany do testów silnika gry.

@author Jakub Jach &copy; 2022
*/

#include <iostream>
#include <chrono>
#include <fstream>
#include "Engine.hpp"
#include "OnlineEngine.hpp"
#include "OnlineServer.hpp"
#ifndef __UNIX__
	#include <Windows.h>
#endif
#define SERVER


int main(int argc, char** argv) {

#ifdef SERVER
	unsigned int owner;
	std::string address;
	try {
#ifndef __UNIX__
		system("color");
		if (!SetConsoleTitle(L"OnlineServer"))
			std::cout << "Failed to set console title\n";
#endif
		std::cout << "Wprowadz id wlasciciela gry: ";
		do {
			if (std::cin.fail()) {
				std::cout << "Wprowadzono bledny typ danych\n";
				std::cin.clear();
				std::cin.ignore();
			}
			std::cin >> owner;
		} while (std::cin.fail());

		OnlineServer server(owner);
		do {
			std::cout << "Podaj adres serwera: ";
			std::cin >> address;
		} while (!server.bind(address));
		server.start();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	catch (...) {
		std::cerr << "Unknown exception!\n";
	}
#else
	try {

#ifndef __UNIX__
		system("color");
		if (!SetConsoleTitle(L"LudoClient"))
			std::cout << "Failed to set console title\n";
#endif
		std::string nick;
		unsigned int quarter, option = 1;
		std::cout << "Wprowadz swoj nick: ";
		std::cin >> nick;
		OnlineEngine engine;
		engine.connect("192.168.1.25");
		
		auto* p = new Player(std::string(nick));
		std::cout << "Twoje id " << p->getId() << "\nSkopiuj je do serwera jesli jestes wlascicielem\n";
		while (!engine.finished())
		{
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore();
			}
			std::cout << "Wybierz opcje: \n1. Dodaj gracza. \n2. Rozpocznij gre\n3. Rzuc kostka\n4. Wykonaj ruch\n5. Wyswietl stan silnika\nWybor: ";
			std::cin >> option;
			switch (option) {
			case 1:
				std::cout << "Podaj cwiartke: ";
				std::cin >> quarter;
				engine.addPlayer(p, quarter);
				break;
			case 2:
				engine.start();
				break;
			case 3:
				engine.rollDice();
				break;
			case 4:
				std::cout << "Wybierz pole: ";
				std::cin >> option;
				engine.move(option);
				break;
			case 5:
				std::cout << engine.str() << '\n';
				break;
			default:
				std::cout << "To nie jest poprawna opcja!\n";
				break;
			}
		}
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	catch (...) {
		std::cerr << "Unknown exception!\n";
	}
#endif
#if !defined(__UNIX__) && defined(_DEBUG)
	system("pause");
#endif

	return 0;
}