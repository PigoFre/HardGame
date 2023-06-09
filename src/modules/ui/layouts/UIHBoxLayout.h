#pragma once

#include "IUILayout.h"

class UIHBoxLayout: public IUILayout {
private:
	float _spacing;
	bool _expandChildren;
	int _align;
public:
	UIHBoxLayout (float spacing = 0.0f, bool expandChildren = false, int align = 0);
	virtual ~UIHBoxLayout ();

	void setSpacing (float spacing);

	void layout (UINode* parent) override;
};

inline void UIHBoxLayout::setSpacing (float spacing)
{
	_spacing = spacing;
}
