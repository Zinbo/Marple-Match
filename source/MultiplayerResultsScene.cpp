#include "MultiplayerResultsScene.h"

using namespace SFAS2014;

const float MultiplayerResultsScene::kPlayer1ScoreX = 7.0f;
const float MultiplayerResultsScene::kPlayer1ScoreY = 48.0f;
const float MultiplayerResultsScene::kPlayer2ScoreX = 160.0f;
const float MultiplayerResultsScene::kPlayer2ScoreY = 48.0f;
const float MultiplayerResultsScene::kScoreWidth = 100.0f;
const float MultiplayerResultsScene::kScoreHeight = 20.0f;

MultiplayerResultsScene::MultiplayerResultsScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingMenu)
	:ResultsScene(xGraphicsScale, yGraphicsScale, settingMenu)
{
}

void MultiplayerResultsScene::Reset()
{
	Scene::Reset();
	Audio::PlayMusic(g_pResources->GetMenuMusicFilename(), true);
	UpdateForNewScore();
	SetupLeaderboard();
	SetupRecentScoreLabels();
	//If the sound and music has been turned off in another scene then set the buttons on this scene to reflect this.
}

void MultiplayerResultsScene::Init()
{
	Scene::Init();

	InitUI();
	InitRecentScoreLabels();
	InitLeaderboardLabels();
	InitButtons();
	PopulateScores();
}

void MultiplayerResultsScene::Update(float deltaTime, float alphaMul)
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
				MultiplayerGameScene * gameScene = (MultiplayerGameScene *) m_Manager->Find("MultiplayerState");
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

void MultiplayerResultsScene::UpdateForNewScore()
{
	char nameBuffer[6];
	int newScoreIndex = -1;
	PlayerScore oldScore;
	for(int k = 0; k < 2; k++)
	{
		for(int i = 0; i < 5; i++)
		{

			if(((GameSceneManager *) m_Manager)->GetScore(k) > m_TopScores->GetNameScorePair(i).GetScore())
			{
				char dialogText[100];
				sprintf(dialogText, "New Highscore for player %d! Please enter name. (5 characters or less)", k+1);
				const char* playerName = s3eOSReadStringUTF8(dialogText);
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
			p.SetScore(((GameSceneManager *) m_Manager)->GetScore(k));
			m_TopScores->SetNameScorePair(p, newScoreIndex);

			WriteScoresToFile();
		}
	}
	
}

void MultiplayerResultsScene::InitRecentScoreLabels()
{
	// Create the score text
	m_Player1ScoreLabel = new CLabel();
	m_Player1ScoreLabel->m_X = kPlayer1ScoreX * m_XGraphicsScale;
	m_Player1ScoreLabel->m_Y = kPlayer1ScoreY * m_YGraphicsScale;
	m_Player1ScoreLabel->m_W = kScoreWidth * m_XGraphicsScale;
	m_Player1ScoreLabel->m_H = kScoreHeight * m_YGraphicsScale;
	m_Player1ScoreLabel->SetFont(g_pResources->GetSize20Font());
	m_Player1ScoreLabel->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
	m_Player1ScoreLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_Player1ScoreLabel->m_Color = CColor(0,0,0,255);
	AddChild(m_Player1ScoreLabel);

	m_Player2ScoreLabel = new CLabel();
	m_Player2ScoreLabel->m_X = kPlayer2ScoreX * m_XGraphicsScale;
	m_Player2ScoreLabel->m_Y = kPlayer2ScoreY * m_YGraphicsScale;
	m_Player2ScoreLabel->m_W = kScoreWidth * m_XGraphicsScale;
	m_Player2ScoreLabel->m_H = kScoreHeight * m_YGraphicsScale;
	m_Player2ScoreLabel->SetFont(g_pResources->GetSize20Font());
	m_Player2ScoreLabel->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
	m_Player2ScoreLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_Player2ScoreLabel->m_Color = CColor(0,0,0,255);
	AddChild(m_Player2ScoreLabel);
}

void MultiplayerResultsScene::InitUI()
{
	// Create background sprite
	m_Background = new CSprite();
	m_Background->m_X = 0;
	m_Background->m_Y = 0;
	m_Background->SetImage(g_pResources->GetMultiplayerResultBackground());
	m_Background->m_W = m_Background->GetImage()->GetWidth();
	m_Background->m_H = m_Background->GetImage()->GetHeight();
 
	// Fit background to screen size
	m_Background->m_ScaleX = (float)IwGxGetScreenWidth() / m_Background->GetImage()->GetWidth();
	m_Background->m_ScaleY = (float)IwGxGetScreenHeight() / m_Background->GetImage()->GetHeight();
	AddChild(m_Background);
}

void MultiplayerResultsScene::SetupRecentScoreLabels()
{
	char p1ScoreBuffer[5];
	sprintf(p1ScoreBuffer, "%.4d", ((GameSceneManager*) m_Manager)->GetScore(0));
	m_Player1ScoreLabel->SetText(p1ScoreBuffer);

	char p2ScoreBuffer[5];
	sprintf(p2ScoreBuffer, "%.4d", ((GameSceneManager*) m_Manager)->GetScore(1));
	m_Player2ScoreLabel->SetText(p2ScoreBuffer);
}
MultiplayerResultsScene::~MultiplayerResultsScene(void)
{
}
