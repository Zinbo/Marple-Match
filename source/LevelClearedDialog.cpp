#include "LevelClearedDialog.h"


LevelClearedDialog::LevelClearedDialog()
{
	InitChildElements();
}

void LevelClearedDialog::InitChildElements()
{
	//Add score label
	m_ScoreLabel = new CLabel();
	m_ScoreLabel->m_X = 55;
	m_ScoreLabel->m_Y = 150;
	m_ScoreLabel->m_W = 100;
	m_ScoreLabel->m_H = 40;
	m_ScoreLabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	m_ScoreLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_ScoreLabel->SetFont(g_pResources->GetSize30Font());
	m_ScoreLabel->SetText("0000");
	m_ScoreLabel->m_Color = CColor(0,0,0,255);
	AddChild(m_ScoreLabel);
	
	//Add gold label
	m_GoldLabel = new CLabel();
	m_GoldLabel->m_X = 245;
	m_GoldLabel->m_Y = 150;
	m_GoldLabel->m_W = 100;
	m_GoldLabel->m_H = 40;
	m_GoldLabel->m_AnchorX = 1;
	m_GoldLabel->m_AlignHor = IW_2D_FONT_ALIGN_RIGHT;
	m_GoldLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_GoldLabel->SetFont(g_pResources->GetSize30Font());
	m_GoldLabel->SetText("0000");
	m_GoldLabel->m_Color = CColor(0,0,0,255);
	AddChild(m_GoldLabel);

	//Add Item Shop Label
	m_ItemShopButton = new CSprite();
	m_ItemShopButton->m_X = 10;
	m_ItemShopButton->m_Y = 213;
	m_ItemShopButton->SetImage(g_pResources->GetItemShopButton());
	m_ItemShopButton->m_H = m_ItemShopButton->GetImage()->GetHeight();
	m_ItemShopButton->m_W = m_ItemShopButton->GetImage()->GetWidth();
	AddChild(m_ItemShopButton);

	//Add Item Shop Label
	m_NextLevelButton = new CSprite();
	m_NextLevelButton->m_X = 178;
	m_NextLevelButton->m_Y = 213;
	m_NextLevelButton->SetImage(g_pResources->GetNextLevelButton());
	m_NextLevelButton->m_H = m_ItemShopButton->GetImage()->GetHeight();
	m_NextLevelButton->m_W = m_ItemShopButton->GetImage()->GetWidth();
	AddChild(m_NextLevelButton);
}

CLabel * LevelClearedDialog::GetGoldLabel() const
{
	return m_GoldLabel;
}

CLabel * LevelClearedDialog::GetScoreLabel() const
{
	return m_ScoreLabel;
}

CSprite * LevelClearedDialog::GetNextLevelButton() const 
{
	return m_NextLevelButton;
}

CSprite * LevelClearedDialog::GetItemShopButton() const
{
	return m_ItemShopButton;
}

LevelClearedDialog::~LevelClearedDialog(void)
{
}
