#pragma once

#include "network/IProtocolHandler.h"
#include "network/messages/LoadMapMessage.h"
#include "ui/nodes/UINodePoint.h"
#include "client/ClientMap.h"
#include "ui/UI.h"

class LoadMapHandler: public ClientProtocolHandler<LoadMapMessage> {
protected:
	ClientMap& _map;
	ServiceProvider& _serviceProvider;

public:
	LoadMapHandler (ClientMap& map, ServiceProvider& serviceProvider) :
			_map(map), _serviceProvider(serviceProvider)
	{
	}

	virtual void execute (const LoadMapMessage* msg) override
	{
		const SpawnMessage spawnMsg;
		if (_serviceProvider.getNetwork().sendToServer(spawnMsg) == -1) {
			Log::error(LOG_CLIENT, "could not send spawn command to server");
			return;
		}
		UI::get().push(UI_WINDOW_MAP);

		System.track("mapload", msg->getName());
		UINodePoint* pointsNode = UI::get().getNode<UINodePoint>(UI_WINDOW_MAP, UINODE_POINTS);
		if (pointsNode)
			pointsNode->setPoints(0);
		_map.load(msg->getName(), msg->getTitle());
	}
};
