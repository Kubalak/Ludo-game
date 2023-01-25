/** \mainpage Strona g��wna
* Ta cz�� projektu odpowiedzialna jest za silnik rozgrywki oraz obs�ug� sieci.
* G��wne klasy silnika wykorzystywane w projekcie GUI:
* - \subpage Engine
* - \subpage OnlineEngine
* - \subpage OnlineServer
* 
* ## Dodatkowo w ramach projektu utworzono klasy:
* - Dice
* - Counter
* - Player
* - PlayerContainer
* - Tile
* ##  Funkcje dodatkowe
* - Pliki EventMsg.hpp i EventMsg.cpp udost�pniaj� funkcje pozwalaj�ce na stworzenie komunikat�w dla obslugi sieci oraz pobranie aktualnej daty i godziny w postaci ci�gu znak�w.
* - Plik [linux_prepare_libs.sh](../../../linux_prepare_libs.sh) w g��wnym katalogu pozwala na zbudowanie zewn�trznych bibliotek dla Linuxa (wymaga narz�dzia [git](https://git-scm.com/) oraz [cmake](https://cmake.org/)).
* - Plik [Makefile](../../Makefile) umo�liwia zbudowanie serwera w systemie Linux (z u�yciem [make](https://man7.org/linux/man-pages/man1/make.1.html)). <br/>
Opcje pliku makefile (polecenia terminala):
*   + `make` - Buduje zwyk�y plik wykonywalny w systemie Linux zlokalizowany w folderze `LudoGameServer_0.9-1/bin`
*   + `make <nazwa_klasy>` - Buduje obiekt klasy z opcj� `-c`.
*   + `make deb` - Buduje projekt i tworzy plik `LudoGameServer_0.9-1.deb` gotowy do instalacji w systemie (u�ywaj�c [dpkg](https://man7.org/linux/man-pages/man1/dpkg.1.html)).
* ## U�ytke biblioteki opr�cz standardowych bibliotek C++:
* - [ZeroMQ](https://zeromq.org) s�u��cej do obs�ugi wymiany danych poprzez sie�.
* - [JSON](https://github.com/nlohmann/json) s�u��ca do serializacji obiekt�w i obs�ugi komunikat�w.
@author Jakub Jach &copy; 2023
*/

/** \page Engine
* Ta klasa implementuje funkcjonalno�� silnika gry "Chi�czyk".
* Jest to bazowa klasa na podstawie kt�rej tworzone s� klasy OnlineEngine oraz OnlineServer.
* Przejd� do dokumentacji klasy Engine.
*/

/** \page OnlineEngine
* Klasa odpowiada za klienta dla gry "Chi�czyk" w wersji online.
* Do wymiany danych wykorzystywany jest format JSON.
* Opr�cz metod dziedziczonych z Engine posiada swoje w�asne unikalne metody.
* Przejd� do dokumentacji klasy OnlineEngine.
*/

/** \page OnlineServer
* Klasa odpowiedzialna za serwer gry "Chi�czyk".
* Opr�cz metod z klasy Engine implementowane s� dodatkowe metody do zarz�dzania serwerem.
* Wymiana danych w postaci formatu JSON.
* Przejd� do dokumentacji klasy OnlineServer.
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
		std::cout << "Argumenty:\n-help\t\tWyswietla ten tekst.\n-address [ip]\tAdres pod ktorym ma byc dostepny serwer.\nNacisnij enter aby zakonczyc\n";
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
			if (std::strcmp(argv[i], "-address") == 0)
				address = std::string(argv[i + 1]);
		}
		OnlineServer server;
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