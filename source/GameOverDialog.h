#pragma once

#include "Iw2DSceneGraph.h"
#include "resources.h"

class GameOverDialog : public CSprite
{
public:
	GameOverDialog(void);
	~GameOverDialog(void);
	CLabel * GetScoreLabel() const;
	CSprite * GetScoreButton() const;
	CSprite * GetFacebookButton() const;
private:
	void InitChildElements();
	CSprite * m_ScoreBoardButton;
	CLabel * m_ScoreLabel;
	CSprite * m_FacebookButton;

};

