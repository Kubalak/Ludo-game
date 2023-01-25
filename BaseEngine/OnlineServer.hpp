#pragma once
#pragma once
#include "Engine.hpp"
#include <zmq.hpp>
#include <thread>
#include <nlohmann/json.hpp>

/**
Klasa obs�uguj�ca serwer i brokera gry Chi�czyk.
@author Jakub Jach &copy; 2023
*/
class OnlineServer : private Engine {
	/** Zapewnia bezpiecze�stwo danych przy u�yciu metod */
	bool onlineShouldWork;
	unsigned int owner;
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
	/** Domy�lny konstruktor serwera */
	OnlineServer();
	/** 
	* Rozpoczyna gr�. Blokuje bie��cy w�tek a� do zako�czenia gry.
	* @return true W przypadku pomy�lnego uruchomienia lub false w przeciwnym wypadku
	*/
	bool start();
	/** 
	* Przypisanie ADRESU dla serwera. Nr port�w to<br/>2000 dla socket nas�uchuj�cego 2001 dla wysy�ania zdarze�.
	* @param addr Adres IP, pod kt�ry podpi�� socket.
	* @return true w przypadku powodzenia lub false w przeciwnym wypadku.
	*/
	bool bind(std::string addr);

	~OnlineServer();
};
