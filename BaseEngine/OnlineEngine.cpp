#include "OnlineEngine.hpp"
#include "EventMsg.hpp"
#include <ctime>


OnlineEngine::OnlineEngine() :
	onlineShouldWork(true),
	online(nullptr),
	localP(nullptr) {
	serverSubscriber = zmq::socket_t(context, zmq::socket_type::pull);
	eventPublisher = zmq::socket_t(context, zmq::socket_type::push);
}

bool OnlineEngine::move(int fieldNo) {
	std::lock_guard<std::mutex> lock(method_lock); // <- Blokuje mutex dla bie¿¹cego kontekstu.
	return Engine::move(fieldNo);
}

bool OnlineEngine::addPlayer(Player* player, unsigned int quarter, bool local) {
	std::lock_guard<std::mutex> lock(method_lock); // <- Blokuje mutex dla bie¿¹cego kontekstu.
	if (localP != nullptr && local == true)
		return false;
	auto res = Engine::addPlayer(player, quarter);
	if (res)
		localP = player;
	return res;
}

void OnlineEngine::start() {
	std::lock_guard<std::mutex> lock(method_lock); // <- Blokuje mutex dla bie¿¹cego kontekstu.
	if (state == EngineStates::CREATED) {
		auto result = eventPublisher.send(zmq::buffer(constructMessage(EventType::GAME_START, *localP)), zmq::send_flags::none);
		std::cout << "Thread id: " << std::this_thread::get_id() << '\n';
		online = new std::thread([this] { run(); });
	}
}

// # IMPORTANT #
//TODO: Zaimplementowaæ metodê run.
void OnlineEngine::run() {
	char buf[80];

	std::cout << "["<< currentTimestamp(buf, 80) << "]: New thread with id "<< std::this_thread::get_id() << " created\n";
	while (onlineShouldWork) {
		zmq::message_t message;
		zmq::recv_result_t result = serverSubscriber.recv(message, zmq::recv_flags::dontwait); // !!!!
		if (result.has_value())
			std::cout << "[" << currentTimestamp(buf, 80) << "]: Server message \"" << message.to_string() << "\"\n";

		std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Ograniczenie szybkoœci do 20 ticks/s.
	}
}

bool OnlineEngine::step() {
	std::lock_guard<std::mutex> lock(method_lock);
	return Engine::step();
}

unsigned int OnlineEngine::rollDice() {
	// Wysy³a wiadomoœæ z DICE_ROLL
	auto result = eventPublisher.send(zmq::buffer(constructMessage(EventType::DICE_ROLL, *localP)), zmq::send_flags::none);
	if (result.has_value())
		std::cout << result.value() << '\n';
	return dice.getLast();
}

bool OnlineEngine::connect(std::string addr) {
	if (localP == nullptr)
		return false;
	try {
		serverSubscriber.connect("tcp://" + addr + ":2000");
		eventPublisher.connect("tcp://" + addr + ":2001");
		auto t = eventPublisher.send(zmq::buffer(constructMessage(EventType::PLAYER_JOINED,*localP)), zmq::send_flags::none);
		if (t.has_value())
			std::cout << "Value: " << t.value() << '\n';
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
	if (online != nullptr) {
		onlineShouldWork = false;
		online->join();
		delete online;
	}
	//try {
	if (serverSubscriber)
		serverSubscriber.close();
	if (eventPublisher)
		eventPublisher.close();
	/*	}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
		}
		catch (...) {
			std::cerr << "Unknown exception in " << __FILE__ << " line: " << __LINE__ << '\n';
		}*/
}