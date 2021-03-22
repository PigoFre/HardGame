#pragma once

#include "caveexpress/server/entities/npcs/INPCCave.h"

namespace caveexpress {

// forward decl
class CaveMapTile;

/**
 * @brief This npc will put a package in front of its cave
 * @sa Package
 */
class NPCPackage : public INPCCave {
public:
	NPCPackage (CaveMapTile *cave, const EntityType& type);
	virtual ~NPCPackage ();

	void leavePackage ();

	// NPC
	void onSpawn () override;
	void setIdle () override;
	void update (uint32_t deltaTime) override;
	bool shouldCollide (const IEntity* entity) const override;
};

}
