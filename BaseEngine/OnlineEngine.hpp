#pragma once
#include "Engine.hpp"
#include <zmq.hpp>
#include <mutex>
#include <thread> // <- Uruchamiana b�dzie metoda run() z klasy.
#include <nlohmann/json.hpp>

//TODO: Sie� i wymiana danych.
//TODO: Dzia�anie jako klient / serwer gry.
//TODO: Zabezpieczenie metod modyfikuj�cych dane.

class OnlineEngine : public Engine {
	/** Zapewnia bezpiecze�stwo danych przy u�yciu metod */
	std::mutex method_lock;
	/** W�tek do wersji online */
	std::thread* online;
	/** Metoda uruchamiania przez w�tek */
	bool onlineShouldWork;
	Player* localP;
	void run();
	std::string addr;
	zmq::context_t context{ 1 };
	zmq::socket_t serverSubscriber;
	zmq::socket_t eventPublisher;
public:
	OnlineEngine();
	/** Dzia�a jak z Engine ale z u�yciem mutexa */
	bool move(int fieldNo);
	/** Dodaje nowego gracza ze wskazaniem, czy jest to gracz lokalny. Uniemo�liwia dodanie wi�cej jak jednego gracza lokalnego. */
	bool addPlayer(Player* player, unsigned int quarter, bool local = true);
	/** Inicjuje gr� jak w Engine.
		! DODATKOWO !
		Uruchamia silnik online w postaci nowego w�tku.
		Do silnika mo�na odwo�ywa� si� jak do zwyk�ego Engine. 
		Osobny w�tek zajmuje si� komunikacj� z serwerem. 
	*/
	void start();
	/**  Dzia�a jak z Engine ale z u�yciem mutexa */
	bool step();
	/**  Dzia�a jak z Engine ale z u�yciem mutexa */
	unsigned int rollDice();

	/** Pod��cza klienta do serwera gry. 
	* @param server - Adres serwera gry.
	* @return true przy powodzeniu zestawienia i konfiguracji po��czenia lub false w ka�dym innym przypadku.
	*/
	bool connect(std::string, std::string);

	~OnlineEngine();
};
