#include "UINodeCampaignSelector.h"
#include "campaign/CampaignManager.h"
#include "common/CommandSystem.h"
#include "ui/UI.h"

UINodeCampaignSelector::UINodeCampaignSelector (IFrontend *frontend, CampaignManager &campaignManager, int cols, int rows) :
		Super(frontend, cols, rows), _campaignManager(campaignManager)
{
	defaults();
	setPaddingPixel(10);
	setColsRowsFromTexture("icon-campaign");
	reset();
}

UINodeCampaignSelector::~UINodeCampaignSelector ()
{
}

void UINodeCampaignSelector::visitCampaign (CampaignPtr& campaign)
{
	addData(campaign);
}

bool UINodeCampaignSelector::onSelect (const CampaignPtr& data)
{
	const CampaignPtr& campaign = _campaignManager.activateCampaign(data->getId());
	if (!campaign)
		return false;

	UI::get().push(UI_WINDOW_CAMPAIGN_MAPS);
	return true;
}

void UINodeCampaignSelector::renderSelectorEntry (int index, const CampaignPtr& data, int x, int y, int colWidth, int rowHeight, float alpha) const
{
	const std::string& icon = data->getIcon();
	TexturePtr t = loadTexture(icon);
	if (!t || !t->isValid())
		t = loadTexture("icon-campaign");

	if (!data->getText().empty()) {
		const BitmapFontPtr& font = getFont(SMALL_FONT);
		const int textHeight = font->getTextHeight(data->getText());
		const int fontX = std::max(x, x + colWidth / 2 - font->getTextWidth(data->getText()) / 2);
		const int fontY = y + rowHeight - textHeight - 1;
		_frontend->renderFilledRect(x, fontY - 1, colWidth, textHeight + 2, colorBlack);
		//_frontend->renderRect(x, fontY - 1, colWidth, textHeight + 2, colorWhite);
		renderImage(t, x, y, colWidth, rowHeight - textHeight, alpha);
		font->printMax(data->getText(), colorWhite, fontX, fontY, colWidth);
	} else {
		renderImage(t, x, y, colWidth, rowHeight, alpha);
	}
}

void UINodeCampaignSelector::reset ()
{
	Super::reset();
	_campaignManager.visitCampaigns(this);
}
