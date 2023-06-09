#pragma once

#include "network/IProtocolHandler.h"
#include "caveexpress/server/map/Map.h"
#include "network/messages/StopMovementMessage.h"

namespace caveexpress {

class StopMovementHandler: public IServerProtocolHandler {
private:
	Map& _map;
public:
	StopMovementHandler (Map& map) :
			_map(map)
	{
	}

	void execute (const ClientId& clientId, const IProtocolMessage& message) override
	{
		Player* player = _map.getPlayer(clientId);
		if (player == nullptr) {
			Log::error(LOG_GAMEIMPL, "stop movement for player with clientId %i failed", (int)clientId);
			return;
		}
		const StopMovementMessage* msg = assert_cast<const StopMovementMessage*, const IProtocolMessage*>(&message);
		player->resetAcceleration(msg->getDirection());
	}
};

}
