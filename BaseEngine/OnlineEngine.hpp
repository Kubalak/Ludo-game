#pragma once
#include "Engine.hpp"
#include <zmq.hpp>
#include <mutex>
#include <thread> // <- Uruchamiana b�dzie metoda run() z klasy.
#include <nlohmann/json.hpp>


/**
Klasa obs�uguj�ca klienta gry Chi�czyk.
@author Jakub Jach &copy; 2023
*/

class OnlineEngine : public Engine {
	/** W�tek do wersji online */
	std::thread* online;
	/** Metoda uruchamiania przez w�tek */
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
	/** Wysy�a ��danie ruchu do serwera
	* @param fieldNo Numer pola, z kt�rego chcemy si� ruszy�.
	* @return Informacja czy wys�ano ��danie.
	*/
	bool move(int fieldNo);
	/** Dodaje nowego gracza lokalnego. Uniemo�liwia dodanie wi�cej jak jednego gracza lokalnego. 
	* @param player Gracz lokalny, kt�rego dodajemy (gracze zdalni zostan� dodani automatycznie).
	* @param quarter �wiartka, w kt�rej ma znale�� si� gracz. Mo�liwa jest zmiana �wiartki nawet je�eli gracz lokalny ju� istnieje.
	*/
	bool addPlayer(Player* player, unsigned int quarter);
	/** 
	Wysy�a ��danie rozpocz�cia gry do serwera gry.
	! DODATKOWO !
	Uruchamia silnik online w postaci nowego w�tku.
	Do silnika mo�na odwo�ywa� si� jak do zwyk�ego Engine.
	Osobny w�tek zajmuje si� pobieraniem zmian z serwera.
	*/
	bool start();
	/**  
	* Wysy�a do serwera ��danie rzutu kostk�. Zwraca aktualn� warto�� kostki. 
	* @return Ostatnia warto�� kostki.
	*/
	unsigned int rollDice();

	/** Pod��cza klienta do serwera gry.
	* @param addr Adres serwera gry.
	* @return true przy powodzeniu zestawienia i konfiguracji po��czenia lub false w ka�dym innym przypadku.
	*/
	bool connect(std::string);

	/**
	* Zwraca wska�nik na lokalnego gracza.
	* @return Wska�nik na lokalnego gracza.
	*/
	Player* getLocalPlayer()noexcept { return localP; }

	~OnlineEngine();
};
