#include "OnlineServer.hpp"
#include "EventMsg.hpp"
#include <zmq_addon.hpp>
#include <ctime>


OnlineServer::OnlineServer(unsigned int owner) :
	onlineShouldWork(true),
	owner(owner),
	// Tablica skrótów.
	eventFuncs({
		{ "PLAYER_JOINED", [this](nlohmann::json& data) { return handlePlayerJoined(data);  } },
		{ "NEW_PLAYER", [this](nlohmann::json& data) { return handleNewPlayer(data);  } },
		{ "ENGINE_STATE", [this](nlohmann::json& data) { std::cout << *this << '\n'; return true;  }},
		{ "GAME_START", [this](nlohmann::json& data) { return handleGameStarted(data);  } },
		{ "DICE_ROLL", [this](nlohmann::json& data) { return handleDiceRoll(data);  } },
		{ "ROLL_RESULT", [this](nlohmann::json& data) { std::cout << "Not implemented "; return false; }},
		{ "PLAYER_MOVE", [this](nlohmann::json& data) { return handlePlayerMove(data);  } },
		{ "DELETE_PLAYER", [this](nlohmann::json& data) { std::cout << "Not implemented "; return false;  } },
		{ "GAME_FINISHED", [this](nlohmann::json& data) { std::cout << "Not implemented "; return false;  } }
	})	{

	serverSocketSubscriber = zmq::socket_t(context, zmq::socket_type::pull);
	serverSocketPublisher = zmq::socket_t(context, zmq::socket_type::push);

}


bool OnlineServer::handlePlayerJoined(nlohmann::json& ev) {
	std::stringstream ss;
	ss << "{\"players\":[";
	auto p = players.begin();
	for (; p != players.end();) {
		ss << "{\"player\":" << (*p).second->getPlayer() << ", \"quarter\":" << (*p).first + 1 << "}";
		++p;
		if (p != players.end())
			ss << ",";
	}
	ss << "]}";
	auto result = serverSocketPublisher.send(zmq::buffer(constructMessage(EventType::ENGINE_STATE, ss.str())), zmq::send_flags::none);
	std::cout << "players count " << players.size() << ' ';
	return result.has_value();
}

bool OnlineServer::handleNewPlayer(nlohmann::json& ev) {
	if (Engine::getCurrentState() != EngineStates::CREATED) {
		std::cout << "current state doesn't allow to add new players ";
		return false;
	}
	unsigned int q = ev["quarter"].get<unsigned int>();
	auto* p = new Player(ev["player"]);
	if (Engine::addPlayer(p, q)) {
		std::stringstream ss;
		ss << "{\"player\":" << *p << "," << "\"quarter\":" << q << "}"; // JSON z nowym graczem.
		std::cout << "added player " << p->getNick() << " with id " << p->getId() << ' ';
		return serverSocketPublisher.send(zmq::buffer(constructMessage(EventType::NEW_PLAYER, ss.str())), zmq::send_flags::none).has_value();
	}
	else {
		std::cout << "could not add new player ";
		delete p;
		return false;
	}
}

bool OnlineServer::handleGameStarted(nlohmann::json& ev) {
	if (ev["id"].get<unsigned int>() == owner) {
		if (Engine::start()) {
			std::cout << "starting new game... no new players allowed ";
			return serverSocketPublisher.send(zmq::buffer(constructMessage(EventType::GAME_START, "null")), zmq::send_flags::none).has_value();
		}
		else {
			std::cout << "cannot start game ";
			return false;
		}
	}
	std::cout << "player is not game owner ";
	return false;
}

bool OnlineServer::handleDiceRoll(nlohmann::json& ev) {
	if (getCurrentState() == EngineStates::CREATED) {
		std::cout << "game has not started yet ";
		return false;
	}

	if (ev["id"].get<unsigned int>() == getCurrentPlayer().getId()) {
		std::cout << "dice roll value " << rollDice() << ' ';
		return serverSocketPublisher.send(zmq::buffer(constructMessage(EventType::DICE_ROLL, dice.getLast())), zmq::send_flags::none).has_value();
	}
	return false;
}

bool OnlineServer::handlePlayerMove(nlohmann::json& ev) {
	if (getCurrentState() == EngineStates::CREATED) {
		std::cout << "game has not started yet ";
		return false;
	}

	if (ev["player"]["id"].get<unsigned int>() == getCurrentPlayer().getId()) {
		if (move(ev["field"].get<int>())) {
			std::cout << "player " << getCurrentPlayer().getNick() << "(" << getCurrentPlayer().getId() << ") moved from field " << ev["field"].get<int>() << ' ';
			if (!Engine::step())
				std::cout << "step has failed! ";
			return serverSocketPublisher.send(zmq::buffer(constructMessage(EventType::PLAYER_MOVE, ev["field"].get<int>())), zmq::send_flags::none).has_value();
		}
		std::cout << "player " << getCurrentPlayer().getNick() << "(" << getCurrentPlayer().getId() << ") couldn't move from field " << ev["field"].get<int>() << ' ';
		return false;
	}
	std::cout << "this player can't move now ";

	return false;
}


void OnlineServer::start() {
	if (state == EngineStates::CREATED) {
		run();
	}
}

// # IMPORTANT #
//TODO: Zaimplementowaæ metodê run.
void OnlineServer::run() {
	char buf[80];
	nlohmann::json jmessage;
	bool retval;
	std::string eventType;
	while (onlineShouldWork && !finished()) {
		try {
			zmq::message_t message;
			zmq::recv_result_t result = serverSocketSubscriber.recv(message, zmq::recv_flags::dontwait);
			if (result.has_value())
			{
				
				std::cout << std::resetiosflags(std::cout.flags());
				jmessage = nlohmann::json::parse(message.to_string());
				eventType = jmessage["event"].get<std::string>();
				if (eventFuncs.find(eventType) == eventFuncs.end()) {
					std::cout << "[" << currentTimestamp(buf, 80) << "]: Unknown event type \"" << eventType << "\"\n";
					continue;
				}

				std::cout << "[" << currentTimestamp(buf, 80) << "]: " << eventType << ' ';
				retval = eventFuncs.at(eventType)(jmessage["payload"]);
				std::cout << "[" << (retval ? "\033[0;32mOK\033[0m" : "\033[0;31m--\033[0m") << "]\n";
			}			
		}
		catch (std::exception& e) {
			std::cerr << "\n\033[0;33m[" << currentTimestamp(buf, 80) << "]:  WARNING: " << e.what() << "\033[0m\n";
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(5)); // 200 ticks/s
	}
}

bool OnlineServer::bind(std::string addr) {
	try {
		serverSocketPublisher.bind("tcp://"+addr+":2000");
		serverSocketSubscriber.bind("tcp://" + addr + ":2001");
		std::cout << "Server is available under " << addr << '\n';
		return true;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	catch (...) {
		std::cerr << "Unknown exception in " << __FILE__ << " at line " << __LINE__ << '\n';
	}
	return false;
}

OnlineServer::~OnlineServer() {
	onlineShouldWork = false;
	if (serverSocketPublisher)
		serverSocketPublisher.close();
	if (serverSocketSubscriber)
		serverSocketSubscriber.close();
}