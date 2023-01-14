#include "EventMsg.hpp"
#define __STDC_WANT_LIB_EXT1__ 1

const char* currentTimestamp(char buf[], int bufflen) {
	time_t now = time(0);
	struct tm tstruct;
#ifdef __STDC_LIB_EXT1__
	localtime_s(&tstruct, &now);
#elif __UNIX__
	localtime_r(&now, &tstruct);
#else 
	localtime_s(&tstruct, &now);
#endif 
	strftime(buf, bufflen, "%Y-%m-%d %X", &tstruct);
	return buf;
}