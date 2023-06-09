#pragma once

#include <caveexpress/shared/CaveExpressMapContext.h>
#include "common/EntityType.h"
#include "common/ThemeType.h"
#include "common/Compiler.h"

// forward decl
class SpriteDef;

namespace caveexpress {

typedef unsigned int randomGridCoord;
typedef unsigned int randomGridSize;

struct RandomMapPos {
	randomGridCoord x, y;
};

// this context will generate a randomly assembled map
// there are some assumptions that you should be aware of:
// * each solid and background tile must be grid aligned
// * each solid and background tile can't have a fractional part for their width and height
class RandomMapContext: public CaveExpressMapContext {
private:
	// the amount of caves
	unsigned int _caves;
	// place these amount of rock tiles randomly in the map
	const unsigned int _randomRockTiles;
	// place these rock tiles around the randomly placed rock tiles
	const unsigned int _overallRockAmount;
	// the width of the map
	const unsigned int _mapWidth;
	// the height of the map
	const unsigned int _mapHeight;
	SpriteDef** const _map;
	float _waterHeight;

	std::vector<SpriteDefPtr> _groundTiles;
	std::vector<SpriteDefPtr> _solidTiles;
	std::vector<SpriteDefPtr> _backgroundTiles;
	std::vector<SpriteDefPtr> _caveTiles;
	std::vector<SpriteDefPtr> _bridgeTiles;
	std::vector<SpriteDefPtr> _windowTiles;
	std::vector<RandomMapPos> _groundPos;
	std::vector<RandomMapPos> _playerPos;
	std::vector<CaveTileDefinition> _caveDefinitions;

	bool rndAddTile (const SpriteDefPtr& def, randomGridCoord x, randomGridCoord y);
	bool rndAddCave (const SpriteDefPtr& def, randomGridCoord x, randomGridCoord y, const EntityType& type, int delay);
	bool rndAddEmitter (randomGridCoord x, randomGridCoord y, const EntityType& entityType, randomGridSize width, randomGridSize height);
	bool rndAddGroundTile (randomGridCoord x, randomGridCoord y);

	void fillMap (const SpriteDefPtr& def, randomGridCoord x, randomGridCoord y);

	// checks whether every free tile is reachable from every other free tile
	bool checkFreeTiles (const SpriteDefPtr& def, randomGridCoord x, randomGridCoord y);

	inline bool isFree (randomGridCoord x, randomGridCoord y) const;
	// returns the placed sprite definition on the given grid coordinates - or nullptr if there is none yet
	inline const SpriteDef* getFromGridPos (randomGridCoord x, randomGridCoord y) const;
	bool checkPassage (randomGridCoord x, randomGridCoord y, randomGridSize width, randomGridSize height) const;
	bool checkPassage (randomGridCoord x, randomGridCoord y, const SpriteDefPtr& def) const;
	inline bool isFree (randomGridCoord x, randomGridCoord y, randomGridSize width, randomGridSize height) const;
	inline bool isFree (randomGridCoord x, randomGridCoord y, const SpriteDefPtr& def) const;
	// checks whether there is enough ground available to place an entity of the given size to the give ground position
	inline bool isEnoughGround (randomGridCoord x, randomGridCoord y, randomGridSize width, randomGridSize height) const;
	// get the left and right boundaries for a ground tile at the given grid coordinates - returns false if the
	// given y level does not contain any ground tiles
	bool getGroundDimensions (randomGridCoord x, randomGridCoord y, randomGridCoord& left, randomGridCoord& right) const;
	// checks whether a tile of the given sprite type is on the y grid axis between left and right
	bool isTileAt (const SpriteType& def, randomGridCoord left, randomGridCoord right, randomGridCoord y) const;

	bool placeInitialRandomTiles ();
	void placeTilesAroundInitialTiles ();
	void placeGroundTiles ();
	void placeBridges ();
	int placeCaveTiles ();

	bool fullSize (const SpriteDefPtr& def) const;

	void findValidPlayerStartingPositionsAndFillBackground ();

	void placeEmitterTiles ();
	// some emitters needs to be placed on a ground tile (e.g. trees)
	bool placeEmitterGroundTile (const EntityType& entityType);
	// place emitters that are able to fall down - just place them in a free slot
	bool placeEmitterTile (const EntityType& entityType);

public:
	// valid themes are currently rock and ice
	RandomMapContext (const std::string& name, const ThemeType& theme, unsigned int randomRockTiles,
			unsigned int overallRockAmount, unsigned int width, unsigned int height);
	virtual ~RandomMapContext ();

	void setSettings (const IMap::SettingsMap& settings);
	void setFlyingNPC (bool flyingNPC);
	void setWind (float wind);
	void setCaves (unsigned int caves);
	void setWaterParameters (float waterHeight, float waterChangeSpeed, uint32_t waterRisingDelay, uint32_t waterFallingDelay);

	// IMapContext
	bool load (bool skipErrors) override;
};

}
