#include "OnlineServer.hpp"
#include "EventMsg.hpp"
#include <zmq_addon.hpp>
#include <ctime>


OnlineServer::OnlineServer() :
	onlineShouldWork(true) {
	serverSocketSubscriber = zmq::socket_t(context, zmq::socket_type::pull);
	serverSocketPublisher = zmq::socket_t(context, zmq::socket_type::push);
}

bool OnlineServer::move(int fieldNo) {
	std::lock_guard<std::mutex> lock(method_lock); // <- Blokuje mutex dla bie¿¹cego kontekstu.
	return Engine::move(fieldNo);
}

bool OnlineServer::addPlayer(Player* player, unsigned int quarter) {
	std::lock_guard<std::mutex> lock(method_lock); // <- Blokuje mutex dla bie¿¹cego kontekstu.
	return Engine::addPlayer(player, quarter);
}

void OnlineServer::start() {
	if (state == EngineStates::CREATED) {
		//Engine::start();
		run();
	}
}

// # IMPORTANT #
//TODO: Zaimplementowaæ metodê run.
void OnlineServer::run() {
	char buf[80];
	while (onlineShouldWork) {
		zmq::message_t message;
		zmq::recv_result_t result = serverSocketSubscriber.recv(message, zmq::recv_flags::none);
		if (result.has_value())
			std::cout << "[" << currentTimestamp(buf,80) << "]:" << message.to_string() << '\n';
			//std::cout << "Value: " << result.value() << '\n';
		serverSocketPublisher.send(zmq::buffer("Reply message"), zmq::send_flags::none);
	}
}

bool OnlineServer::step() {
	std::lock_guard<std::mutex> lock(method_lock); // <- Blokuje mutex dla bie¿¹cego kontekstu.
	return Engine::step();
}

unsigned int OnlineServer::rollDice() {
	std::lock_guard<std::mutex> lock(method_lock); // <- Blokuje mutex dla bie¿¹cego kontekstu.
	return Engine::rollDice();
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