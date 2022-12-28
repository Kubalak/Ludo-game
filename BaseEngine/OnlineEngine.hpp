#pragma once
#include "Engine.hpp"
#include <zmq.hpp>
#include <mutex>
#include <thread> // <- Uruchamiana bêdzie metoda run() z klasy.
#include <nlohmann/json.hpp>

//TODO: Sieæ i wymiana danych.
//TODO: Dzia³anie jako klient / serwer gry.
//TODO: Zabezpieczenie metod modyfikuj¹cych dane.

class OnlineEngine : public Engine {
	/** Zapewnia bezpieczeñstwo danych przy u¿yciu metod */
	std::mutex method_lock;
	/** W¹tek do wersji online */
	std::thread* online;
	/** Metoda uruchamiania przez w¹tek */
	bool onlineShouldWork;
	Player* localP;
	void run();
	std::string addr;
	zmq::context_t context{ 1 };
	zmq::socket_t serverSubscriber;
	zmq::socket_t eventPublisher;
public:
	OnlineEngine();
	/** Dzia³a jak z Engine ale z u¿yciem mutexa */
	bool move(int fieldNo);
	/** Dodaje nowego gracza ze wskazaniem, czy jest to gracz lokalny. Uniemo¿liwia dodanie wiêcej jak jednego gracza lokalnego. */
	bool addPlayer(Player* player, unsigned int quarter, bool local = true);
	/** Inicjuje grê jak w Engine.
		! DODATKOWO !
		Uruchamia silnik online w postaci nowego w¹tku.
		Do silnika mo¿na odwo³ywaæ siê jak do zwyk³ego Engine. 
		Osobny w¹tek zajmuje siê komunikacj¹ z serwerem. 
	*/
	void start();
	/**  Dzia³a jak z Engine ale z u¿yciem mutexa */
	bool step();
	/**  Dzia³a jak z Engine ale z u¿yciem mutexa */
	unsigned int rollDice();

	/** Pod³¹cza klienta do serwera gry. 
	* @param server - Adres serwera gry.
	* @return true przy powodzeniu zestawienia i konfiguracji po³¹czenia lub false w ka¿dym innym przypadku.
	*/
	bool connect(std::string, std::string);

	~OnlineEngine();
};
