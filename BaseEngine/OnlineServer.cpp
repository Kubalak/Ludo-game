#include "OnlineServer.hpp"
#include <zmq_addon.hpp>

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
//FIXME: Zaimplementowaæ metodê run.
void OnlineServer::run() {
	std::vector<zmq::message_t> messages;
	while (onlineShouldWork) {
		zmq::message_t message;
		zmq::recv_result_t result = zmq::recv_multipart(serverSocketSubscriber,std::back_inserter(messages));
		if(result.has_value())
			std::cout << "Value: " << result.value() << '\n';
		
		std::cout << messages[0].to_string() << '\n';
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

bool OnlineServer::bind(std::string pubaddr, std::string subaddr) {
	try {
		serverSocketPublisher.bind(pubaddr);
		serverSocketSubscriber.bind(subaddr);
		//serverSocketSubscriber.set(zmq::sockopt::subscribe, "");
		std::cout << "Server is available at " << pubaddr << " (sub) " << subaddr << " (pub)\n";
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
	if (serverSocketPublisher)
		serverSocketPublisher.close();
	if (serverSocketSubscriber)
		serverSocketSubscriber.close();
}