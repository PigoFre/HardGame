#include "tests/TestShared.h"
#include "cavepacker/server/map/SokobanMapContext.h"

namespace cavepacker {

TEST(SokobanMapContextTest, testMapCreation)
{
	for (int i = 1; i <= 90; ++i) {
		const std::string name = string::format("xsokoban%04i", i);
		SokobanMapContext ctx(name);
		ASSERT_TRUE(ctx.load(false));
	}
}

}
