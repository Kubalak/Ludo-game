#pragma once
#pragma once
#include "Engine.hpp"
#include <zmq.hpp>
#include <thread>
#include <nlohmann/json.hpp>

/**
Klasa obs³uguj¹ca serwer i brokera gry Chiñczyk.
@author Jakub Jach &copy; 2023
*/
class OnlineServer : private Engine {
	/** Zapewnia bezpieczeñstwo danych przy u¿yciu metod */
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
	/** Domyœlny konstruktor serwera */
	OnlineServer();
	/** 
	* Rozpoczyna grê. Blokuje bie¿¹cy w¹tek a¿ do zakoñczenia gry.
	* @return true W przypadku pomyœlnego uruchomienia lub false w przeciwnym wypadku
	*/
	bool start();
	/** 
	* Przypisanie ADRESU dla serwera. Nr portów to<br/>2000 dla socket nas³uchuj¹cego 2001 dla wysy³ania zdarzeñ.
	* @param addr Adres IP, pod który podpi¹æ socket.
	* @return true w przypadku powodzenia lub false w przeciwnym wypadku.
	*/
	bool bind(std::string addr);

	~OnlineServer();
};
