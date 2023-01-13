#pragma once
#pragma once
#include "Engine.hpp"
#include <zmq.hpp>
#include <mutex>
#include <thread> // <- Uruchamiana bêdzie metoda run() z klasy.
#include <nlohmann/json.hpp>

//TODO: Sprawdziæ czy siê nie wysypie z byle powodu.

/**
Klasa obs³uguj¹ca serwer i brokera gry Chiñczyk.
@author Jakub Jach &copy; 2023
*/
class OnlineServer : private Engine {
	/** Zapewnia bezpieczeñstwo danych przy u¿yciu metod */
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
	/** Konstruktor z wybraniem id gracza w³aœciciela gry */
	OnlineServer(unsigned int);
	/** Rozpoczyna grê. Blokuje bie¿¹cy w¹tek a¿ do zakoñczenia gry.*/
	void start();
	/** Przypisanie ADRESU dla serwera. Nr portów to<br/>2000 dla socket nas³uchuj¹cego 2001 dla wysy³ania zdarzeñ.*/
	bool bind(std::string addr);

	~OnlineServer();
};
