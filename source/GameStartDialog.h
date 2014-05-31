#pragma once
#include "Iw2DSceneGraph.h"
#include "resources.h"

class GameStartDialog : public CSprite
{
public:
	GameStartDialog();
	~GameStartDialog(void);
	CSprite * GetStartButton() const;
	CLabel * GetMatchLabel() const;
	CLabel * GetPairLabel() const;
	CLabel * GetTimeLabel() const;
private:
	void InitChildElements();

	CSprite * m_StartButton;
	CLabel * m_MatchLabel;
	CLabel * m_PairLabel;
	CLabel * m_TimeLabel;
};

