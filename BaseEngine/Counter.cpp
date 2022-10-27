#include "Counter.hpp"
#ifdef _DEBUG
std::ostream& operator<< (std::ostream& os,const Counter& e) {
	os << "<Counter object " << std::hex << std::uppercase << &e << std::resetiosflags(std::ios_base::basefield) << ">: Id: " << e.id << " Owned by: " << e.ownedBy;
	
	return os;
}
#endif