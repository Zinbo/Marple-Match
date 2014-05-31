#include "GameStartDialog.h"

GameStartDialog::GameStartDialog()
{
	InitChildElements();
}

void GameStartDialog::InitChildElements()
{
	//add start button to game over dialog
	m_StartButton = new CSprite();
	m_StartButton->m_X = 72.5;
	m_StartButton->m_Y = 245;
	m_StartButton->SetImage(g_pResources->GetStartButton());
	m_StartButton->m_H = m_StartButton->GetImage()->GetHeight();
	m_StartButton->m_W = m_StartButton->GetImage()->GetWidth();
	AddChild(m_StartButton);

	//Add match label
	m_MatchLabel = new CLabel();
	m_MatchLabel->m_X = 70;
	m_MatchLabel->m_Y = 60;
	m_MatchLabel->m_W = 230;
	m_MatchLabel->m_H = 50;
	m_MatchLabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	m_MatchLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_MatchLabel->SetFont(g_pResources->GetSize20Font());
	m_MatchLabel->SetText("0 Pairs");
	m_MatchLabel->m_Color = CColor(0,0,0,255);
	AddChild(m_MatchLabel);

	//Add pair label
	m_PairLabel = new CLabel();
	m_PairLabel->m_X = 70;
	m_PairLabel->m_Y = 125;
	m_PairLabel->m_W = 230;
	m_PairLabel->m_H = 50;
	m_PairLabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	m_PairLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_PairLabel->SetFont(g_pResources->GetSize20Font());
	m_PairLabel->SetText("0 Per Board");
	m_PairLabel->m_Color = CColor(0,0,0,255);
	AddChild(m_PairLabel);

	//Add time label
	m_TimeLabel = new CLabel();
	m_TimeLabel->m_X = 70;
	m_TimeLabel->m_Y = 190;
	m_TimeLabel->m_W = 230;
	m_TimeLabel->m_H = 50;
	m_TimeLabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	m_TimeLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_TimeLabel->SetFont(g_pResources->GetSize20Font());
	m_TimeLabel->SetText("00:00");
	m_TimeLabel->m_Color = CColor(0,0,0,255);
	AddChild(m_TimeLabel);
}

CSprite * GameStartDialog::GetStartButton() const
{
	return m_StartButton;
}

CLabel * GameStartDialog::GetMatchLabel() const
{
	return m_MatchLabel;
}

CLabel * GameStartDialog::GetPairLabel() const
{
	return m_PairLabel;
}

CLabel * GameStartDialog::GetTimeLabel() const
{
	return m_TimeLabel;
}

GameStartDialog::~GameStartDialog()
{

}