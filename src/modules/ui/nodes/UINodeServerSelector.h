#pragma once

#include "ui/nodes/UINodeSelector.h"
#include "network/INetwork.h"

struct ServerEntry {
	ServerEntry (const std::string& _name, const std::string& _host, int _port, const std::string& _mapName,
			int _playerCount, int _maxPlayerCount) :
			name(_name), host(_host), mapName(_mapName), port(_port), playerCount(_playerCount), maxPlayerCount(
					_maxPlayerCount)
	{
	}
	std::string name;
	std::string host;
	std::string mapName;
	int port;
	int playerCount;
	int maxPlayerCount;
};

// this node search for servers and presents then in a list to connect to them
class UINodeServerSelector: public UINodeSelector<ServerEntry> {
private:
	typedef UINodeSelector<ServerEntry> Super;
	inline int getNameX () const;
	inline int getMapX () const;
	inline int getPlayersX () const;

	int _headlineHeight;
	BitmapFontPtr _headlineFont;
public:
	UINodeServerSelector (IFrontend *frontend, int rows = 10);
	virtual ~UINodeServerSelector ();

	void addServer (const std::string& host, const std::string& name, const std::string& mapName, int port,
			int playerCount, int maxPlayerCount);

	// UINodeSelector
	bool onSelect (const ServerEntry& data) override;
	void render (int x, int y) const override;
	void renderSelectorEntry (int index, const ServerEntry& data, int x, int y, int colWidth, int rowHeight, float alpha) const override;

	// UINode
	bool onPush () override;
};
