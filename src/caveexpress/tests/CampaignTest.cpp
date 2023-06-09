#include "tests/TestShared.h"
#include "campaign/persister/SQLitePersister.h"
#include "campaign/CampaignManager.h"
#include "network/NoNetwork.h"
#include "common/MapManager.h"
#include "common/FileSystem.h"
#include "common/TextureDefinition.h"
#include "caveexpress/shared/CaveExpressMapContext.h"
#include "common/MapSettings.h"

namespace caveexpress {

TEST(CampaignTest, testSave) {
	SCOPED_TRACE("new.sqlite");
	SQLitePersister persister(System.getDatabaseDirectory() + "new.temp");
	ASSERT_TRUE(persister.init()) << "Failed to initialize the persister. " << persister.getError();
	Campaign campaign("testsave", &persister);
	campaign.addMap("test1", "test1");
	campaign.addMap("test2", "test2");
	campaign.addMap("test3", "test3");
	campaign.unlock();
	ASSERT_TRUE(campaign.unlockNextMap(false)) << "failed to unlock the next map";
	const int expectedLives = 1;
	campaign.setLives(expectedLives);
	ASSERT_TRUE(campaign.saveProgress()) << "failed to save the campaign";
	campaign.setLives(100);
	ASSERT_TRUE(campaign.unlockNextMap(false)) << "failed to unlock the next map";
	ASSERT_EQ(std::string("test3"), campaign.getNextMap()) << "Failed to unlock the next map";
	ASSERT_TRUE(campaign.loadProgress()) << "failed to load the campaign progress";
	ASSERT_EQ(std::string("test2"), campaign.getNextMap()) << "Failed to load the campaign map progress";
	ASSERT_EQ(expectedLives, (int )campaign.getLives()) << "Failed to save/load lives";
}

TEST(CampaignTest, testLoad) {
	SCOPED_TRACE("gamestate.sqlite");
	const std::string target = System.getDatabaseDirectory() + "gamestatetestload.sqlite";
	ASSERT_TRUE(FS.copy("base/tests/gamestate.sqlite", target));
	SQLitePersister persister(target);
	ASSERT_TRUE(persister.init()) << "Failed to initialize the persister for " << target << ". " << persister.getError();
	Campaign campaign("tutorial", &persister);
	ASSERT_TRUE(campaign.loadProgress()) << "failed to load the campaign progress";
}

TEST(CampaignTest, DISABLED_testLoad2) {
	SCOPED_TRACE("gamestate2.sqlite");
	const std::string target = System.getDatabaseDirectory() + "gamestatetestload2.sqlite";
	ASSERT_TRUE(FS.copy("base/tests/gamestate2.sqlite", target));
	SQLitePersister persister(target);
	ASSERT_TRUE(persister.init()) << "Failed to initialize the persister for " << target << ". " << persister.getError();
	Campaign campaign("tutorial", &persister);
	ASSERT_TRUE(campaign.loadProgress()) << "failed to load the campaign progress";
}

TEST(CampaignTest, testReset) {
	SCOPED_TRACE("reset.temp");
	SQLitePersister persister(System.getDatabaseDirectory() + "reset.temp");
	ASSERT_TRUE(persister.init()) << "Failed to initialize the persister. " << persister.getError();
	Campaign campaign("testsave", &persister);
	campaign.addMap("test1", "test1");
	campaign.addMap("test2", "test2");
	campaign.addMap("test3", "test3");
	campaign.unlock();
	ASSERT_TRUE(campaign.unlockNextMap(true)) << "failed to unlock the next map";
	ASSERT_EQ(std::string("test2"), campaign.getNextMap()) << "Failed to load the campaign map progress";
	const int expectedLives = 3;
	ASSERT_TRUE(campaign.reset(true)) << "failed to reset the campaign";
	ASSERT_TRUE(campaign.isUnlocked()) << "failed to reset the locked state of the campaign";
	ASSERT_TRUE(campaign.saveProgress()) << "failed to save the campaign";
	ASSERT_TRUE(campaign.loadProgress()) << "failed to load the campaign progress";
	ASSERT_EQ(std::string("test1"), campaign.getNextMap()) << "Failed to load the campaign map progress";
	ASSERT_EQ(expectedLives, (int )campaign.getLives()) << "Failed to reset lives";
	ASSERT_TRUE(campaign.reset(false)) << "failed to reset the campaign";
	ASSERT_TRUE(!campaign.isUnlocked()) << "failed to reset the locked state of the campaign";
	ASSERT_TRUE(campaign.loadProgress()) << "failed to load the campaign progress";
	ASSERT_EQ(std::string(""), campaign.getNextMap()) << "Failed to load the campaign map progress";
	ASSERT_EQ(expectedLives, (int )campaign.getLives()) << "Failed to reset lives";
}

// check that all the specified maps exist and are loadable
TEST(CampaignTest, testMaps) {
	SCOPED_TRACE("idontcare.temp");
	SQLitePersister persister(System.getDatabaseDirectory() + "idontcare.temp");
	ASSERT_TRUE(persister.init()) << "Failed to initialize the persister. " << persister.getError();
	LUAMapManager mapMgr;
	mapMgr.loadMaps();
	TextureDefinition t("small");
	SpriteDefinition::get().init(t);
	CampaignManager mgr(&persister, mapMgr);
	mgr.init();

	class Visitor: public ICampaignVisitor {
	public:
		bool atLeastOnce;
		Visitor() :
				atLeastOnce(false) {
		}
		void visitCampaign(CampaignPtr& campaign) override {
			const Campaign::MapList& m = campaign->getMaps();
			ASSERT_FALSE(m.empty()) << "failed to get the maps for campaign " << campaign->getId();
			for (Campaign::MapListConstIter i = m.begin(); i != m.end(); ++i) {
				atLeastOnce = true;
				const std::string& id = (*i)->getId();
				CaveExpressMapContext ctx(id);
				EXPECT_TRUE(ctx.load(false)) << "failed to load the map " << id;
				IMap::SettingsMap settings = ctx.getSettings();
				const gridCoord x = string::toFloat(ctx.getStartPositions()[0]._x);
				const gridCoord y = string::toFloat(ctx.getStartPositions()[0]._y);
				EXPECT_TRUE(ctx.isLocationValid(x, y)) << "map " << id << " has invalid player start positions: " << x << ":" << y << " (" << settings[msn::WIDTH] << ":" << settings[msn::HEIGHT] << ")";
				EXPECT_TRUE(ctx.isLocationFree(x, y)) << "map " << id << " has blocked player start positions: " << x << ":" << y;
			}
		}
	};

	Visitor visitor;
	mgr.visitCampaigns(&visitor);
	ASSERT_TRUE(visitor.atLeastOnce) << "failed to get any campaign";
}

TEST(CampaignTest, testUpdateMapValues) {
	SCOPED_TRACE("updatemapvalues.temp");
	SQLitePersister persister(System.getDatabaseDirectory() + "updatemapvalues.temp");
	ASSERT_TRUE(persister.init()) << "Failed to initialize the persister. " << persister.getError();
	LUAMapManager mapMgr;
	mapMgr.loadMaps();
	TextureDefinition t("small");
	SpriteDefinition::get().init(t);
	CampaignManager mgr(&persister, mapMgr);
	mgr.init();
	CampaignPtr campaign = mgr.getActiveCampaign();
	CampaignMapPtr campaignMap = campaign->getMaps().front();
	campaignMap->reset();
	ASSERT_TRUE(mgr.updateMapValues(campaignMap->getId(), 100, 4, 1));
	ASSERT_EQ(1, (int)campaignMap->getStars()) << "stars don't match";
	ASSERT_EQ(4u, campaignMap->getTime()) << "time doesn't match";
	ASSERT_EQ(100u, campaignMap->getFinishPoints()) << "points don't match";
	ASSERT_TRUE(campaign->loadProgress()) << "failed to load the campaign progress";
	ASSERT_TRUE(mgr.updateMapValues(campaignMap->getId(), 150, 3, 2));
	ASSERT_EQ(2, (int)campaignMap->getStars()) << "stars don't match";
	ASSERT_EQ(3u, campaignMap->getTime()) << "time doesn't match";
	ASSERT_EQ(150u, campaignMap->getFinishPoints()) << "points don't match";
	ASSERT_TRUE(campaign->loadProgress())<< "failed to load the campaign progress";
	ASSERT_EQ(2, (int)campaignMap->getStars()) << "stars don't match after loading";
	ASSERT_EQ(3u, campaignMap->getTime()) << "time doesn't match after loading";
	ASSERT_EQ(150u, campaignMap->getFinishPoints()) << "points don't match after loading";
	ASSERT_TRUE(mgr.updateMapValues(campaignMap->getId(), 1, 10, 1));
	ASSERT_EQ(2, (int)campaignMap->getStars()) << "stars don't match after loading";
	ASSERT_EQ(3u, campaignMap->getTime()) << "time doesn't match after loading";
	ASSERT_EQ(150u, campaignMap->getFinishPoints()) << "points don't match after loading";
}

TEST(CampaignTest, DISABLED_testResetProgress) {
	SCOPED_TRACE("gamestate2.sqlite");
	const std::string target = System.getDatabaseDirectory() + "gamestatetestresetprogress.sqlite";
	ASSERT_TRUE(FS.copy("base/tests/gamestate2.sqlite", target));
	SQLitePersister persister(target);
	ASSERT_TRUE(persister.init()) << "Failed to initialize the persister for " << target << ". " << persister.getError();
	LUAMapManager mapMgr;
	mapMgr.loadMaps();
	TextureDefinition t("small");
	SpriteDefinition::get().init(t);
	CampaignManager mgr(&persister, mapMgr);
	mgr.init();
	CampaignPtr c = mgr.getAutoActiveCampaign();
	ASSERT_TRUE(c.get()) << "There is no active campaign";
	ASSERT_EQ("ice", c->getId());
	ASSERT_TRUE(c->isUnlocked()) << "Campaign ice is not unlocked";
	ASSERT_TRUE(mgr.resetAllSavedData()) << "Failed to reset the campaign progress";
	ASSERT_FALSE(c->isUnlocked()) << "Campaign ice is still unlocked";
	CampaignPtr activeCampaign = mgr.getActiveCampaign();
	ASSERT_EQ("tutorial", activeCampaign->getId());
}

}
