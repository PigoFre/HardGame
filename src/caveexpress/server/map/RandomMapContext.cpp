#include "RandomMapContext.h"
#include "common/MapSettings.h"
#include "common/KeyValueParser.h"
#include "common/EntityType.h"
#include "common/Animation.h"
#include "caveexpress/shared/constants/EmitterSettings.h"
#include "caveexpress/shared/CaveExpressEntityType.h"
#include "caveexpress/shared/CaveExpressSpriteType.h"
#include "caveexpress/shared/CaveExpressAnimation.h"
#include "common/SpriteDefinition.h"
#include "common/FileSystem.h"
#include "common/String.h"
#include "common/Log.h"
#include "common/TextureDefinition.h"

#include <algorithm>
#include <SDL_assert.h>
#include <math.h>

namespace caveexpress {

namespace {
const int directions[][2] = { { 0, -1 }, { 0, 1 }, { 1, 0 }, { -1, 0 }, { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 } };
const int directionLength = sizeof(directions) / sizeof(directions[0]);
const int baseDirections = 4;
}

struct MapTileDefinitionSorter {
	inline bool operator() (const MapTileDefinition& md1, const MapTileDefinition& md2)
	{
		const randomGridCoord val1 = md1.x * 10000 + md1.y;
		const randomGridCoord val2 = md2.x * 10000 + md2.y;
		return val1 < val2;
	}
};

struct RandomMapPosXSorter {
	inline bool operator() (const RandomMapPos& pos1, const RandomMapPos& pos2)
	{
		return pos1.x < pos2.x;
	}
};

#define getGridSize(x) std::max(1.0f, x) + 0.0001f
#define gridGetVoid(x) (reinterpret_cast<void*>(*reinterpret_cast<intptr_t*>(&x)))

RandomMapContext::RandomMapContext (const std::string& name, const ThemeType& theme, unsigned int randomRockTiles,
		unsigned int overallRockAmount, unsigned int width, unsigned int height) :
		CaveExpressMapContext(name), _caves(5), _randomRockTiles(randomRockTiles), _overallRockAmount(overallRockAmount), _mapWidth(
				width), _mapHeight(height), _map(new SpriteDef*[_mapWidth * _mapHeight])
{
	_theme = &theme;
	Log::info(LOG_GAMEIMPL, "random map size: %i:%i", width, height);
	_settings[msn::WIDTH] = string::toString(width);
	_settings[msn::HEIGHT] = string::toString(height);

	setFlyingNPC(true);
	setWind(0.0f);
	setWaterParameters(1.0f, 0.1f, 10000L, 10000L);
	_settings[msn::GRAVITY] = string::toString(msdv::GRAVITY);

	for (SpriteDefMapConstIter i = SpriteDefinition::get().begin(); i != SpriteDefinition::get().end(); ++i) {
		const SpriteDefPtr& def = i->second;
		const SpriteType& type = def->type;
		if (!SpriteTypes::isMapTile(type))
			continue;

		if (!def->theme.isNone() && def->theme != theme)
			continue;

		if (SpriteTypes::isRock(type) && fullSize(def))
			_solidTiles.push_back(def);
		else if (SpriteTypes::isBackground(type))
			_backgroundTiles.push_back(def);
		else if (SpriteTypes::isCave(type))
			_caveTiles.push_back(def);
		else if (SpriteTypes::isBridge(type))
			_bridgeTiles.push_back(def);
		else if (SpriteTypes::isGround(type) && fullSize(def))
			_groundTiles.push_back(def);
		else if (SpriteTypes::isWindow(type))
			_windowTiles.push_back(def);
	}
	Log::info(LOG_GAMEIMPL, "%i solid tiles", (int)_solidTiles.size());
	Log::info(LOG_GAMEIMPL, "%i ground tiles", (int)_groundTiles.size());
	Log::info(LOG_GAMEIMPL, "%i background tiles", (int)_backgroundTiles.size());
	Log::info(LOG_GAMEIMPL, "%i window tiles", (int)_windowTiles.size());
	Log::info(LOG_GAMEIMPL, "%i cave tiles", (int)_caveTiles.size());
}

RandomMapContext::~RandomMapContext ()
{
	delete[] _map;
}

bool RandomMapContext::fullSize (const SpriteDefPtr& def) const
{
	if (def->hasShape()) {
		return false;
	}
	const float width = def->width;
	const float height = def->height;
	float integralPart;
	const float w = ::modff(width, &integralPart);
	const float h = ::modff(height, &integralPart);
	return w < 0.00001f || h < 0.00001f;
}

void RandomMapContext::setSettings (const IMap::SettingsMap& settings)
{
	for (IMap::SettingsMapConstIter i = settings.begin(); i != settings.end(); ++i) {
		_settings[i->first] = i->second;
	}
}

bool RandomMapContext::isTileAt (const SpriteType& def, randomGridCoord left, randomGridCoord right, randomGridCoord y) const
{
	for (std::vector<MapTileDefinition>::const_iterator i = _definitions.begin(); i != _definitions.end(); ++i) {
		const MapTileDefinition& mapDef = *i;
		if (mapDef.spriteDef->type != def) {
			continue;
		}
		const randomGridCoord ry = getGridSize(mapDef.y);
		const randomGridCoord rx = getGridSize(mapDef.x);
		if (ry != y) {
			continue;
		}
		if (rx < left || rx > right) {
			continue;
		}
		return true;
	}
	return false;
}

bool RandomMapContext::checkFreeTiles (const SpriteDefPtr& def, randomGridCoord x, randomGridCoord y)
{
	randomGridCoord startState;
	const randomGridSize width = getGridSize(def->width);
	const randomGridSize height = getGridSize(def->height);
	for (startState = 0; startState < _mapWidth * _mapHeight; ++startState) {
		const randomGridCoord nx = startState % _mapWidth;
		const randomGridCoord ny = startState / _mapWidth;
		if (nx >= x && nx < x + width && ny >= y && ny < y + height)
			continue;
		if (isFree(nx, ny))
			break;
	}
	if (startState == _mapWidth * _mapHeight) {
		Log::error(LOG_GAMEIMPL, "no free slot found");
		return false;
	}

	return true;
}

inline void RandomMapContext::fillMap (const SpriteDefPtr& def, randomGridCoord x, randomGridCoord y)
{
	const randomGridSize width = getGridSize(def->width);
	const randomGridSize height = getGridSize(def->height);
	for (randomGridSize w = 0; w < width; ++w) {
		for (randomGridSize h = 0; h < height; ++h) {
			const int index = (x + w) + ((y + h) * _mapWidth);
			SDL_assert(_map[index] == nullptr);
			_map[index] = def.get();
		}
	}
}

bool RandomMapContext::rndAddTile (const SpriteDefPtr& def, randomGridCoord x, randomGridCoord y)
{
	const SpriteType& type = def->type;
	SDL_assert(!SpriteTypes::isCave(type));
	if (x >= _mapWidth || y >= _mapHeight) {
		return false;
	}

	// tile does not fit
	if (!isFree(x, y, def)) {
		return false;
	}

	if (SpriteTypes::isRock(type)) {
		if (!checkPassage(x, y, def))
			return false;
	} else if (SpriteTypes::isBridgeLeft(type)) {
		if (!isFree(x + 1, y)) {
			const SpriteDef *defBeside = getFromGridPos(x + 1, y);
			if (!SpriteTypes::isBridgePlank(defBeside->type) && !SpriteTypes::isBridgeRight(defBeside->type))
				return false;
		}
	} else if (SpriteTypes::isBridgeRight(type)) {
		if (!isFree(x - 1, y)) {
			const SpriteDef *defBeside = getFromGridPos(x + 1, y);
			if (!SpriteTypes::isBridgePlank(defBeside->type) && !SpriteTypes::isBridgeLeft(defBeside->type))
				return false;
		}
	} else if (SpriteTypes::isAnyGround(type)) {
		if (y == 0) {
			return false;
		} else if (!isFree(x, y - 1, def)) {
			return false;
		}

		if (SpriteTypes::isGroundLeft(type) || SpriteTypes::isGroundRight(type)) {
			// the tile below a ground should not be free
			if (!isFree(x, y + 1, def))
				return false;

			if (!checkPassage(x, y, def))
				return false;

			if (SpriteTypes::isGroundLeft(type)) {
				// the tile left to the ground should be free if we place a left or right end
				if (!isFree(x - 1, y, def)) {
					return false;
				}
				// they should not be placed next to each other
				const SpriteDef *groundEdgeDef = getFromGridPos(x + 1, y);
				if (groundEdgeDef != nullptr) {
					if (SpriteTypes::isGroundLeft(groundEdgeDef->type) || SpriteTypes::isGroundRight(groundEdgeDef->type)) {
						return false;
					}
				}
			} else {
				// the tile left to the ground should be free if we place a left or right end
				if (!isFree(x + 1, y, def)) {
					return false;
				}
				// they should not be placed next to each other
				const SpriteDef *groundEdgeDef = getFromGridPos(x - 1, y);
				if (groundEdgeDef != nullptr) {
					if (SpriteTypes::isGroundLeft(groundEdgeDef->type) || SpriteTypes::isGroundRight(groundEdgeDef->type)) {
						return false;
					}
				}
			}
		}
	}

	if (!_definitions.empty() && SpriteTypes::isSolid(type) && !checkFreeTiles(def, x, y)) {
		return false;
	}

	const MapTileDefinition mapTileDef(static_cast<gridCoord>(x), static_cast<gridCoord>(y), def, 0);
	_definitions.push_back(mapTileDef);
	fillMap(def, x, y);

	Log::debug(LOG_GAMEIMPL, "placed tile %s at %i:%i", def->id.c_str(), x, y);

	return true;
}

bool RandomMapContext::rndAddCave (const SpriteDefPtr& def, randomGridCoord x, randomGridCoord y, const EntityType& type, int delay)
{
	if (x >= _mapWidth || y >= _mapHeight) {
		return false;
	}

	// tile does not fit
	if (!isFree(x, y, def)) {
		return false;
	}

	randomGridCoord left;
	randomGridCoord right;
	if (!getGroundDimensions(x, y + 1, left, right))
		return false;

	if (isTileAt(SpriteTypes::CAVE, left, right, y))
		return false;

	const CaveTileDefinition caveTileDef(static_cast<gridCoord>(x), static_cast<gridCoord>(y), def, type, delay);
	_caveDefinitions.push_back(caveTileDef);
	fillMap(def, x, y);
	Log::debug(LOG_GAMEIMPL, "placed cave %s at %i:%i", def->id.c_str(), x, y);

	return true;
}

bool RandomMapContext::rndAddEmitter (randomGridCoord x, randomGridCoord y, const EntityType& entityType, randomGridSize width, randomGridSize height)
{
	for (std::vector<EmitterDefinition>::const_iterator i = _emitters.begin(); i != _emitters.end(); ++i) {
		const EmitterDefinition& def = *i;
		for (randomGridSize w = 0; w < width; ++w)
			for (randomGridSize h = 0; h < height; ++h) {
				const randomGridCoord rx = getGridSize(def.x);
				const randomGridCoord ry = getGridSize(def.y);
				if (rx == x + w && ry == y + h)
					return false;
			}
	}
	const EmitterDefinition def(static_cast<gridCoord>(x), static_cast<gridCoord>(y), entityType, 1, -1, "");
	_emitters.push_back(def);
	return true;
}

void RandomMapContext::setWind (float wind)
{
	_settings[msn::WIND] = string::toString(wind);
}

void RandomMapContext::setCaves (unsigned int caves)
{
	_caves = caves;
}

void RandomMapContext::setFlyingNPC (bool flyingNPC)
{
	_settings[msn::FLYING_NPC] = string::toString(flyingNPC);
}

void RandomMapContext::setWaterParameters (float waterHeight, float waterChangeSpeed,
		uint32_t waterRisingDelay, uint32_t waterFallingDelay)
{
	_waterHeight = waterHeight;
	_settings[msn::WATER_HEIGHT] = string::toString(waterHeight);
	_settings[msn::WATER_CHANGE] = string::toString(waterChangeSpeed);
	_settings[msn::WATER_RISING_DELAY] = string::toString(waterRisingDelay);
	_settings[msn::WATER_FALLING_DELAY] = string::toString(waterFallingDelay);
}

bool RandomMapContext::placeInitialRandomTiles ()
{
	unsigned int tries = 0;
	for (unsigned int i = 0; i < _randomRockTiles; ++i) {
		const randomGridCoord x = rand() % _mapWidth;
		randomGridCoord y = rand() % _mapHeight;
		if (y < 3)
			y = 3;
		else if (y > _mapHeight - 2)
			y = _mapHeight - 2;
		const int index = rand() % _solidTiles.size();
		const SpriteDefPtr& def = _solidTiles[index];
		if (!rndAddTile(def, x, y)) {
			// could not add the tile
			--i;
			++tries;
			if (tries > _randomRockTiles * 4) {
				return false;
			}
		} else {
			Log::info(LOG_GAMEIMPL, "placed initial tile '%s' at %u:%u", def->id.c_str(), x, y);
			tries = 0;
		}
	}
	return true;
}

void RandomMapContext::placeTilesAroundInitialTiles ()
{
	unsigned int tries = 0;
	unsigned int overallTilesAmount = _overallRockAmount;

	SDL_assert(!_definitions.empty());

	std::vector<MapTileDefinition> definitions = _definitions;
	while (overallTilesAmount > 0) {
		std::random_shuffle(definitions.begin(), definitions.end());
		for (std::vector<MapTileDefinition>::const_iterator i = definitions.begin(); i != definitions.end(); ++i) {
			const MapTileDefinition& mapDef = *i;
			const int random = rand();
			const int randomDir = random % baseDirections;
			const int index = random % _solidTiles.size();
			const SpriteDefPtr& def = _solidTiles[index];
			for (unsigned int step = 1; step <= 2; ++step) {
				const randomGridCoord x = mapDef.x + directions[randomDir][0] * step;
				const randomGridCoord y = mapDef.y + directions[randomDir][1] * step;
				if (y < 3)
					continue;
				if (rndAddTile(def, x, y)) {
					--overallTilesAmount;
					break;
				}
			}
			++tries;
		}
		if (tries > _overallRockAmount * 80)
			break;
	}
}

bool RandomMapContext::rndAddGroundTile (randomGridCoord x, randomGridCoord y)
{
	if (!isFree(x, y)) {
		return false;
	}

	const int size = rand() % _groundTiles.size();
	std::vector<SpriteDefPtr>::iterator i = _groundTiles.begin();
	std::advance(i, size);
	const std::vector<SpriteDefPtr>::iterator r = i;
	for (; i != _groundTiles.end(); ++i) {
		const SpriteDefPtr& def = *i;
		if (rndAddTile(def, x, y)) {
			const RandomMapPos p = { x, y };
			_groundPos.push_back(p);
			return true;
		}
	}
	i = _groundTiles.begin();
	for (; i != r; ++i) {
		const SpriteDefPtr& def = *i;
		if (rndAddTile(def, x, y)) {
			const RandomMapPos p = { x, y };
			_groundPos.push_back(p);
			return true;
		}
	}

	return false;
}

void RandomMapContext::placeGroundTiles ()
{
	std::vector<MapTileDefinition> definitions = _definitions;
	std::sort(definitions.begin(), definitions.end(), MapTileDefinitionSorter());
	for (std::vector<MapTileDefinition>::const_iterator i = definitions.begin(); i != definitions.end(); ++i) {
		const MapTileDefinition& mapDef = *i;
		const randomGridCoord x = mapDef.x;
		const randomGridCoord y = mapDef.y;
		if (y < 3)
			continue;

		const int width = mapDef.spriteDef->width;
		for (int j = 0; j < width; ++j) {
			const randomGridCoord x1 = j + x;
			if (isFree(x1, y - 2))
				continue;
			if (isFree(x1 - 1, y - 2))
				continue;
			if (isFree(x1 + 1, y - 2))
				continue;
			rndAddGroundTile(x1, y - 1);
		}
		const int r = rand() % 4;
		if (r & 1)
			rndAddGroundTile(x - 1, y - 1);
		if (r & 2)
			rndAddGroundTile(x + width, y - 1);
	}
}

void RandomMapContext::placeBridges ()
{
	// TODO
#if 0
	for (std::vector<MapTileDefinition>::const_iterator i = _definitions.begin(); i != _definitions.end();) {
		const MapTileDefinition& mapDef = *i;
		const randomGridCoord x = mapDef.x;
		const randomGridCoord y = mapDef.y;
		if (mapDef.spriteDef->type.isBackground()) {

		}
	}
#endif
}

int RandomMapContext::placeCaveTiles ()
{
	int caves = 0;
	unsigned int tries = 0;
	for (unsigned int i = 0; i < _caves; ++tries) {
		const int groundPosIndex = rand() % _groundPos.size();
		const RandomMapPos& p = _groundPos[groundPosIndex];
		const int index = rand() % _caveTiles.size();
		const SpriteDefPtr& def = _caveTiles[index];
		const randomGridCoord y = p.y - 1;
		const int delayMs = 1000;
		if (rndAddCave(def, p.x, y, EntityType::NONE, delayMs)) {
			++caves;
			const int windowIndex = rand() % _windowTiles.size();
			const SpriteDefPtr& windowDef = _windowTiles[windowIndex];
			rndAddTile(windowDef, p.x + 1, y) || rndAddTile(windowDef, p.x - 1, y);
			++i;
		}

		if (tries > 100)
			break;
	}

	return caves;
}

void RandomMapContext::placeEmitterTiles ()
{
	placeEmitterGroundTile(EntityTypes::STONE);
	placeEmitterGroundTile(EntityTypes::TREE);
	placeEmitterGroundTile(EntityTypes::NPC_WALKING);
	placeEmitterGroundTile(EntityTypes::NPC_BLOWING);
	placeEmitterGroundTile(EntityTypes::NPC_MAMMUT);
	const bool packageTarget = placeEmitterGroundTile(ThemeTypes::isIce(*_theme) ? EntityTypes::PACKAGETARGET_ICE : EntityTypes::PACKAGETARGET_ROCK);
	if (packageTarget)
		placeEmitterTile(EntityTypes::PACKAGE_ROCK);
}

bool RandomMapContext::placeEmitterTile (const EntityType& entityType)
{
	const Animation& animation = EntityTypes::hasDirection(entityType) ? Animations::ANIMATION_IDLE_RIGHT : Animations::ANIMATION_IDLE;
	const SpriteDefPtr& def = SpriteDefinition::get().getFromEntityType(entityType, animation);
	if (!def)
		return false;
	const randomGridSize width = def->width;
	const randomGridSize height = def->height;
	const randomGridCoord startX = rand() % _mapWidth;
	const randomGridCoord startY = rand() % _mapHeight;
	for (randomGridSize w = 0; w < _mapWidth; ++w) {
		const randomGridCoord _x = (w + startX) % _mapWidth;
		for (randomGridSize h = 0; h < _mapHeight; ++h) {
			const randomGridCoord _y = (h + startY) % _mapHeight;
			if (!isFree(_x, _y, width, height) || !rndAddEmitter(_x, _y, entityType, width, height))
				continue;

			return true;
		}
	}
	return false;
}

bool RandomMapContext::placeEmitterGroundTile (const EntityType& entityType)
{
	if (_groundPos.empty())
		return false;

	const Animation& animation = EntityTypes::hasDirection(entityType) ? Animations::ANIMATION_IDLE_RIGHT : Animations::ANIMATION_IDLE;
	const SpriteDefPtr& def = SpriteDefinition::get().getFromEntityType(entityType, animation);
	if (!def)
		return false;
	const randomGridSize width = getGridSize(def->width);
	const randomGridSize height = getGridSize(def->height);
	const int groundPosIndex = rand() % _groundPos.size();
	int groundPosIndexInner = groundPosIndex;
	for (;;) {
		const RandomMapPos& p = _groundPos[groundPosIndexInner];
		if (p.y <= 1 || !isFree(p.x, p.y - 1, width, height) || !isEnoughGround(p.x, p.y, width, height)
				|| !rndAddEmitter(p.x, p.y - height, entityType, width, height)) {
			++groundPosIndexInner;
			groundPosIndexInner %= _groundPos.size();
			// unable to place anything?
			if (groundPosIndexInner == groundPosIndex)
				break;

			continue;
		}

		return true;
	}

	return false;
}

void RandomMapContext::findValidPlayerStartingPositionsAndFillBackground ()
{
	for (randomGridCoord x = 0; x < _mapWidth; ++x) {
		for (randomGridCoord y = 0; y < _mapHeight; ++y) {
			if (!isFree(x, y))
				continue;

			bool success = false;
			do {
				const int index = rand() % _backgroundTiles.size();
				const SpriteDefPtr& def = _backgroundTiles[index];
				success = rndAddTile(def, x, y);
				if (success && y < _mapHeight - _waterHeight) {
					const RandomMapPos p = { x, y };
					_playerPos.push_back(p);
				}
			} while (!success);
		}
	}

	if (_playerPos.empty())
		return;

	if (!_startPositions.empty())
		return;

	const int playerPosIndex = rand() % _playerPos.size();
	const RandomMapPos& p = _playerPos[playerPosIndex];
	const IMap::StartPosition startPos{string::toString(p.x), string::toString(p.y)};
	_startPositions.push_back(startPos);
}

bool RandomMapContext::load (bool skipErrors)
{
	resetTiles();

	if (_solidTiles.size() == 0) {
		Log::error(LOG_GAMEIMPL, "no solid tiles available");
		return false;
	}

	if (_mapWidth == 0 || _mapHeight == 0) {
		Log::error(LOG_GAMEIMPL, "no width or height set for the random map");
		return false;
	}

	memset(_map, 0, sizeof(SpriteDef*) * _mapWidth * _mapHeight);

	if (_randomRockTiles == 0) {
		Log::error(LOG_GAMEIMPL, "no initial random rock tiles");
		return false;
	}

	if (_randomRockTiles >= _mapWidth * _mapHeight) {
		Log::error(LOG_GAMEIMPL, "map is too small for the initial solid tiles setting");
		return false;
	}

	if (!placeInitialRandomTiles()) {
		Log::error(LOG_GAMEIMPL, "could not place the initial tiles");
		return false;
	}
	placeTilesAroundInitialTiles();
	placeGroundTiles();
	placeBridges();

	if (_groundPos.empty()) {
		Log::error(LOG_GAMEIMPL, "no valid spots to place a cave on were found");
		if (!skipErrors)
			return false;
	}

	const int caves = _groundPos.empty() ? 0 : placeCaveTiles();
	if (caves < 1) {
		Log::error(LOG_GAMEIMPL, "could not create random map - not enough caves were placed");
		if (!skipErrors)
			return false;
	}
	findValidPlayerStartingPositionsAndFillBackground();
	placeEmitterTiles();

	if (_playerPos.empty()) {
		Log::error(LOG_GAMEIMPL, "no valid player positions found");
		if (!skipErrors)
			return false;
	}

	return true;
}

bool RandomMapContext::isFree (randomGridCoord x, randomGridCoord y) const
{
	if (y >= _mapHeight)
		return false;
	if (x >= _mapWidth)
		return false;
	return getFromGridPos(x, y) == nullptr;
}

const SpriteDef *RandomMapContext::getFromGridPos (randomGridCoord x, randomGridCoord y) const
{
	if (y >= _mapHeight)
		return nullptr;
	if (x >= _mapWidth)
		return nullptr;
	return _map[x + _mapWidth * y];
}

bool RandomMapContext::checkPassage (randomGridCoord x, randomGridCoord y, const SpriteDefPtr& def) const
{
	const randomGridSize width = getGridSize(def->width);
	const randomGridSize height = getGridSize(def->height);
	return checkPassage(x, y, width, height);
}

bool RandomMapContext::checkPassage (randomGridCoord x, randomGridCoord y, randomGridSize width, randomGridSize height) const
{
	for (int i = 0; i < directionLength; ++i) {
		const randomGridCoord nx = x + directions[i][0] + ((directions[i][0] > 0) ? 1 - width : 0);
		const randomGridCoord ny = y + directions[i][1] + ((directions[i][1] > 0) ? 1 - height : 0);
		Log::debug(LOG_GAMEIMPL, "check %i:%i with size %i:%i with %i:%i", x, y, width, height, nx, ny);
		if (ny >= _mapHeight || nx >= _mapWidth)
			break;
		if (!isFree(nx, ny))
			continue;
		// go one step further and check for a solid tile - then it's not allowed
		const randomGridCoord _nx = nx + directions[i][0];
		const randomGridCoord _ny = ny + directions[i][1];
		if (_ny >= _mapHeight || _nx >= _mapWidth)
			break;
		if (!isFree(_nx, _ny))
			return false;
		// we have to check for even 3 tiles in the upwards direction, because the ground tiles are placed here, too
		if (directions[i][1] < 0) {
			const randomGridCoord __nx = _nx + directions[i][0];
			const randomGridCoord __ny = _ny + directions[i][1];
			if (__ny >= _mapHeight || __nx >= _mapWidth)
				break;
			if (!isFree(__nx, __ny))
				return false;
		}
	}
	return true;
}

bool RandomMapContext::isFree (randomGridCoord x, randomGridCoord y, randomGridSize width, randomGridSize height) const
{
	SDL_assert(width > 0);
	SDL_assert(height > 0);
	for (randomGridSize w = 0; w < width; ++w) {
		if (x + w >= _mapWidth)
			return false;
		for (randomGridSize h = 0; h < height; ++h) {
			if (y + h >= _mapHeight)
				return false;
			if (!isFree(x + w, y + h)) {
				return false;
			}
		}
	}

	return true;
}

bool RandomMapContext::isFree (randomGridCoord x, randomGridCoord y, const SpriteDefPtr& def) const
{
	const randomGridSize width = getGridSize(def->width);
	const randomGridSize height = getGridSize(def->height);
	return isFree(x, y, width, height);
}

bool RandomMapContext::getGroundDimensions (randomGridCoord x, randomGridCoord y, randomGridCoord& left, randomGridCoord& right) const
{
	left = 0;
	right = 0;
	bool leftSet = false;
	bool rightSet = false;

	std::vector<RandomMapPos> groundPos;

	// find all ground tiles on the same y level
	for (std::vector<RandomMapPos>::const_iterator i = _groundPos.begin(); i != _groundPos.end(); ++i) {
		const RandomMapPos& pos = *i;
		if (pos.y != y)
			continue;

		groundPos.push_back(pos);
	}

	if (groundPos.empty()) {
		Log::error(LOG_GAMEIMPL, "no valid ground tiles found at %i", y);
		return false;
	}

	// check if they are connected
	std::sort(groundPos.begin(), groundPos.end(), RandomMapPosXSorter());
	int step = 1;
	for (std::vector<RandomMapPos>::const_iterator i = groundPos.begin(); i != groundPos.end(); ++i) {
		const RandomMapPos& pos = *i;
		if (pos.x == x + step) {
			right = pos.x;
			rightSet = true;
			++step;
		}
	}
	step = 1;
	for (std::vector<RandomMapPos>::reverse_iterator i = groundPos.rbegin(); i != groundPos.rend(); ++i) {
		const RandomMapPos& pos = *i;
		if (pos.x == x - step) {
			left = pos.x;
			leftSet = true;
			++step;
		}
	}

	if (!leftSet || !rightSet)
		return false;

	return true;
}

bool RandomMapContext::isEnoughGround (randomGridCoord x, randomGridCoord y, randomGridSize width, randomGridSize height) const
{
	randomGridCoord left;
	randomGridCoord right;

	if (!getGroundDimensions(x, y, left, right))
		return false;

	// TODO: check for height
	return right - left >= width;
}

}
