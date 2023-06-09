#pragma once

#include "network/IProtocolHandler.h"
#include "client/network/InitDoneHandler.h"
#include "caveexpress/shared/CaveExpressAnimation.h"
#include "common/ConfigManager.h"

namespace caveexpress {

class HudInitDoneHandler: public InitDoneHandler {
public:
	HudInitDoneHandler (ClientMap& map) :
			InitDoneHandler(map)
	{
	}

	void execute (const InitDoneMessage* msg) override
	{
		InitDoneHandler::execute(msg);
		const uint8_t packages = msg->getPackages();
		{
			UINodeSprite* node = UI::get().getNode<UINodeSprite>(UI_WINDOW_MAP, UINODE_PACKAGES);
			if (node) {
				node->clearSprites();
				const std::string name = SpriteDefinition::get().getSpriteName(EntityTypes::PACKAGE_ROCK,
						Animations::ANIMATION_IDLE);
				const SpritePtr sprite = UI::get().loadSprite(name);
				for (uint8_t i = 0; i < packages; ++i) {
					node->addSprite(sprite);
				}
			}
		}
		{
			UINodeSprite* node = UI::get().getNode<UINodeSprite>(UI_WINDOW_MAP, UINODE_TARGETCAVEID);
			if (node) {
				node->clearSprites();
			}
		}

		UI::get().setBarValue(UI_WINDOW_MAP, UINODE_HITPOINTS, msg->getHitpoints());

		{
			const uint8_t lives = msg->getLives();
			UINodeSprite* node = UI::get().getNode<UINodeSprite>(UI_WINDOW_MAP, UINODE_LIVES);
			if (node) {
				node->clearSprites();
				const SpritePtr sprite = UI::get().loadSprite("icon-heart");
				for (uint8_t i = 0; i < lives; ++i) {
					node->addSprite(sprite);
				}
			}
		}
	}
};

}
