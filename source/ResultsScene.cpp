/*
 * (C) 2014 Search for a Star
 * 
 */

#include "ResultsScene.h"
#include "IwGx.h"
#include "resources.h"
#include "TitleScene.h"
#include "s3eOSReadString.h"
#include "GameSceneManager.h"

#define BUTTON_SPACING 50.0f
#define BUTTON_STARTING_X 1.0f
#define BUTTON_STARTING_Y 1.0f

#define MAIN_MENU_BUTTON_X 184.0f
#define MAIN_MENU_BUTTON_Y 384.0f

#define PLAY_AGAIN_BUTTON_X 24.0f
#define PLAY_AGAIN_BUTTON_Y 384.0f

using namespace SFAS2014;

 const float ResultsScene::kButtonSpacing = 50.0f;
 const float ResultsScene::kButtonStartingX = 1.0f;
 const float ResultsScene::kButtonStartingY = 1.0f;
 const float ResultsScene::kMainMenuButtonX = 184.0f;
 const float ResultsScene::kMainMenuButtonY = 384.0f;
 const float ResultsScene::kPlayAgainButtonX = 24.0f;
 const float ResultsScene::kPlayAgainButtonY = 384.0f;

//
//
// ResultsScene class
//
//
ResultsScene::ResultsScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingMenu)
	:MasterScene(xGraphicsScale, yGraphicsScale, settingMenu)
{
	m_TopScores = new TopScores();
}

ResultsScene::~ResultsScene()
{
	delete m_TopScores;
}

void ResultsScene::Init()
{
	Scene::Init();

	InitUI();
	InitRecentScoreLabels();
	InitLeaderboardLabels();
	InitButtons();
	PopulateScores();
}

void ResultsScene::InitRecentScoreLabels()
{
	// Create the score text
	m_ScoreLabel = new CLabel();
	m_ScoreLabel->m_X = 85.0f * m_XGraphicsScale;
	m_ScoreLabel->m_Y = 65.0f * m_YGraphicsScale;
	m_ScoreLabel->m_W = 150.0f;
	m_ScoreLabel->m_H = 30.0f;
	m_ScoreLabel->SetFont(g_pResources->GetSize30Font());
	m_ScoreLabel->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
	m_ScoreLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_ScoreLabel->m_Color = CColor(0,0,0,255);
	m_ScoreLabel->m_ScaleX = m_XGraphicsScale;
	m_ScoreLabel->m_ScaleY = m_YGraphicsScale;
	AddChild(m_ScoreLabel);
}


void ResultsScene::Update(float deltaTime, float alphaMul)
{
	//if not current scene, don't bother updating.
	if(!(m_Manager->GetCurrent() == this))
	{
		return;
	}
	
	Scene::Update(deltaTime, alphaMul);

	if( m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		if(!SettingsMenuHitTest())
		{
			if(m_PlayAgainButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				SinglePlayerGameScene * gameScene = (SinglePlayerGameScene *) m_Manager->Find("GameState");
				SwitchScene(gameScene);
			}
			else if(m_MainMenuButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				TitleScene * titleScene = (TitleScene *) m_Manager->Find("TitleState");
				SwitchScene(titleScene);
			}
		}
		g_pInput->Reset();
	}
}

void ResultsScene::InitButtons()
{
	m_SettingsButton = new CSprite();
	m_SettingsButton->m_X = ((float) IwGxGetScreenWidth() - (BUTTON_STARTING_X*m_XGraphicsScale) - (BUTTON_SPACING*m_XGraphicsScale));
	m_SettingsButton->m_Y = BUTTON_STARTING_Y*m_YGraphicsScale;
	m_SettingsButton->SetImage(g_pResources->GetSettingsButton());
	m_SettingsButton->m_H = m_SettingsButton->GetImage()->GetHeight();
	m_SettingsButton->m_W = m_SettingsButton->GetImage()->GetWidth();
	m_SettingsButton->m_ScaleX =  m_XGraphicsScale;
	m_SettingsButton->m_ScaleY = m_YGraphicsScale;
	AddChild(m_SettingsButton);

	m_PlayAgainButton = new CSprite();
	m_PlayAgainButton->m_X = PLAY_AGAIN_BUTTON_X * m_XGraphicsScale;
	m_PlayAgainButton->m_Y = PLAY_AGAIN_BUTTON_Y * m_YGraphicsScale;
	m_PlayAgainButton->SetImage(g_pResources->GetPlayAgainButton());
	m_PlayAgainButton->m_H = m_PlayAgainButton->GetImage()->GetHeight();
	m_PlayAgainButton->m_W = m_PlayAgainButton->GetImage()->GetWidth();
	m_PlayAgainButton->m_ScaleX = m_XGraphicsScale;
	m_PlayAgainButton->m_ScaleY = m_YGraphicsScale;
	AddChild(m_PlayAgainButton);

	m_MainMenuButton = new CSprite();
	m_MainMenuButton->m_X = MAIN_MENU_BUTTON_X * m_XGraphicsScale;
	m_MainMenuButton->m_Y = MAIN_MENU_BUTTON_Y * m_YGraphicsScale;
	m_MainMenuButton->SetImage(g_pResources->GetMainMenuButton());
	m_MainMenuButton->m_H = m_MainMenuButton->GetImage()->GetHeight();
	m_MainMenuButton->m_W = m_MainMenuButton->GetImage()->GetWidth();
	m_MainMenuButton->m_ScaleX = m_XGraphicsScale;
	m_MainMenuButton->m_ScaleY = m_YGraphicsScale;
	AddChild(m_MainMenuButton);

}

void ResultsScene::Reset()
{
	MasterScene::Reset();
	UpdateForNewScore();
	SetupLeaderboard();
	SetupRecentScoreLabels();
}

void ResultsScene::InitUI()
{
	// Create background sprite
	m_Background = new CSprite();
	m_Background->m_X = 0;
	m_Background->m_Y = 0;
	m_Background->SetImage(g_pResources->GetResultBackground());
	m_Background->m_W = m_Background->GetImage()->GetWidth();
	m_Background->m_H = m_Background->GetImage()->GetHeight();
 
	// Fit background to screen size
	m_Background->m_ScaleX = (float)IwGxGetScreenWidth() / m_Background->GetImage()->GetWidth();
	m_Background->m_ScaleY = (float)IwGxGetScreenHeight() / m_Background->GetImage()->GetHeight();
	AddChild(m_Background);
}

void ResultsScene::InitLeaderboardLabels()
{
	for(int i = 0; i < 5; i++)
	{
		m_TopScoreNames[i] = new CLabel();
		CLabel * nameLabel = m_TopScoreNames[i]; 
		nameLabel->m_X = 40.0f  * m_XGraphicsScale;
		nameLabel->m_Y = (170.0f + i*40.0f)  * m_YGraphicsScale;
		nameLabel->m_H = 20.0f;
		nameLabel->m_W = 100.0f;
		nameLabel->SetFont(g_pResources->GetSize20Font());
		nameLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
		nameLabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
		nameLabel->m_Color = CColor(0,0,0,255);
		nameLabel->m_ScaleX = m_XGraphicsScale;
		nameLabel->m_ScaleY = m_YGraphicsScale;
		AddChild(nameLabel);

		m_TopScoreLabels[i] = new CLabel();
		CLabel * scoreLabel = m_TopScoreLabels[i];
		scoreLabel->m_X = 210.0f  * m_XGraphicsScale;
		scoreLabel->m_Y = (170.0f + i*40.0f) * m_YGraphicsScale;
		scoreLabel->m_H = 20.0f;
		scoreLabel->m_W = 100.0f;
		scoreLabel->SetFont(g_pResources->GetSize20Font());
		scoreLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
		scoreLabel->m_AlignHor = IW_2D_FONT_ALIGN_RIGHT;
		scoreLabel->m_Color = CColor(0,0,0,255);
		scoreLabel->m_ScaleX = m_XGraphicsScale;
		scoreLabel->m_ScaleY = m_YGraphicsScale;
		AddChild(scoreLabel);
	}

}

void ResultsScene::SetupRecentScoreLabels()
{
	char scoreBuffer[5];
	sprintf(scoreBuffer, "%.4d", ((GameSceneManager*) m_Manager)->GetScore(0));
	m_ScoreLabel->SetText(scoreBuffer);
}

void ResultsScene::SetupLeaderboard()
{
	for(int i = 0; i < 5; i++)
	{
		PlayerScore p = m_TopScores->GetNameScorePair(i);
		char scoreBuffer[5];
		sprintf(scoreBuffer, "%.4d", p.GetScore());
		m_TopScoreNames[i]->SetText(p.GetName()); 
		m_TopScoreLabels[i]->SetText(scoreBuffer);
	}
}

void ResultsScene::PopulateScores()
{
	if(!IwFileCheckExists("scores.data"))
	{
		for(int i = 0; i < 5; i++)
		{
			PlayerScore newScore;
			newScore.SetName("COM");
			newScore.SetScore((50 - 10*i));
			m_TopScores->SetNameScorePair(newScore, i);
		}
		WriteScoresToFile();
	}
	else
	{
		ReadScoresFromFile();
	}
	
}

void ResultsScene::ReadScoresFromFile()
{
	s3eFile *fp = s3eFileOpen("scores.data", "rb");
	for(int i = 0; i < 5; i++)
	{
		char scoreBuffer[6];
		char nameBuffer[6];
		s3eFileRead(nameBuffer, sizeof(nameBuffer), 1, fp);
		s3eFileRead(scoreBuffer, sizeof(scoreBuffer), 1, fp);

		PlayerScore playerScore;
		playerScore.SetName(nameBuffer);
		playerScore.SetScore(atoi(scoreBuffer));
		m_TopScores->SetNameScorePair(playerScore, i);
	}
	
	s3eFileClose(fp);
}

void ResultsScene::WriteScoresToFile()
{
	s3eFile *fp = s3eFileOpen("scores.data", "wb");
	
	for(int i = 0; i < 5; i++)
	{
		char scoreBuffer[6];
		int score = m_TopScores->GetNameScorePair(i).GetScore();
		sprintf(scoreBuffer,"%.4d", score);
		s3eFileWrite(m_TopScores->GetNameScorePair(i).GetName(), 6, 1, fp);
		s3eFileWrite(scoreBuffer, sizeof(scoreBuffer), 1, fp);
	}
	
	s3eFileClose(fp);
}

void ResultsScene::UpdateForNewScore()
{
	char nameBuffer[6];
	int newScoreIndex = -1;
	PlayerScore oldScore;
	for(int i = 0; i < 5; i++)
	{

		if(((GameSceneManager *) m_Manager)->GetScore(0) > m_TopScores->GetNameScorePair(i).GetScore())
		{
			
			const char* playerName = s3eOSReadStringUTF8("New Highscore for player 1! Please enter name. (5 characters or less)");
			for(int j = 0; j < 5; j++)
			{
				nameBuffer[j] = playerName[j];
			}
			nameBuffer[5] = '\0';
			newScoreIndex = i;
			break;
		}
	}
	if(newScoreIndex != -1)
	{
		for(int i = 4; i > newScoreIndex; i--)
		{
			PlayerScore newScore;
			newScore.SetName(m_TopScores->GetNameScorePair(i-1).GetName());
			newScore.SetScore(m_TopScores->GetNameScorePair(i-1).GetScore());
			m_TopScores->SetNameScorePair(newScore, i);
		}
		PlayerScore p = m_TopScores->GetNameScorePair(newScoreIndex);
		p.SetName(nameBuffer);
		p.SetScore(((GameSceneManager *) m_Manager)->GetScore(0));
		m_TopScores->SetNameScorePair(p, newScoreIndex);

		WriteScoresToFile();
	}
}

void ResultsScene::ExitScene()
{
	//Not needed
}

void ResultsScene::ResumeGame()
{
	//Not needed
}

void ResultsScene::PauseGame()
{
	//Not needed
}