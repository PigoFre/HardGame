#pragma once

#include "common/Compiler.h"
#include "ui/windows/intro/Intro.h"

namespace caveexpress {

class IntroPackage: public Intro {
public:
	explicit IntroPackage (IFrontend* frontend);
protected:
	void addIntroNodes(UINode* parent) override;
};

}
