#include "GameOverDialog.h"


GameOverDialog::GameOverDialog(void)
{
	InitChildElements();
}

void GameOverDialog::InitChildElements()
{
	m_ScoreBoardButton = new CSprite();
	m_ScoreBoardButton->m_X = 90;
	m_ScoreBoardButton->m_Y = 213;
	m_ScoreBoardButton->SetImage(g_pResources->GetScoreBoardButton());
	m_ScoreBoardButton->m_H = m_ScoreBoardButton->GetImage()->GetHeight();
	m_ScoreBoardButton->m_W = m_ScoreBoardButton->GetImage()->GetWidth();
	AddChild(m_ScoreBoardButton);

	//Add score label
	m_ScoreLabel = new CLabel();
	m_ScoreLabel->m_X = 135;
	m_ScoreLabel->m_Y = 130;
	m_ScoreLabel->m_W = 200;
	m_ScoreLabel->m_H = 40;
	m_ScoreLabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	m_ScoreLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_ScoreLabel->SetFont(g_pResources->GetSize20Font());
	m_ScoreLabel->SetText("0000");
	m_ScoreLabel->m_Color = CColor(0,0,0,255);
	AddChild(m_ScoreLabel);

	m_FacebookButton = new CSprite();
	m_FacebookButton->m_X = 90;
	m_FacebookButton->m_Y = 180;
	m_FacebookButton->SetImage(g_pResources->GetFacebookIcon());
	m_FacebookButton->m_H = m_ScoreBoardButton->GetImage()->GetHeight();
	m_FacebookButton->m_W = m_ScoreBoardButton->GetImage()->GetWidth();
	AddChild(m_FacebookButton);

}

CLabel * GameOverDialog::GetScoreLabel() const
{
	return m_ScoreLabel;
}

CSprite * GameOverDialog::GetScoreButton() const
{
	return m_ScoreBoardButton;
}

CSprite * GameOverDialog::GetFacebookButton() const
{
	return m_FacebookButton;
}

GameOverDialog::~GameOverDialog(void)
{
}


