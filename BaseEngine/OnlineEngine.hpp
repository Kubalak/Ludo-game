#pragma once
#include "Engine.hpp"
#include <zmq.hpp>
#include <mutex>
#include <thread> // <- Uruchamiana bêdzie metoda run() z klasy.
#include <nlohmann/json.hpp>


/**
Klasa obs³uguj¹ca klienta gry Chiñczyk.
@author Jakub Jach &copy; 2023
*/

class OnlineEngine : public Engine {
	/** W¹tek do wersji online */
	std::thread* online;
	/** Metoda uruchamiania przez w¹tek */
	bool onlineShouldWork;
	bool onlineIsWorking;
	Player* localP;
	void run();
	std::string addr;
	zmq::context_t context{ 1 };
	zmq::socket_t serverSubscriber;
	zmq::socket_t eventPublisher;
	const std::map<std::string, std::function<bool(nlohmann::json&)>> respFuncs;

	bool handlePlayers(nlohmann::json&);
	bool handleNewPlayer(nlohmann::json&);
	bool handleStart(nlohmann::json&);
	bool handleMove(nlohmann::json&);
	bool handleRoll(nlohmann::json&);

public:
	OnlineEngine();
	/** Wysy³a ¿¹danie ruchu do serwera
	* @param fieldNo Numer pola, z którego chcemy siê ruszyæ.
	* @return Informacja czy wys³ano ¿¹danie.
	*/
	bool move(int fieldNo);
	/** Dodaje nowego gracza lokalnego. Uniemo¿liwia dodanie wiêcej jak jednego gracza lokalnego. 
	* @param player Gracz lokalny, którego dodajemy (gracze zdalni zostan¹ dodani automatycznie).
	* @param quarter Æwiartka, w której ma znaleŸæ siê gracz. Mo¿liwa jest zmiana æwiartki nawet je¿eli gracz lokalny ju¿ istnieje.
	*/
	bool addPlayer(Player* player, unsigned int quarter);
	/** 
	Wysy³a ¿¹danie rozpoczêcia gry do serwera gry.
	! DODATKOWO !
	Uruchamia silnik online w postaci nowego w¹tku.
	Do silnika mo¿na odwo³ywaæ siê jak do zwyk³ego Engine.
	Osobny w¹tek zajmuje siê pobieraniem zmian z serwera.
	*/
	bool start();
	/**  
	* Wysy³a do serwera ¿¹danie rzutu kostk¹. Zwraca aktualn¹ wartoœæ kostki. 
	* @return Ostatnia wartoœæ kostki.
	*/
	unsigned int rollDice();

	/** Pod³¹cza klienta do serwera gry.
	* @param addr Adres serwera gry.
	* @return true przy powodzeniu zestawienia i konfiguracji po³¹czenia lub false w ka¿dym innym przypadku.
	*/
	bool connect(std::string);

	/**
	* Zwraca wskaŸnik na lokalnego gracza.
	* @return WskaŸnik na lokalnego gracza.
	*/
	Player* getLocalPlayer()noexcept { return localP; }

	~OnlineEngine();
};
