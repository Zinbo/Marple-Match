/*
 * (C) 2014 Search for a Star
 * 
 */

#include "SinglePlayerGameScene.h"


using namespace SFAS2014;

const float SinglePlayerGameScene::kTimeTextX = 7.0f;
const float SinglePlayerGameScene::kTimeTextY = 25.0f;

const float SinglePlayerGameScene::kScoreTextX = 213.0f;
const float SinglePlayerGameScene::kScoreTextY = 25.0f;

const float SinglePlayerGameScene::kLabelHeight = 20.0f;
const float SinglePlayerGameScene::kLabelWidth = 100.0f;

const float SinglePlayerGameScene::kStarXOffset = 61.0f;
const float SinglePlayerGameScene::kStarYOffset = 111.0f;
const float SinglePlayerGameScene::kStarSpacing = 66.0f;
const float SinglePlayerGameScene::kButtonSpacing = 50.0f;
const float SinglePlayerGameScene::kButtonStartingX = 1.0f;
const float SinglePlayerGameScene::kButtonStartingY = 1.0f;

const float SinglePlayerGameScene::kUpdateToScoreX = 160.0f;
const float SinglePlayerGameScene::kUpdateToScoreY = 55.0f;
const float SinglePlayerGameScene::kUpdateToScoreHeight = 15.0f;
const float SinglePlayerGameScene::kUpdateToScoreWidth = 150.0f;

const float SinglePlayerGameScene::kUpdateToTimeX = 10.0f;
const float SinglePlayerGameScene::kUpdateToTimeY = 55.0f;
const float SinglePlayerGameScene::kUpdateToTimeHeight = 15.0f;
const float SinglePlayerGameScene::kUpdateToTimeWidth = 150.0f;

SinglePlayerGameScene::SinglePlayerGameScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingsMenu) 
	: GameScene(1, xGraphicsScale, yGraphicsScale, settingsMenu, 60.0f)
	
{
	m_GridElements.gridHeight = 6;
	m_GridElements.gridWidth = 4;

	m_Time = ((float) keTimeLimit);
	m_GameState = keGamePlaying;
	IwRandSeed( time( 0 ) );

	Create();
	Clear();
}

void SinglePlayerGameScene::AddGridToScene(std::vector<CharacterBuilder> &characterTypes, int player)
{
	float x = kStarXOffset*m_XGraphicsScale;
	float y = kStarYOffset*m_YGraphicsScale;
	for( int row = 0; row < m_GridElements.gridHeight; row++ )
	{
		x = kStarXOffset*m_XGraphicsScale;
		for( int column = 0; column < m_GridElements.gridWidth; column++ )
		{
			int characterTypeIndex = rand() % characterTypes.size();
			GridItem* grid = new GridItem( x, y, characterTypes.at(characterTypeIndex));
			characterTypes.erase(characterTypes.begin() + characterTypeIndex);

			m_Grid[0][(row*m_GridElements.gridWidth)+column] = grid; 
			AddChild( grid->GetStarSprite() );
			AddChild(grid->GetCharacterSprite());

			x += kStarSpacing*m_XGraphicsScale;
		}

		y += kStarSpacing*m_YGraphicsScale;
	}
}

void SinglePlayerGameScene::InitButtons()
{
	m_SettingsButton = new CSprite();
	m_SettingsButton->m_X = (135*m_XGraphicsScale);
	m_SettingsButton->m_Y = (1*m_YGraphicsScale);
	m_SettingsButton->SetImage(g_pResources->GetSettingsButton());
	m_SettingsButton->m_H = m_SettingsButton->GetImage()->GetHeight();
	m_SettingsButton->m_W = m_SettingsButton->GetImage()->GetWidth();
	float buttonScale = (50 / m_SettingsButton->m_H);
	m_SettingsButton->m_ScaleX = (buttonScale * m_XGraphicsScale);
	m_SettingsButton->m_ScaleY = (buttonScale * m_YGraphicsScale);
	AddChild(m_SettingsButton);
}

void SinglePlayerGameScene::ResetDoublePoints(Timer* timer, void* userData)
{
	SinglePlayerGameScene* self = (SinglePlayerGameScene*) userData;
	self->m_DoublePoints[0] = false;
}

void SinglePlayerGameScene::InitUI()
{
	//Add background
	m_Background = new CSprite();
	m_Background->m_X = 0;
	m_Background->m_Y = 0;
	m_Background->SetImage(g_pResources->GetGameBackground());
	m_Background->m_W = m_Background->GetImage()->GetWidth();
	m_Background->m_H = m_Background->GetImage()->GetHeight();

	// Fit background to screen size
	m_Background->m_ScaleX = (float)IwGxGetScreenWidth() / m_Background->m_W;
	m_Background->m_ScaleY = (float)IwGxGetScreenHeight() / m_Background->m_H;
	AddChild(m_Background);
}

void SinglePlayerGameScene::InitLabels()
{
	// Create the score text
	m_ScoreLabel[0] = new CLabel();
	m_ScoreLabel[0]->m_X = kScoreTextX * m_XGraphicsScale;
	m_ScoreLabel[0]->m_Y = kScoreTextY * m_YGraphicsScale;
	m_ScoreLabel[0]->m_W = kLabelWidth;
	m_ScoreLabel[0]->m_H = kLabelHeight;
	m_ScoreLabel[0]->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
	m_ScoreLabel[0]->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_ScoreLabel[0]->SetFont(g_pResources->GetSize20Font());
	m_ScoreLabel[0]->SetText("0000");
	m_ScoreLabel[0]->m_Color = CColor(0,0,0,255);
	m_ScoreLabel[0]->m_ScaleX = m_XGraphicsScale;
	m_ScoreLabel[0]->m_ScaleY = m_YGraphicsScale;
	AddChild(m_ScoreLabel[0]);

	// Create the time text
	m_TimeLabel[0] = new CLabel();
	m_TimeLabel[0]->m_X = kTimeTextX*m_XGraphicsScale;
	m_TimeLabel[0]->m_Y = kTimeTextY*m_YGraphicsScale;
	m_TimeLabel[0]->m_W = kLabelWidth;
	m_TimeLabel[0]->m_H = kLabelHeight;
	m_TimeLabel[0]->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
	m_TimeLabel[0]->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_TimeLabel[0]->SetFont(g_pResources->GetSize20Font());
	m_TimeLabel[0]->SetText("02:00");
	m_TimeLabel[0]->m_Color = CColor(0,0,0,255);
	m_TimeLabel[0]->m_ScaleX = m_XGraphicsScale;
	m_TimeLabel[0]->m_ScaleY = m_YGraphicsScale;
	AddChild(m_TimeLabel[0]);

	m_UpdateToScoreLabel = new CLabel();
	m_UpdateToScoreLabel->m_X = kUpdateToScoreX * m_XGraphicsScale;
	m_UpdateToScoreLabel->m_Y = kUpdateToScoreY * m_YGraphicsScale;
	m_UpdateToScoreLabel->m_H = kUpdateToScoreHeight;
	m_UpdateToScoreLabel->m_W = kUpdateToScoreWidth;
	m_UpdateToScoreLabel->m_AlignHor = IW_2D_FONT_ALIGN_RIGHT;
	m_UpdateToScoreLabel->SetFont(g_pResources->GetSize8Font());
	m_UpdateToScoreLabel->m_Color = CColor(0,0,0,255);
	m_UpdateToScoreLabel->m_ScaleX = m_XGraphicsScale;
	m_UpdateToScoreLabel->m_ScaleY = m_YGraphicsScale;
	AddChild(m_UpdateToScoreLabel);

	m_UpdateToTimeLabel = new CLabel();
	m_UpdateToTimeLabel->m_X = kUpdateToTimeX * m_XGraphicsScale;
	m_UpdateToTimeLabel->m_Y = kUpdateToTimeY * m_YGraphicsScale;
	m_UpdateToTimeLabel->m_H = kUpdateToTimeHeight;
	m_UpdateToTimeLabel->m_W = kUpdateToTimeWidth;
	m_UpdateToTimeLabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	m_UpdateToTimeLabel->SetFont(g_pResources->GetSize8Font());
	m_UpdateToTimeLabel->m_Color = CColor(0,0,0,255);
	m_UpdateToTimeLabel->m_ScaleX = m_XGraphicsScale;
	m_UpdateToTimeLabel->m_ScaleY = m_YGraphicsScale;
	AddChild(m_UpdateToTimeLabel);
}

void SinglePlayerGameScene::ExitScene()
{
	m_Timers.Cancel(m_DoublePointsTimer[0]);
	m_DoublePointsTimer[0] = NULL;
	m_FirstSelectedItem[0] = NULL;
	m_SecondSelectedItem[0] = NULL;
	ResultsScene * resultsScene= (ResultsScene*) m_Manager->Find("ResultsState");
	Audio::StopMusic();
	m_Manager->SwitchTo(resultsScene);	
	m_GameState = keGameOver;
	m_NoOfMatchedPairs[0] = 0;
}