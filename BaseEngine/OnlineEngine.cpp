#include "OnlineEngine.hpp"
#include "EventMsg.hpp"
#include <ctime>


OnlineEngine::OnlineEngine() :
	onlineShouldWork(true),
	online(nullptr),
	localP(nullptr),
	onlineIsWorking(false),
	respFuncs({
		{ "PLAYER_JOINED", [this](nlohmann::json& data) { std::cout << " not implemented "; return true; }},
		{ "NEW_PLAYER", [this](nlohmann::json& data) { return handleNewPlayer(data);  }},
		{ "ENGINE_STATE", [this](nlohmann::json& data) { return handlePlayers(data);  }},
		{ "GAME_START", [this](nlohmann::json& data) { return handleStart(data);  }},
		{ "DICE_ROLL", [this](nlohmann::json& data) { return handleRoll(data);  }},
		{ "ROLL_RESULT", [this](nlohmann::json& data) { std::cout << " Not implemented "; return false; }},
		{ "PLAYER_MOVE", [this](nlohmann::json& data) { return handleMove(data);  }},
		{ "DELETE_PLAYER", [this](nlohmann::json& data) { std::cout << " Not implemented "; return false;  }},
		{ "GAME_FINISHED", [this](nlohmann::json& data) { std::cout << " Not implemented "; return false;  }}
		}) {

	serverSubscriber = zmq::socket_t(context, zmq::socket_type::sub);
	eventPublisher = zmq::socket_t(context, zmq::socket_type::push);
}


bool OnlineEngine::handlePlayers(nlohmann::json& ev) {
	Player* player;
	unsigned int q, id;
	for (auto& p : ev["players"])
	{
		
		id = p["player"]["id"].get<unsigned int>();
		q = p["quarter"].get<unsigned int>();
		if (std::count_if(players.begin(), players.end(), [&id](std::pair<unsigned int, PlayerContainer*> c) {return c.second->getPlayer().getId() == id; }) == 0) {
			player = new Player(p["player"]);
			if (!Engine::addPlayer(player, q)) {
				std::cout << " error while adding player ";
				delete player;
				return false;
			}
			std::cout << " online player " << player->getNick() << "(" << player->getId() << ") ";
		}
	}
	return true;
}

bool OnlineEngine::handleNewPlayer(nlohmann::json& ev) {
	unsigned int id, q;
	id = ev["player"]["id"].get<unsigned int>();
	q = ev["quarter"].get<unsigned int>();
	if (std::count_if(players.begin(), players.end(), [&id](std::pair<unsigned int, PlayerContainer*> c) {return c.second->getPlayer().getId() == id; }) == 0) {
		auto* player = new Player(ev["player"]);
		if (!Engine::addPlayer(player, q)) {
			std::cout << " error while adding player ";
			delete player;
			return false;
		}
	}
	std::cout << " player exists ";
	return true;
}

bool OnlineEngine::handleStart(nlohmann::json& ev) {
	return Engine::start();
}

bool OnlineEngine::handleMove(nlohmann::json& ev) {
	bool result = Engine::move(ev.get<int>());
	if (result)
		std::cout << " player has moved from field " << ev.get<int>() << ' ';
	else
		std::cout << " player move failed ";
	bool stepval = Engine::step();
	if (!stepval)
		std::cout << " step has failed ";

	return result && stepval;
}

bool OnlineEngine::handleRoll(nlohmann::json& ev) {
	Engine::rollDice(); // Konieczne do zmiany stanu na DICE_ROLLED
	return dice.setLast(ev.get<unsigned int>());
}


bool OnlineEngine::move(int fieldNo) {
	if (currentPlayer < 0)
		return false;
	if (getCurrentPlayer().getId() != localP->getId())
		return false;
	std::stringstream ss;
	ss << "{\"player\":" << *localP << "," << "\"field\":" << fieldNo << "}"; //JSON z kto co robi.
	// Wys³anie ¿¹dania ruchu bez oczekiwania.
	return eventPublisher.send(zmq::buffer(constructMessage(EventType::PLAYER_MOVE, ss.str())), zmq::send_flags::dontwait).has_value(); // Czy wysy³anie zakoñczono powodzeniem.
}

bool OnlineEngine::addPlayer(Player* player, unsigned int quarter) {
	// Sprawdzamy czy lokalny gracz istnieje i czy nie wystêpuje na liœcie graczy.
	if (localP != nullptr && std::count_if(players.begin(), players.end(), [this](const std::pair<int, PlayerContainer*>& pc) {return pc.second->getPlayer().getId() == localP->getId(); }))
		return false;
	else if (localP == nullptr)
		localP = player;
	std::stringstream ss;
	ss << "{\"player\":" << *localP << "," << "\"quarter\":" << quarter << "}"; // JSON z nowym graczem.
	// Wys³anie ¿¹dania dodania do listy graczy (blokuj¹ce).
	auto result = eventPublisher.send(zmq::buffer(constructMessage(EventType::NEW_PLAYER, ss.str())), zmq::send_flags::none);

	return result.has_value();
}

bool OnlineEngine::start() {
	if (state == EngineStates::CREATED && localP != nullptr) {
		auto result = eventPublisher.send(zmq::buffer(constructMessage(EventType::GAME_START, *localP)), zmq::send_flags::none);
		return result.has_value();
	}
	return false;
}

// # IMPORTANT #
//TODO: Zaimplementowaæ metodê run.
void OnlineEngine::run() {
	char buf[80];
	nlohmann::json response;
	std::string type;
	bool retval;
	std::cout << "[" << currentTimestamp(buf, 80) << "]: New thread with id " << std::this_thread::get_id() << " created\n";
	onlineIsWorking = true;
	while (onlineShouldWork) {
		try {
			zmq::message_t message;
			zmq::recv_result_t result = serverSubscriber.recv(message, zmq::recv_flags::dontwait); // !!!!
			if (result.has_value()) {
				response = nlohmann::json::parse(message.to_string());
				type = response["event"].get<std::string>();
				if (respFuncs.find(type) == respFuncs.end()) {
					std::cout << "[" << currentTimestamp(buf, 80) << "]: Unknown event type \"" << type << "\"\n";
					continue;
				}
				std::cout << "[" << currentTimestamp(buf, 80) << "]: "<< type << ' ';
				retval = respFuncs.at(type)(response["payload"]);
				std::cout << "[" << (retval ? "\033[0;32mOK\033[0m" : "\033[0;31m--\033[0m") << "]\n";
				
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Ograniczenie szybkoœci do 20 ticks/s.
		}
		catch (std::exception& e) {
			std::cerr << "\n\033[0;33m[" << currentTimestamp(buf, 80) << "]: WARNING " << e.what() << "\033[0m\n";
		}
	}
	onlineIsWorking = false;
}

bool OnlineEngine::step() {
	return true;
}

unsigned int OnlineEngine::rollDice() {
	// Wysy³a wiadomoœæ z DICE_ROLL
	if (localP != nullptr)
		eventPublisher.send(zmq::buffer(constructMessage(EventType::DICE_ROLL, *localP)), zmq::send_flags::dontwait);
	return dice.getLast();
}

bool OnlineEngine::connect(std::string addr) {
	try {
		serverSubscriber.connect("tcp://" + addr + ":2000");
		serverSubscriber.set(zmq::sockopt::subscribe, "");
		eventPublisher.connect("tcp://" + addr + ":2001");
		online = new std::thread([this] { run(); });
		eventPublisher.send(zmq::buffer(constructMessage(EventType::PLAYER_JOINED, "null")), zmq::send_flags::none);
		return true;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	catch (...) {
		std::cerr << "Unknown exception in " << __FILE__ << " line: " << __LINE__ << '\n';
	}
	return false;
}

OnlineEngine::~OnlineEngine() {
	onlineShouldWork = false;
	if (online != nullptr) {
		if(serverSubscriber)
			online->join();
		delete online;
	}
	if (eventPublisher.handle() != nullptr) 
		eventPublisher.close();
	if (serverSubscriber.handle() != nullptr)
		serverSubscriber.close();
	
	context.shutdown();
	if (localP != nullptr)
		delete localP;
}