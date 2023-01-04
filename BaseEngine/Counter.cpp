#include "Counter.hpp"
std::ostream& operator<< (std::ostream& os, const Counter& e) {

	os << "{\"id\":" << std::to_string(e.id) << ",\"ownedBy\":" << std::to_string(e.ownedBy) << "}";
	return os;
}

std::string Counter::str() {
	std::stringstream ss;
	ss << "<Counter object " << std::hex << std::uppercase << this << std::resetiosflags(std::ios_base::basefield) << ">: Id: " << id << " Owned by: " << ownedBy;
	return ss.str();
}


std::string Counter::json() {
	return "{\"id\":" + std::to_string(id) + ",\"ownedBy\":" + std::to_string(ownedBy) + "}";
}