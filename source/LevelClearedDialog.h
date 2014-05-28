#pragma once
#include "Iw2DSceneGraph.h"
#include "resources.h"

class LevelClearedDialog : public CSprite
{
public:
	LevelClearedDialog();
	~LevelClearedDialog(void);
	CSprite * GetNextLevelButton() const;
	CSprite * GetItemShopButton() const;
	CLabel * GetScoreLabel() const;
	CLabel * GetGoldLabel() const;
private:
	void InitChildElements();

	CSprite * m_NextLevelButton;
	CSprite * m_ItemShopButton;
	CLabel * m_ScoreLabel;
	CLabel * m_GoldLabel;
};

