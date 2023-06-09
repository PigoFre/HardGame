#pragma once

#include "DeadlockTypes.h"
#include "SimpleDeadlockDetector.h"
#include "FrozenDeadlockDetector.h"
#include "BipartiteDetector.h"
#include "ClosedDiagonalDetector.h"
#include "CorralDetector.h"

#include <unordered_set>

namespace cavepacker {

/**
 * @brief Checks whether the current board contains a deadlock. There are several deadlock situations.
 *
 * You can find more information at http://sokobano.de/wiki/index.php?title=Deadlocks and
 * http://sokobano.de/wiki/index.php?title=How_to_detect_deadlocks
 */
class DeadlockDetector {
private:
	SimpleDeadlockDetector _simple;
	FrozenDeadlockDetector _frozen;
	BipartiteDetector _bipartite;
	ClosedDiagonalDetector _closedDiagonal;
	CorralDetector _corral;

	uint32_t _start = { 0u };
public:
	/**
	 * @brief Call this whenever you want to reset the initialized data from previous runs
	 */
	void clear();
	void init(const BoardState& state);
	bool hasDeadlock(const BoardState& state, uint32_t timeout = 50u);
	DeadlockSet getDeadlocks() const;
};

}
