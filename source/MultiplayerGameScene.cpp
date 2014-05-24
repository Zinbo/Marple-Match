#include "MultiplayerGameScene.h"

using namespace SFAS2014;

const float MultiplayerGameScene::kPlayer1TimeTextX = 7.0f;
const float MultiplayerGameScene::kPlayer1TimeTextY = 275.0f;
const float MultiplayerGameScene::kLabelHeight = 20.0f;
const float MultiplayerGameScene::kLabelWidth = 100.0f;
const float MultiplayerGameScene::kPlayer1ScoreTextX = 214.0f;
const float MultiplayerGameScene::kPlayer1ScoreTextY = 275.0f;

const float MultiplayerGameScene::kPlayer2TimeTextX = 7.0f;
const float MultiplayerGameScene::kPlayer2TimeTextY = 185.0f;
const float MultiplayerGameScene::kPlayer2ScoreTextX = 214.0f;
const float MultiplayerGameScene::kPlayer2ScoreTextY = 185.0f;

const float MultiplayerGameScene::kPlayer1StarXOffset = 60.0f;
const float MultiplayerGameScene::kPlayer1StarYOffset = 335.0f;
const float MultiplayerGameScene::kPlayer2StarXOffset = 60.0f;
const float MultiplayerGameScene::kPlayer2StarYOffset = 35.0f;
const float MultiplayerGameScene::kStarXSpacing = 66.0f;
const float MultiplayerGameScene::kStarYSpacing = 55.0f;

MultiplayerGameScene::MultiplayerGameScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingsMenu)
	:  GameScene(2, xGraphicsScale, yGraphicsScale, settingsMenu, 50.0f)
{
	m_GridElements.gridHeight = 3;
	m_GridElements.gridWidth = 4;

	m_Time = ((float) keTimeLimit);
	m_GameState = keGamePlaying;
	IwRandSeed( time( 0 ) );

	Create();
	Clear();
}

void MultiplayerGameScene::ExitScene()
{
	MasterScene::CleanUp();

	Clear();

	MultiplayerResultsScene * resultsScene= (MultiplayerResultsScene*) m_Manager->Find("MultiplayerResultsState");
	m_Manager->SwitchTo(resultsScene);	
	m_GameState = keGameOver;
}

void MultiplayerGameScene::InitUI()
{
	//Add background
	m_Background = new CSprite();
	m_Background->m_X = 0;
	m_Background->m_Y = 0;
	m_Background->SetImage(g_pResources->GetMultiplayerGameBackground());
	m_Background->m_W = m_Background->GetImage()->GetWidth();
	m_Background->m_H = m_Background->GetImage()->GetHeight();

	// Fit background to screen size
	m_Background->m_ScaleX = (float)IwGxGetScreenWidth() / m_Background->m_W;
	m_Background->m_ScaleY = (float)IwGxGetScreenHeight() / m_Background->m_H;
	AddChild(m_Background);
}

void MultiplayerGameScene::InitLabels()
{
	// Create the score text
	m_ScoreLabel[0] = new CLabel();
	m_ScoreLabel[0]->m_X = kPlayer1ScoreTextX * m_XGraphicsScale;
	m_ScoreLabel[0]->m_Y = kPlayer1ScoreTextY * m_YGraphicsScale;
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
	m_TimeLabel[0]->m_X = kPlayer1TimeTextX*m_XGraphicsScale;
	m_TimeLabel[0]->m_Y = kPlayer1TimeTextY*m_YGraphicsScale;
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

	// Create the score text
	m_ScoreLabel[1] = new CLabel();
	m_ScoreLabel[1]->m_X = kPlayer2ScoreTextX * m_XGraphicsScale + (kLabelWidth*m_XGraphicsScale)/2;
	m_ScoreLabel[1]->m_Y = kPlayer2ScoreTextY * m_YGraphicsScale + (kLabelHeight*m_YGraphicsScale)/2;
	m_ScoreLabel[1]->m_H = kLabelHeight;
	m_ScoreLabel[1]->m_W = kLabelWidth;
	m_ScoreLabel[1]->m_AnchorX = 0.5f;
	m_ScoreLabel[1]->m_AnchorY = 0.5f;
	m_ScoreLabel[1]->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
	m_ScoreLabel[1]->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_ScoreLabel[1]->SetFont(g_pResources->GetSize20Font());
	m_ScoreLabel[1]->SetText("0000");
	m_ScoreLabel[1]->m_Color = CColor(0,0,0,255);
	m_ScoreLabel[1]->m_Angle = 180.0f;
	m_ScoreLabel[1]->m_ScaleX = m_XGraphicsScale;
	m_ScoreLabel[1]->m_ScaleY = m_YGraphicsScale;
	AddChild(m_ScoreLabel[1]);

	// Create the time text
	m_TimeLabel[1] = new CLabel();
	m_TimeLabel[1]->m_X = kPlayer2TimeTextX*m_XGraphicsScale + (kLabelWidth*m_XGraphicsScale)/2;
	m_TimeLabel[1]->m_Y = kPlayer2TimeTextY*m_YGraphicsScale + (kLabelHeight*m_YGraphicsScale)/2;
	m_TimeLabel[1]->m_H = kLabelHeight;
	m_TimeLabel[1]->m_W = kLabelWidth;
	m_TimeLabel[1]->m_AnchorX = 0.5f;
	m_TimeLabel[1]->m_AnchorY = 0.5f;
	m_TimeLabel[1]->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
	m_TimeLabel[1]->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_TimeLabel[1]->SetFont(g_pResources->GetSize20Font());
	m_TimeLabel[1]->SetText("02:00");
	m_TimeLabel[1]->m_Color = CColor(0,0,0,255);
	m_TimeLabel[1]->m_Angle = 180.0f;
	m_TimeLabel[1]->m_ScaleX = m_XGraphicsScale;
	m_TimeLabel[1]->m_ScaleY = m_YGraphicsScale;
	AddChild(m_TimeLabel[1]);

}

void MultiplayerGameScene::InitButtons()
{
	m_SettingsButton = new CSprite();
	m_SettingsButton->m_X = (float)IwGxGetScreenWidth() / 2;
	m_SettingsButton->m_Y = (float)IwGxGetScreenHeight() / 2;
	m_SettingsButton->SetImage(g_pResources->GetSettingsButton());
	m_SettingsButton->m_H = m_SettingsButton->GetImage()->GetHeight();
	m_SettingsButton->m_W = m_SettingsButton->GetImage()->GetWidth();
	m_SettingsButton->m_AnchorX = 0.5f;
	m_SettingsButton->m_AnchorY = 0.5f;
	float buttonScale = (50 / m_SettingsButton->m_H);
	m_SettingsButton->m_ScaleX = (buttonScale * m_XGraphicsScale);
	m_SettingsButton->m_ScaleY = (buttonScale * m_YGraphicsScale);
	AddChild(m_SettingsButton);
}

void MultiplayerGameScene::AddGridToScene(std::vector<CharacterBuilder> &characterTypes, int player)
{
	float x = 0;
	float y = 0;
	float xOffset = 0;
	float yOffset = 0;
	if(0 == player)
	{
		xOffset = kPlayer1StarXOffset*m_XGraphicsScale;
		yOffset = kPlayer1StarYOffset*m_YGraphicsScale;
	}
	else
	{
		xOffset = kPlayer2StarXOffset*m_XGraphicsScale;
		yOffset = kPlayer2StarYOffset*m_YGraphicsScale;
	}
	y = yOffset;
	for( int row = 0; row < m_GridElements.gridHeight; row++ )
	{
		x = xOffset;
		for( int column = 0; column < m_GridElements.gridWidth; column++ )
		{
			int characterTypeIndex = rand() % characterTypes.size();
			GridItem* grid = new GridItem( x, y, characterTypes.at(characterTypeIndex));
			characterTypes.erase(characterTypes.begin() + characterTypeIndex);
			m_Grid[player][(row*m_GridElements.gridWidth)+column] = grid; 
			if(1 == player)
			{
				grid->GetStarSprite()->m_Angle = 180.0f;
				grid->GetCharacterSprite()->m_Angle = 180.0f;
			}
			grid->GetStarSprite()->m_ScaleX = (kStarSize / (grid->GetStarSprite()->m_W)) * m_XGraphicsScale;
			grid->GetStarSprite()->m_ScaleY = (kStarSize / (grid->GetStarSprite()->m_H)) * m_XGraphicsScale;
			
			float characterScale = kStarSize / (grid->GetCharacterSprite()->m_H);
			grid->GetCharacterSprite()->m_ScaleX = characterScale*m_XGraphicsScale;
			grid->GetCharacterSprite()->m_ScaleY = characterScale*m_YGraphicsScale;
			AddChild( grid->GetStarSprite() );
			AddChild(grid->GetCharacterSprite());

			x += kStarXSpacing*m_XGraphicsScale;
		}

		y += kStarYSpacing*m_YGraphicsScale;
	}
}