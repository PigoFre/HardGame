#pragma once

#include "engine/common/IMapContext.h"
#include <string>

namespace Sokuban {
const int WALL = '#';
const int PLAYER = '@';
const int PACKAGE = '$';
const int TARGET = '.';
const int GROUND = ' ';
const int PACKAGEONTARGET = '*';
const int PLAYERONTARGET = '+';
}

class SokubanMapContext : public IMapContext {
private:
	bool _playerSpawned;

	void addPlayer(int col, int row);
	void addWall(int col, int row);
	void addGround(int col, int row);
	void addPackage(int col, int row);
	void addTarget(int col, int row);
	void addTile(const std::string& tile, int col, int row);
	bool isEmpty(int col, int row) const;
public:
	SokubanMapContext(const std::string& map);
	virtual ~SokubanMapContext();

	// IMapContext
	void onMapLoaded () override;
	bool load (bool skipErrors) override;
	bool save () const override { return false; }
};
