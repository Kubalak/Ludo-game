#include "Counter.hpp"

void Counter::move(int moves) {
	if (static_cast<int>(movesNo) + moves < 0)
		movesNo = 0;
	movesNo += moves;
}