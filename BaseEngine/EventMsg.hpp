#pragma once
#include <map>
#include <string>
#include <sstream>
#include <ctime>

/** Klasa do typ�w wiadomo�ci */
enum class EventType {
	PLAYER_JOINED,
	NEW_PLAYER,
	ENGINE_STATE,
	GAME_START,
	DICE_ROLL,
	ROLL_RESULT,
	PLAYER_MOVE,
	DELETE_PLAYER,
	GAME_FINISHED
};

/** Mapa u�yta do konwersji obiektu EventType na std::string.*/
const static std::map<EventType, std::string> eventStr{
	{EventType::PLAYER_JOINED, "PLAYER_JOINED"},
	{EventType::NEW_PLAYER, "NEW_PLAYER"},
	{EventType::ENGINE_STATE, "ENGINE_STATE"},
	{EventType::GAME_START, "GAME_START"},
	{EventType::DICE_ROLL, "DICE_ROLL"},
	{EventType::ROLL_RESULT, "ROLL_RESULT"},
	{EventType::PLAYER_MOVE, "PLAYER_MOVE"},
	{EventType::DELETE_PLAYER, "DELETE_PLAYER"},
	{EventType::GAME_FINISHED, "GAME_FINISHED"}
};

/**
* Zwraca wiadomo�� mo�liw� do wys�ania przez zmq::socket
* @param type Rodzaj wydarzenia, kt�re mia�o miejsce.
* @param obj Obiekt do przekazania jako wiadomo�� w formacie JSON (musi by� mo�liwy do przekazania do strumienia).
* @return Ci�g znak�w konwertowalny do nlohmann::json.
*/
template <typename T> std::string constructMessage(EventType type, const T& obj) {
	std::stringstream ss;
	ss << "{\"event\":\"" << eventStr.at(type) << "\",";
	ss << "\"payload\":" << obj << "}";

	return ss.str();
}

/**
* Zwraca aktualn� dat� i godzin� w postaci ci�gu znak�w.
* @param buf[] Bufor znak�w do kt�rego ma zosta� wpisana data i godzina.
* @param bufflen Rozmiar bufora.
* @return Parametr buf[].
*/
const char* currentTimestamp(char buf[], int bufflen);