/**

Plik wykorzystywany do testów silnika gry.

@author Jakub Jach &copy; 2023
*/

#include <iostream>
#include "OnlineServer.hpp"
#ifndef __UNIX__
	#include <Windows.h>
#endif



int main(int argc, char** argv) {

	unsigned int owner = 1;
	bool ownerSet = false;
	std::string address;
	if (argc == 2 && std::strcmp(argv[1], "-help") == 0) {
		std::cout << "Argumenty:\n-help\t\tWyswietla ten tekst.\n-owner [id]\tUstala wlasciciela gry przy uruchamianiu.\n-address [ip]\tAdres pod ktorym ma byc dostepny serwer.\nNacisnij enter aby zakonczyc\n";
		std::cin.get();
		return 0;
	}
#ifndef __UNIX__
	system("color");
	if (!SetConsoleTitle(L"Ludo Game Server"))
		std::cout << "Failed to set console title\n";
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prev_mode;
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
#endif
	try {
		for (int i{ 0 }; i < argc - 1; ++i) {
			if (std::strcmp(argv[i], "-owner") == 0) {
				try {
					owner = std::stoul(argv[i + 1]);
					ownerSet = true;
				}
				catch (std::exception& e) {
					std::cerr << "Argument parsing error " << e.what() << '\n';
				}
			}
			else if (std::strcmp(argv[i], "-address") == 0)
				address = std::string(argv[i + 1]);
		}
		if (!ownerSet) {
			std::cout << "Wprowadz id wlasciciela gry: ";
			do {
				if (std::cin.fail()) {
					std::cout << "Wprowadzono bledny typ danych\n";
					std::cin.clear();
					std::cin.ignore();
				}
				std::cin >> owner;
			} while (std::cin.fail());
		}
		OnlineServer server(owner);
		if (address == "")
		{
			do {
				std::cout << "Podaj adres serwera: ";
				std::cin >> address;
			} while (!server.bind(address));
			std::thread serverThread([&server] {server.start(); });
			serverThread.join();
		}
		else if (server.bind(address)) {
			std::thread serverThread([&server] {server.start(); });
			serverThread.join();
		}
		else std::cerr << "Couldn't start server!\n";
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	catch (...) {
		std::cerr << "Unknown exception!\n";
	}
#ifndef __UNIX__
	SetConsoleMode(hInput, prev_mode);
#endif 
#if !defined(__UNIX__) && defined(_DEBUG)
	system("pause");
#endif

	return 0;
}

/*
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
*/