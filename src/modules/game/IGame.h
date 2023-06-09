#pragma once

#include <memory>
#include "network/IProtocolHandler.h"
#include "common/MapManager.h"
#include "common/ConfigManager.h"
#include "common/Commands.h"
#include "common/CommandSystem.h"
#include "campaign/CampaignManager.h"
#include <string>

// TODO: rename methods and document stuff
class IGame : public ICampaignManagerListener {
protected:
	std::string _name;
public:
	virtual ~IGame() {
	}

	inline void setName(const std::string& name) {
		_name = name;
	}

	inline const std::string& getName() const {
		return _name;
	}

	virtual DirectoryEntries listDirectory(const std::string& basedir, const std::string& subdir) {
		DirectoryEntries e;
		return e;
	}

	// create the windows
	virtual void initUI (IFrontend* frontend, ServiceProvider& serviceProvider) {}

	virtual void update (uint32_t deltaTime) {}

	virtual std::string getMapName () { return ""; }

	virtual int getMaxClients ();

	virtual void shutdown () {}

	virtual int getPlayers () { return -1; }

	virtual void connect (ClientId clientId) {}

	virtual int disconnect (ClientId clientId) { return -1; }

	virtual void init (IFrontend *frontend, ServiceProvider& serviceProvider) {}

	virtual void mapReload () {}

	virtual bool mapLoad (const std::string& map) { return false; }

	virtual void mapShutdown () {}

	virtual IMapManager* getMapManager () { return nullptr; }

	// ICampaignManagerListener
	void onCampaignUnlock (Campaign* oldCampaign, Campaign* newCampaign) override;
};

typedef IGame* GamePtr;
