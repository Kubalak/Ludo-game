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
	OnlineServer(unsigned int);
	void start();
	bool bind(std::string addr);

	~OnlineServer();
};
