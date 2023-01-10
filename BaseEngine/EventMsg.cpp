#include "EventMsg.hpp"


const char* currentTimestamp(char buf[], int bufflen) {
	time_t now = time(0);
	struct tm tstruct;
	localtime_s(&tstruct, &now);
	strftime(buf, bufflen, "%Y-%m-%d %X", &tstruct);
	return buf;
}