#include "OnlineEngine.hpp"

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
		Engine::start();
		std::cout << "Thread id: " << std::this_thread::get_id() << '\n';
		online = new std::thread([this] { run(); });
	}
}

// # IMPORTANT #
//FIXME: Zaimplementowaæ metodê run.
void OnlineEngine::run() {
	std::cout << "Thread id: " << std::this_thread::get_id() << '\n';
	std::cout << "It runs" << '\n';
}

bool OnlineEngine::step() {
	std::lock_guard<std::mutex> lock(method_lock); // <- Blokuje mutex dla bie¿¹cego kontekstu.
	return Engine::step();
}

unsigned int OnlineEngine::rollDice() {
	std::lock_guard<std::mutex> lock(method_lock); // <- Blokuje mutex dla bie¿¹cego kontekstu.
	return Engine::rollDice();
}

bool OnlineEngine::connect(std::string serverpub, std::string serversub) {
	if (localP == nullptr)
		return false;
	try {
		serverSubscriber.connect(serversub);
		eventPublisher.connect(serverpub);
		//		addr = server;
				//serverSubscriber.set(zmq::sockopt::subscribe, "events");
				//eventPublisher.send(zmq::str_buffer("NEW_PLAYERS"), zmq::send_flags::none);
		auto t = eventPublisher.send(zmq::buffer(localP->json()));
		std::cout << "Has value: " << t.has_value() << '\n';
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