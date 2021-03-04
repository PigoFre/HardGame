#pragma once

#include "SokobanTiles.h"
#include "deadlock/DeadlockDetector.h"
#include "common/Log.h"
#include <SDL_assert.h>
#include <vector>

namespace cavepacker {

#define MOVE_LEFT 'l'
#define MOVE_RIGHT 'r'
#define MOVE_UP 'u'
#define MOVE_DOWN 'd'

typedef std::vector<char> StateMap;

class BoardState {
private:
	StateMap _state;
	DeadlockDetector _deadlock;
	int _width = 0;
	int _height = 0;

public:
	BoardState();

	BoardState(const BoardState& state);

	/**
	 * @brief Clears the board state including the deadlocks - but not the size
	 */
	void clear();
	/**
	 * @brief Clears the board state but keeps the precalculated deadlocks
	 */
	void clearBoard();
	/**
	 * @brief Configures the size of the board.
	 */
	void setSize(int width, int height);
	/**
	 * @brief Checks whether the board is in a deadlock situation
	 */
	bool hasDeadlock();
	/**
	 * @brief There are some deadlock situations that are more or less fixed and can be
	 * precalculated at start. To do this, call this method once after everything is loaded.
	 */
	void initDeadlock();
	/**
	 * @brief Fills the board with fields
	 * @return @c false if there was already a field set on the given col/row
	 * @sa @c clear()
	 */
	bool setField(int col, int row, char field);
	bool setFieldForIndex(int index, char field);

	/**
	 * @brief Removed the given field from the board and returns the old value. If there wasn't any
	 * value on the specified field, @c '\0' is returned.
	 */
	char clearField(int col, int row);
	char clearFieldForIndex(int index);

	void getReachableIndices(int index, std::vector<int>& successors) const;

	/**
	 * @brief Checks whether the given field is free in a sense that the player
	 * could walk there if no obstacle is in the way
	 */
	bool isFree(int col, int row) const;
	bool isFree(int index) const;
	/**
	 * @brief Checks whether the given field is a target for a package. It checks all
	 * three available target types: empty target, package on target, player on target
	 */
	bool isTarget(int col, int row) const;
	/**
	 * @brief Checks whether the given field is a package. It checks all available package
	 * types: normal package, package on target
	 */
	bool isPackage(int col, int row) const;
	/**
	 * @brief Checks whether the current state is done. That means that all the packages must be
	 * on a target.
	 */
	bool isDone() const;

	std::string toString() const;

	inline StateMap::const_iterator begin() const {
		return _state.begin();
	}

	inline StateMap::const_iterator end() const {
		return _state.end();
	}

	inline const DeadlockDetector& getDeadlockDetector () const {
		return _deadlock;
	}

	/**
	 * @param[out] col [0, w - 1]
	 * @param[out] row [0, h - 1]
	 * @return @c false if the conversion failed because the index isn't part of the board
	 */
	inline bool getColRowFromIndex(int index, int& col, int& row) const {
		if (index < 0 || index >= size())
			return false;
		if (_state[index] == '\0')
			return false;
		col = index % _width;
		row = index / _width;
		return true;
	}

	inline int size() const {
		return (int)_state.size();
	}

	/**
	 * @param[in] col [0, w - 1]
	 * @param[in] row [0, h - 1]
	 */
	inline int getIndex(int col, int row) const {
		SDL_assert_always(row < _height);
		SDL_assert_always(col < _width);
		return col + _width * row;
	}

	inline int getWidth() const {
		return _width;
	}

	inline int getHeight() const {
		return _height;
	}

	/**
	 * @brief Returns the field id for the given col and row. If the col and row is not
	 * part of the map, a @c \0 is returned.
	 */
	inline char getField(int col, int row) const {
		const int index = getIndex(col, row);
		return _state[index];
	}

	inline char getFieldByIndex(int index) const {
		return _state[index];
	}

	/**
	 * @brief If the given col and row indices are not known to the state object this is returning @c false.
	 *
	 * @note Even fields that are within the board dimensions might be invalid because they are outside of the map
	 */
	inline bool isInvalid(int col, int row) const {
		const int index = getIndex(col, row);
		return _state[index] == '\0';
	}
};

/**
 * @brief Get the relative col and row for a given direction
 * @param[in] step The direction to move into
 * @param[out] x the relative col (e.g. -1 for moving left)
 * @param[out] y the relative row (e.g. -1 for moving up)
 */
inline void getXY(char step, int& x, int& y) {
	switch (tolower(step)) {
	case MOVE_LEFT:
		x = -1;
		y = 0;
		break;
	case MOVE_RIGHT:
		x = 1;
		y = 0;
		break;
	case MOVE_UP:
		x = 0;
		y = -1;
		break;
	case MOVE_DOWN:
		x = 0;
		y = 1;
		break;
	default:
		x = 0;
		y = 0;
		break;
	}
}

/**
 * @brief Get the relative col and row for a given direction and invert it
 * @param[in] step The direction to move into
 * @param[out] x the relative col (e.g. 1 for moving left)
 * @param[out] y the relative row (e.g. 1 for moving up)
 */
inline void getOppositeXY(char step, int& x, int& y) {
	getXY(step, x, y);
	x *= -1;
	y *= -1;
}

inline char BoardState::clearField(int col, int row) {
	const int index = getIndex(col, row);
	return clearFieldForIndex(index);
}

inline bool BoardState::setField(int col, int row, char field) {
	const int index = getIndex(col, row);
	return setFieldForIndex(index, field);
}

inline bool BoardState::setFieldForIndex(int index, char field) {
	if (_state[index] != '\0')
		return false;
	_state[index] = field;
	return true;
}

}
