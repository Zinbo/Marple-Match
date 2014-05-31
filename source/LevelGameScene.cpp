/*
 * (C) 2014 Search for a Star
 * 
 */

#include "LevelGameScene.h"
#include <math.h>
#include <iostream>
#include "GameSceneManager.h"

using namespace SFAS2014;

const float LevelGameScene::kTimeTextX = 7.0f;
const float LevelGameScene::kTimeTextY = 25.0f;

const float LevelGameScene::kScoreTextX = 213.0f;
const float LevelGameScene::kScoreTextY = 25.0f;

const float LevelGameScene::kLabelHeight = 20.0f;
const float LevelGameScene::kLabelWidth = 100.0f;

const float LevelGameScene::kStarXOffset = 61.0f;
const float LevelGameScene::kStarYOffset = 111.0f;
const float LevelGameScene::kStarSpacing = 66.0f;
const float LevelGameScene::kButtonSpacing = 50.0f;
const float LevelGameScene::kButtonStartingX = 1.0f;
const float LevelGameScene::kButtonStartingY = 1.0f;

const float LevelGameScene::kUpdateToScoreX = 160.0f;
const float LevelGameScene::kUpdateToScoreY = 55.0f;
const float LevelGameScene::kUpdateToScoreHeight = 15.0f;
const float LevelGameScene::kUpdateToScoreWidth = 150.0f;

const float LevelGameScene::kUpdateToTimeX = 10.0f;
const float LevelGameScene::kUpdateToTimeY = 55.0f;
const float LevelGameScene::kUpdateToTimeHeight = 15.0f;
const float LevelGameScene::kUpdateToTimeWidth = 150.0f;

const int LevelGameScene::Level::ratioLookUp[][2] = {{2, 2}, {4, 2}, {4, 3}, {4, 4}, {5, 4}, {6, 4}};

LevelGameScene::LevelGameScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingsMenu) 
	: GameScene(1, xGraphicsScale, yGraphicsScale, settingsMenu, 60.0f), m_ActiveLevel(0), noOfLevels(36),
	m_TotalNumberOfPairs(0)
	
{
	m_GridElements.gridHeight = 6;
	m_GridElements.gridWidth = 4;

	IwRandSeed( time( 0 ) );

	Create();
	InitLevels();
	
	Clear();
	m_Time = m_Levels[0].timeLimit;

	rand();

}

void LevelGameScene::Init()
{
	GameScene::Init();

	InitDialogs();
}

void LevelGameScene::InitLevels()
{
	m_Levels.reserve(noOfLevels);
	int counter = 0;
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			for(int k = 0; k < 6; k++)
			{
				int noPerBoard = (k+1)*2;
				int noToMatch = (j+2)*5;
				int timeLimit = (2 - i)*60;
				m_Levels[counter] = Level(timeLimit, noToMatch, noPerBoard);
				counter++;
			}
		}
	}
}

void LevelGameScene::InitGameOverDialog()
{
	//Init GameOver
	m_GameOverDialog = new GameOverDialog();
	m_GameOverDialog->m_X = 10*m_XGraphicsScale;
	m_GameOverDialog->m_Y = 90*m_XGraphicsScale;
	m_GameOverDialog->SetImage(g_pResources->GetGameOverDialog());
	m_GameOverDialog->m_H = m_GameOverDialog->GetImage()->GetHeight();
	m_GameOverDialog->m_W = m_GameOverDialog->GetImage()->GetWidth();
	//Get scale
	float dialogScale = (300 / m_GameOverDialog->m_H);
	m_GameOverDialog->m_ScaleX = (dialogScale * m_XGraphicsScale);
	m_GameOverDialog->m_ScaleY = (dialogScale * m_YGraphicsScale);
	m_GameOverDialog->m_IsVisible = false;

	AddChild(m_GameOverDialog);
}

void LevelGameScene::InitGameStartDialog()
{
	//Init GameStart
	m_GameStartDialog = new GameStartDialog();
	m_GameStartDialog->m_X = 10*m_XGraphicsScale;
	m_GameStartDialog->m_Y = 90*m_XGraphicsScale;
	m_GameStartDialog->SetImage(g_pResources->GetGameStartDialog());
	m_GameStartDialog->m_H = m_GameStartDialog->GetImage()->GetHeight();
	m_GameStartDialog->m_W = m_GameStartDialog->GetImage()->GetWidth();
	float dialogScale = (300 / m_GameOverDialog->m_H);
	m_GameStartDialog->m_ScaleX = (dialogScale * m_XGraphicsScale);
	m_GameStartDialog->m_ScaleY = (dialogScale * m_YGraphicsScale);

	//Show game start dialog
	m_GameStartDialog->m_IsVisible = true;
	m_GameState = keGameStart;
	int minutes, seconds;
	minutes = (int)( m_Levels[m_ActiveLevel].timeLimit / 60 );
	seconds = (int)( m_Levels[m_ActiveLevel].timeLimit - ( minutes * 60.0f ) );
	char timeBuffer[256];
	sprintf(timeBuffer, "%.2d:%.2d minutes", minutes, seconds );

	char matchBuffer[10];
	char pairBuffer[15];
	sprintf(matchBuffer, "%i Pairs", m_Levels[m_ActiveLevel].noOfMatchesToWin);
	sprintf(pairBuffer, "%i Per Board", m_Levels[m_ActiveLevel].noOfPairsPerBoard);

	m_GameStartDialog->GetTimeLabel()->SetText(timeBuffer);
	m_GameStartDialog->GetMatchLabel()->SetText(matchBuffer);
	m_GameStartDialog->GetPairLabel()->SetText(pairBuffer);

	AddChild(m_GameStartDialog);
}

void LevelGameScene::InitLevelWonDialog()
{
	//Init Level Cleared Dialog
	m_LevelClearedDialog = new LevelClearedDialog();
	m_LevelClearedDialog->m_X = 10*m_XGraphicsScale;
	m_LevelClearedDialog->m_Y = 90*m_XGraphicsScale;
	m_LevelClearedDialog->SetImage(g_pResources->GetLevelWonDialog());
	m_LevelClearedDialog->m_H = m_LevelClearedDialog->GetImage()->GetHeight();
	m_LevelClearedDialog->m_W = m_LevelClearedDialog->GetImage()->GetWidth();
	float dialogScale = (300 / m_LevelClearedDialog->m_H);
	m_LevelClearedDialog->m_ScaleX = (dialogScale * m_XGraphicsScale);
	m_LevelClearedDialog->m_ScaleY = (dialogScale * m_YGraphicsScale);
	m_LevelClearedDialog->m_IsVisible = false;

	AddChild(m_LevelClearedDialog);
}

void LevelGameScene::InitExitDialog()
{
	//Init Game Exit Dialog
	m_ExitGameDialog = new CSprite();
	m_ExitGameDialog->m_X = 10*m_XGraphicsScale;
	m_ExitGameDialog->m_Y = 90*m_XGraphicsScale;
	m_ExitGameDialog->SetImage(g_pResources->GetExitGameDialog());
	m_ExitGameDialog->m_H = m_ExitGameDialog->GetImage()->GetHeight();
	m_ExitGameDialog->m_W = m_ExitGameDialog->GetImage()->GetWidth();
	m_ExitGameDialog->m_IsVisible = false;

	//add score board button to game over dialog
	CSprite* confirmButton = new CSprite();
	confirmButton->m_X = 35*m_XGraphicsScale;
	confirmButton->m_Y = 45*m_XGraphicsScale;
	confirmButton->SetImage(g_pResources->GetConfirmButton());
	confirmButton->m_H = confirmButton->GetImage()->GetHeight();
	confirmButton->m_W = confirmButton->GetImage()->GetWidth();
	m_ExitGameDialog->AddChild(confirmButton);

	//add score board button to game over dialog
	CSprite* cancelButton = new CSprite();
	cancelButton->m_X = 215*m_XGraphicsScale;
	cancelButton->m_Y = 45*m_XGraphicsScale;
	cancelButton->SetImage(g_pResources->GetCancelButton());
	cancelButton->m_H = cancelButton->GetImage()->GetHeight();
	cancelButton->m_W = cancelButton->GetImage()->GetWidth();
	m_ExitGameDialog->AddChild(cancelButton);

	AddChild(m_ExitGameDialog);
}

void LevelGameScene::InitDialogs()
{
	InitGameOverDialog();
	InitGameStartDialog();
	InitLevelWonDialog();
	InitExitDialog();	
}

void LevelGameScene::InitBoard()
{
	for(int i = 0; i < m_NoOfPlayers; i++)
	{
		std::vector<CharacterBuilder> characterTypes;
		SetupCharactersArray(characterTypes);
		AddGridToScene(characterTypes, i);
	}
}

void LevelGameScene::ResetBoard(int player)
{
	std::vector<CharacterBuilder> characterTypes;
	SetupCharactersArray(characterTypes);	
	ResetGrid(characterTypes, player);
}

void LevelGameScene::ResetGrid(std::vector<CharacterBuilder> characterTypes, int player)
{
	int width = Level::ratioLookUp[m_ActiveLevel % 6][0];
	int height = Level::ratioLookUp[m_ActiveLevel % 6][1];
	for(int i = 0; i < width*height; i++)
	{
		int characterTypeIndex = rand() % characterTypes.size();
		
		CharacterBuilder charToMake = characterTypes.at(characterTypeIndex);
		m_Grid[player][i]->GetStarSprite()->m_IsVisible = true;
		m_Grid[player][i]->SetCharacterImage(charToMake);

		float characterScale = kStarSize / (m_Grid[player][i]->GetCharacterSprite()->m_H);
		m_Grid[player][i]->GetCharacterSprite()->m_ScaleX = characterScale*m_XGraphicsScale;
		m_Grid[player][i]->GetCharacterSprite()->m_ScaleY = characterScale*m_YGraphicsScale;

		AddChild(m_Grid[player][i]->GetCharacterSprite());

		characterTypes.erase(characterTypes.begin() + characterTypeIndex);
	}
}

void LevelGameScene::SetupCharactersArray(std::vector<CharacterBuilder> &characterTypes)
{
	int width = Level::ratioLookUp[m_ActiveLevel % 6][0];
	int height = Level::ratioLookUp[m_ActiveLevel % 6][1];
	//Fill vector with exactly 2 of each character type
	int numberOfPairs = (width*height)/2;
	for(int i = 0; i < numberOfPairs; i++)
	{
		CharacterBuilder charToMake(i);
		float randNum = ((float) rand() / RAND_MAX );
		if(randNum <= kGoldProb)
		{
			charToMake.SetGold(true);
		}
		else if(randNum <= kSilverProb)
		{
			charToMake.SetSilver(true);
		}
		characterTypes.push_back(charToMake);
		characterTypes.push_back(charToMake);
	}
}

void LevelGameScene::AddGridToScene(std::vector<CharacterBuilder> &characterTypes, int player)
{
	float x = kStarXOffset*m_XGraphicsScale;
	float y = kStarYOffset*m_YGraphicsScale;

	int width = Level::ratioLookUp[m_ActiveLevel % 6][0];
	int height = Level::ratioLookUp[m_ActiveLevel % 6][1];

	for( int row = 0; row < width; row++ )
	{
		x = kStarXOffset*m_XGraphicsScale;
		for( int column = 0; column < height; column++ )
		{
			int characterTypeIndex = rand() % characterTypes.size();
			GridItem* grid = new GridItem( x, y, characterTypes.at(characterTypeIndex));
			characterTypes.erase(characterTypes.begin() + characterTypeIndex);

			m_Grid[0][(row*height)+column] = grid; 
			AddChild( grid->GetStarSprite() );
			AddChild(grid->GetCharacterSprite());

			x += kStarSpacing*m_XGraphicsScale;
		}

		y += kStarSpacing*m_YGraphicsScale;
	}
}

void LevelGameScene::InitButtons()
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

void LevelGameScene::ResetDoublePoints(Timer* timer, void* userData)
{
	LevelGameScene* self = (LevelGameScene*) userData;
	self->m_DoublePoints[0] = false;
}

void LevelGameScene::InitUI()
{
	//Add background
	m_Background = new CSprite();
	m_Background->m_X = 0;
	m_Background->m_Y = 0;
	m_Background->SetImage(g_pResources->GetGameBackground());
	m_Background->m_W = m_Background->GetImage()->GetWidth();
	m_Background->m_H = m_Background->GetImage()->GetHeight();
	/*m_Background->m_Color.r = 255;
	m_Background->m_Color.b = 50;
	m_Background->m_Color.g = 50;*/

	// Fit background to screen size
	m_Background->m_ScaleX = (float)IwGxGetScreenWidth() / m_Background->m_W;
	m_Background->m_ScaleY = (float)IwGxGetScreenHeight() / m_Background->m_H;
	AddChild(m_Background);
}

void LevelGameScene::UpdateLabels()
{
	int minutes, seconds;
	minutes = (int)( m_Time / 60 );
	seconds = (int)( m_Time - ( minutes * 60.0f ) );
	char timeBuffer[256];
	sprintf(timeBuffer, "%.2d:%.2d", minutes, seconds );

	char scoreBuffer[6];
	sprintf(scoreBuffer, "%d/%d", m_TotalNumberOfPairs, m_Levels[m_ActiveLevel].noOfMatchesToWin);

	m_ScoreLabel[0]->SetText(scoreBuffer);
	m_TimeLabel[0]->SetText(timeBuffer);
}

void LevelGameScene::InitLabels()
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

void LevelGameScene::ExitScene()
{
	m_Timers.Cancel(m_DoublePointsTimer[0]);
	m_DoublePointsTimer[0] = NULL;
	m_FirstSelectedItem[0] = NULL;
	m_SecondSelectedItem[0] = NULL;
	ResultsScene * resultsScene= (ResultsScene*) m_Manager->Find("ResultsState");
	Audio::StopMusic();
	m_Manager->SwitchTo(resultsScene);	
	m_NoOfMatchedPairs[0] = 0;
}

void LevelGameScene::RemoveCharactersAfterDelay(int player)
{
	m_CharactersToRemove[player].push_back(m_FirstSelectedItem[player]);
	m_CharactersToRemove[player].push_back(m_SecondSelectedItem[player]);
	if(0 ==player)
	{
		m_Timers.Add(new Timer(0.5f, 1, &LevelGameScene::remove_player_1_matched_characters, (void*)this));
	}
	else
	{
		m_Timers.Add(new Timer(0.5f, 1, &LevelGameScene::remove_player_2_matched_characters, (void*)this));
	}
	m_FirstSelectedItem[player] = NULL;
	m_SecondSelectedItem[player] = NULL;
	
}

void LevelGameScene::remove_player_1_matched_characters(Timer* timer, void* userData)
{
	LevelGameScene * self = (LevelGameScene*)userData;
	//Remove characters from scene and from list of characters to remove.
	self->RemoveMatchedCharacterPairFromList(0);

	self->m_NoOfMatchedPairs[0]++;
	self->m_TotalNumberOfPairs++;

	//If the player has matched 12 pairs then reset the board
	int a =  (self->m_Levels[self->m_ActiveLevel].noOfPairsPerBoard);
	int b =  self->m_NoOfMatchedPairs[0];
	if(self->m_Levels[self->m_ActiveLevel].noOfMatchesToWin == self->m_TotalNumberOfPairs)
	{
		self->m_GameState = keGameWon;
		self->m_LevelClearedDialog->m_IsVisible = true;
		char scoreBuffer[5];
		sprintf(scoreBuffer, "%.4d", ((GameSceneManager*) self->m_Manager)->GetScore(0) );

		self->m_LevelClearedDialog->GetScoreLabel()->SetText(scoreBuffer);
		
		//Need to remove and add level cleared so that it displays in front..?
		self->RemoveChild(self->m_LevelClearedDialog);
		self->AddChild(self->m_LevelClearedDialog);
	}
	if((self->m_Levels[self->m_ActiveLevel].noOfPairsPerBoard) == self->m_NoOfMatchedPairs[0])
	{
		g_pAudio->PlaySound(g_pResources->GetBoardCompleteSoundFilename());
		self->m_NoOfMatchedPairs[0] = 0;
		self->ResetBoard(0);
	}
	
}

void LevelGameScene::Update(float deltaTime, float alphaMul)
{
	//if not current scene, don't bother updating.
	if(!(m_Manager->GetCurrent() == this))
	{
		return;
	}
	Scene::Update(deltaTime, alphaMul);

	if( m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		SettingsMenuHitTest();
	}

	//call the right method for the correct game state
	switch(m_GameState)
	{
	case keGameStart:
		if(GameStartButtonPressed())
		{
			m_GameStartDialog->m_IsVisible = false;
			//ClearBoard();
			
			m_GameState = keGamePlaying;
			
			m_Time = m_Levels[m_ActiveLevel].timeLimit;
			m_TotalNumberOfPairs = 0;

			m_DoublePoints[0] = false;
			m_TriplePoints[0] = false;
			m_Delayed[0] = false;

			m_FirstSelectedItem[0] = NULL;
			m_SecondSelectedItem[0] = NULL;
			for(std::vector<GridItem*>::iterator it = m_CharactersToRemove[0].begin(); it != m_CharactersToRemove[0].end(); ++it)
			{ 
				*it = NULL;
			}
			m_NoOfMatchedPairs[0] = 0;
			m_DelayTime[0] = 0;
			if(m_DoublePointsTimer[0])
			{
				m_Timers.Cancel(m_DoublePointsTimer[0]);
				m_DoublePointsTimer[0] = NULL;
			}
			if(m_TriplePointsTimer[0])
			{
				m_Timers.Cancel(m_TriplePointsTimer[0]);
				m_TriplePointsTimer[0] = NULL;
			}

			InitBoard();

		}
		break;
	case keGamePlaying:
		for(int i = 0; i < m_NoOfPlayers; i++)
		{
			if(m_Delayed[i])
			{
				DelayGameForNonmatch(deltaTime, i);
			}
		}
		CheckForAnyMatches();
		UpdateTime(deltaTime);
		UpdateLabels();
		break;
	case keGameWon:
		if(NextLevelButtonPressed())
		{
			ClearBoard();
			m_LevelClearedDialog->m_IsVisible = false;
			m_GameStartDialog->m_IsVisible = true;
			m_ActiveLevel++;
			m_GameState = keGameStart;

			int minutes, seconds;
			minutes = (int)( m_Levels[m_ActiveLevel].timeLimit / 60 );
			seconds = (int)( m_Levels[m_ActiveLevel].timeLimit - ( minutes * 60.0f ) );
			char timeBuffer[256];
			sprintf(timeBuffer, "%.2d:%.2d minutes", minutes, seconds );

			char matchBuffer[10];
			char pairBuffer[15];
			sprintf(matchBuffer, "%i Pairs", m_Levels[m_ActiveLevel].noOfMatchesToWin);
			sprintf(pairBuffer, "%i Per Board", m_Levels[m_ActiveLevel].noOfPairsPerBoard);

			m_GameStartDialog->GetTimeLabel()->SetText(timeBuffer);
			m_GameStartDialog->GetMatchLabel()->SetText(matchBuffer);
			m_GameStartDialog->GetPairLabel()->SetText(pairBuffer);

		}
	case keGameOver:
		if(ScoreButtonPressed())
		{
			m_GameState = keGameStart;
			ExitScene();
		}
	}
	
	//If the user has clicked elsewhere just swallow the touch
	if( m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		g_pInput->Reset();
	}
}

bool LevelGameScene::ScoreButtonPressed()
{
	if(m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched &&
		m_GameOverDialog->m_IsVisible && m_GameOverDialog->GetScoreButton()->HitTest(g_pInput->m_X, g_pInput->m_Y))
	{
		return true;
	}
	return false;
}


void LevelGameScene::UpdateTime(float deltaTime)
{
	// If a minute has gone by, or we're in the final 10 seconds of the game, then beep to alert the user.
	if((m_Time < keTimeLimit) && 
		AMinuteHasGoneBy(deltaTime) || 
		InTheFinal10Seconds(deltaTime))
	{
		g_pAudio->PlaySound(g_pResources->GetTimeSoundFilename());
	}
	
	//If there is no time left, then clean up a few variables and change to the results scene
	if( ( m_Time) <= 0 )
	{
		m_GameState = keGameOver;
		m_GameOverDialog->m_IsVisible = true;
		char scoreBuffer[5];
		sprintf(scoreBuffer, "%.4d", ((GameSceneManager*) m_Manager)->GetScore(0) );

		m_GameOverDialog->GetScoreLabel()->SetText(scoreBuffer);
	}

	//Update the timer
	m_Time -= deltaTime;
}

void LevelGameScene::ClearBoard()
{
	int width = Level::ratioLookUp[m_ActiveLevel % 6][0];
	int height = Level::ratioLookUp[m_ActiveLevel % 6][1];

	for(int i = 0; i < width*height; i++)
	{
		if(m_Grid[0][i] != 0)
		{
			CSprite * chara = m_Grid[0][i]->GetCharacterSprite();
			CSprite * star = m_Grid[0][i]->GetStarSprite();

			//If the character hasn't already been removed from the scene then remove them
			if(IsChild(chara))
			{
			RemoveChild(chara);
			}
			if(IsChild(star))
			{
				RemoveChild(star);
			}
			
			delete m_Grid[0][i];
			m_Grid[0][i] = NULL;
		}
	}
}

bool LevelGameScene::NextLevelButtonPressed()
{
	if(m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched &&
		m_LevelClearedDialog->m_IsVisible && m_LevelClearedDialog->GetNextLevelButton()->HitTest(g_pInput->m_X, g_pInput->m_Y))
	{
		return true;
	}
	return false;
}

bool LevelGameScene::GameStartButtonPressed()
{
	if(m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched &&
		m_GameStartDialog->m_IsVisible && m_GameStartDialog->GetStartButton()->HitTest(g_pInput->m_X, g_pInput->m_Y))
	{
		return true;
	}
	return false;
}

void LevelGameScene::CheckGridForMatch(int player)
{
	if(!m_Delayed[player])
	{
		for(int gridIndex = 0; gridIndex < m_Levels[m_ActiveLevel].noOfPairsPerBoard*2; gridIndex++ )
		{
			if(StarHasBeenTouched(m_Grid[player][gridIndex]))
			{
				//if the star has been touched then show the character underneath. If the player has already selected a star
				//then see if we have a match or not. Else set m_FirstSelectedItem to the touched star
				ShowCharacter(m_Grid[player][gridIndex]);
			
				if(m_FirstSelectedItem[player])
				{
					m_SecondSelectedItem[player] = m_Grid[player][gridIndex];
					//If the character indexes match up, then we have a normal, silver or gold match
					if(m_FirstSelectedItem[player]->GetCharacterIndex() ==  m_Grid[player][gridIndex]->GetCharacterIndex())
					{
						ProcessMatch(player);
					}
					//If the character indexes don't match, but the player has selected two characters which are both gold or both silver, then we have an odd match,
					//which we need to handle a little differently.
					else if((m_FirstSelectedItem[player]->IsGold() && m_SecondSelectedItem[player]->IsGold()) || (m_FirstSelectedItem[player]->IsSilver() && m_SecondSelectedItem[player]->IsSilver()))
					{
						ProcessOddPowerupMatch(player);
					}
					//Else we have no match
					else
					{
						ProcessIncorrectMatch(player);
					}
				}
				else
				{
					m_FirstSelectedItem[player] = m_Grid[player][gridIndex];
				}	
				break;
			
			}
		}
	}
	
}