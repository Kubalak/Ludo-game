#pragma once
#pragma once
#include "Engine.hpp"
#include <zmq.hpp>
#include <mutex>
#include <thread> // <- Uruchamiana b�dzie metoda run() z klasy.
#include <nlohmann/json.hpp>

//TODO: Sprawdzi� czy si� nie wysypie z byle powodu.

/**
Klasa obs�uguj�ca serwer i brokera gry Chi�czyk.
@author Jakub Jach &copy; 2023
*/
class OnlineServer : private Engine {
	/** Zapewnia bezpiecze�stwo danych przy u�yciu metod */
	bool onlineShouldWork;
	const unsigned int owner;
	void run();
	std::string addr;
	zmq::context_t context{ 1 };
	zmq::socket_t serverSocketPublisher;
	zmq::socket_t serverSocketSubscriber;

	const std::map < std::string, std::function<bool(nlohmann::json&)>> eventFuncs;

	bool handlePlayerJoined(nlohmann::json& ev);
	bool handleNewPlayer(nlohmann::json& ev);
	bool handleGameStarted(nlohmann::json& ev);
	bool handleDiceRoll(nlohmann::json& ev);
	bool handlePlayerMove(nlohmann::json& ev);
public:
	/** Konstruktor z wybraniem id gracza w�a�ciciela gry */
	OnlineServer(unsigned int);
	/** Rozpoczyna gr�. Blokuje bie��cy w�tek a� do zako�czenia gry.*/
	void start();
	/** Przypisanie ADRESU dla serwera. Nr port�w to<br/>2000 dla socket nas�uchuj�cego 2001 dla wysy�ania zdarze�.*/
	bool bind(std::string addr);

	~OnlineServer();
};
