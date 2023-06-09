#pragma once

#include "network/IProtocolHandler.h"
#include "network/messages/ClientInitMessage.h"
#include "caveexpress/server/map/Map.h"

namespace caveexpress {

class ClientInitHandler: public IServerProtocolHandler {
private:
	Map& _map;
public:
	ClientInitHandler (Map& map) :
			_map(map)
	{
	}

	void execute (const ClientId& clientId, const IProtocolMessage& message) override
	{
		Player *player = _map.getPlayer(clientId);
		if (player == nullptr) {
			Log::error(LOG_GAMEIMPL, "init for player with clientId %i failed", (int)clientId);
			return;
		}
		const ClientInitMessage* msg = assert_cast<const ClientInitMessage*, const IProtocolMessage*>(&message);
		player->setName(msg->getName());
		_map.sendPlayersList();
	}
};

}
