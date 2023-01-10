#pragma once
#pragma once
#include "Engine.hpp"
#include <zmq.hpp>
#include <mutex>
#include <thread> // <- Uruchamiana bêdzie metoda run() z klasy.
#include <nlohmann/json.hpp>

//TODO: Przepisaæ na system obs³ugi komunikatów od klientów.
class OnlineServer : private Engine {
	/** Zapewnia bezpieczeñstwo danych przy u¿yciu metod */
	std::mutex method_lock;

	bool onlineShouldWork;

	void run();
	std::string addr;
	zmq::context_t context;
	zmq::socket_t serverSocketPublisher;
	zmq::socket_t serverSocketSubscriber;

	/** Dzia³a jak z Engine ale z u¿yciem mutexa */
	bool move(int fieldNo);
	/** Dodaje nowego gracza ze wskazaniem, czy jest to gracz lokalny. Uniemo¿liwia dodanie wiêcej jak jednego gracza lokalnego. */
	bool addPlayer(Player* player, unsigned int quarter);
	/** Inicjuje grê jak w Engine.
		! DODATKOWO !
		Uruchamia silnik online w postaci nowego w¹tku.
		Do silnika mo¿na odwo³ywaæ siê jak do zwyk³ego Engine.
		Osobny w¹tek zajmuje siê komunikacj¹ z serwerem.
	*/

	/** 
	Dzia³a jak z Engine ale z u¿yciem mutexa 
	*/
	bool step();
	/** 
	Dzia³a jak z Engine ale z u¿yciem mutexa 
	*/
	unsigned int rollDice();

public:
	OnlineServer();
	void start();
	bool bind(std::string addr);

	~OnlineServer();
};
