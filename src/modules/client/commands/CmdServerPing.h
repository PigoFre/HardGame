#pragma once

#include "common/ICommand.h"
#include "service/ServiceProvider.h"
#include "network/INetwork.h"
#include "common/ConfigManager.h"
#include "network/messages/PingMessage.h"
#include "ui/nodes/UINodeServerSelector.h"

class CmdServerPing: public ICommand, public IClientCallback {
private:
	UINodeServerSelector *_serverSelector;
	ServiceProvider& _serviceProvider;

public:
	CmdServerPing (UINodeServerSelector *serverlist, ServiceProvider& serviceProvider) :
			_serverSelector(serverlist), _serviceProvider(serviceProvider)
	{
	}

	void run (const Args& args) override
	{
		_serverSelector->reset();
		if (!_serviceProvider.getNetwork().discover(this, Config.getPort()))  {
			Log::error(LOG_CLIENT, "could not send the ping broadcast");
		} else {
			Log::info(LOG_CLIENT, "sent ping broadcast");
		}
	}

	void onOOBData (const std::string& host, const IProtocolMessage* message) override
	{
		if (message->getId() != protocol::PROTO_PING) {
			Log::error(LOG_CLIENT, "got invalid discover broadcast reply");
			return;
		}
		Log::info(LOG_CLIENT, "got ping broadcast reply");
		const PingMessage* p = static_cast<const PingMessage*>(message);
		_serverSelector->addServer(host, p->getName(), p->getMapName(), p->getPort(), p->getPlayerCount(),
				p->getMaxPlayerCount());
	}
};
