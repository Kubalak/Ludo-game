#pragma once
#pragma once
#include "Engine.hpp"
#include <zmq.hpp>
#include <mutex>
#include <thread> // <- Uruchamiana b�dzie metoda run() z klasy.
#include <nlohmann/json.hpp>

//TODO: Przepisa� na system obs�ugi komunikat�w od klient�w.
class OnlineServer : private Engine {
	/** Zapewnia bezpiecze�stwo danych przy u�yciu metod */
	std::mutex method_lock;

	bool onlineShouldWork;

	void run();
	std::string addr;
	zmq::context_t context;
	zmq::socket_t serverSocketPublisher;
	zmq::socket_t serverSocketSubscriber;

	/** Dzia�a jak z Engine ale z u�yciem mutexa */
	bool move(int fieldNo);
	/** Dodaje nowego gracza ze wskazaniem, czy jest to gracz lokalny. Uniemo�liwia dodanie wi�cej jak jednego gracza lokalnego. */
	bool addPlayer(Player* player, unsigned int quarter);
	/** Inicjuje gr� jak w Engine.
		! DODATKOWO !
		Uruchamia silnik online w postaci nowego w�tku.
		Do silnika mo�na odwo�ywa� si� jak do zwyk�ego Engine.
		Osobny w�tek zajmuje si� komunikacj� z serwerem.
	*/

	/** 
	Dzia�a jak z Engine ale z u�yciem mutexa 
	*/
	bool step();
	/** 
	Dzia�a jak z Engine ale z u�yciem mutexa 
	*/
	unsigned int rollDice();

public:
	OnlineServer();
	void start();
	bool bind(std::string addr);

	~OnlineServer();
};
