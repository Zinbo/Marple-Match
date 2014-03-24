/*
 * (C) 2014 Search for a Star
 * 
 */

#include "GameScene.h"

#define TIME_TEXT_X 7.0f
#define TIME_TEXT_Y 25.0f
#define SCORE_TEXT_X 213.0f
#define SCORE_TEXT_Y 25.0f
#define TIME_TEXT_HEIGHT 20.0f
#define TIME_TEXT_WIDTH 100.0f
#define STAR_X_OFFSET 61.0f
#define STAR_Y_OFFSET 111.0f
#define STAR_SPACING 66.0f
#define BUTTON_SPACING 50.0f
#define BUTTON_STARTING_X 1.0f
#define BUTTON_STARTING_Y 1.0f
#define GOLD_PROB 0.1
#define SILVER_PROB 0.2

#define UPDATE_TO_SCORE_X 160.0f
#define UPDATE_TO_SCORE_Y 55.0f
#define UPDATE_TO_SCORE_HEIGHT 15.0f
#define UPDATE_TO_SCORE_WIDTH 150.0f

#define UPDATE_TO_TIME_X 10.0f
#define UPDATE_TO_TIME_Y 55.0f
#define UPDATE_TO_TIME_HEIGHT 15.0f
#define UPDATE_TO_TIME_WIDTH 150.0f

using namespace SFAS2014;

//
//
// GameScene class
//
//
GameScene::GameScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingMenu) 
	: m_Time((float) TimeLimit), m_DoublePointsTimer(NULL), m_FirstSelectedItem(NULL), 
	m_SecondSelectedItem(NULL), m_DelayTime(0), m_DoublePoints(false),
	m_GameState(keGamePlaying), m_NoOfMatchedPairs(0)
	
{
	IwRandSeed( time( 0 ) );
	m_XGraphicsScale = xGraphicsScale;
	m_YGraphicsScale = yGraphicsScale;
	m_SettingsMenu = settingMenu;
}

GameScene::~GameScene()
{
	delete m_DoublePointsTimer;

	for(int i = 0; i < GridHeight*GridWidth; i++)
	{
		if(m_Grid[i] !=0)
		{
			delete m_Grid[i];
		}
	}
}

void GameScene::Init()
{
	Scene::Init();

	//Initialise background
	InitUI();

	//Initialise buttons for controlling sound and music
	InitButtons();

	//Initialise labels for score and time
	InitLabels();

	//Initialise sound engine
	InitSound();

	//Initialise the game board
	InitBoard();

}

void GameScene::Reset()
{
	Scene::Reset();
	if(m_GameState = keGameOver)
	{
		ResetBoard();
	}
	
	m_Time = (float)TimeLimit;
	((GameSceneManager*) m_Manager)->SetScore(0, 0);
	Audio::PlayMusic(g_pResources->GetGameMusicFilename(), true);
	UpdateLabels();
	//If the sound and music has been turned off in another scene then set the buttons on this scene to reflect this.
	//SetSoundAndMusicButtons();
	
}

void GameScene::Update(float deltaTime, float alphaMul)
{
	//if not current scene, don't bother updating.
	if(!(m_Manager->GetCurrent() == this))
	{
		return;
	}
	Scene::Update(deltaTime, alphaMul);

	if( m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		if(m_SettingsMenu->m_IsVisible && m_SettingsMenu->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			ToggleButtons();
		}
		else if(m_SettingsButton->HitTest(g_pInput->m_X, g_pInput->m_Y) || m_SettingsMenu->m_IsVisible)
		{
			ToggleSettingMenu();
		}
	}

	//call the right method for the correct game state
	switch(m_GameState)
	{
	case keGameOver:
		m_GameState = keGamePlaying;
		break;
	case keGamePlaying:
		CheckForMatches();
		UpdateTime(deltaTime);
		UpdateLabels();
		FadeLabels();
		break;
	case keNonMatch:
		DelayGameForNonmatch(deltaTime);
		UpdateTime(deltaTime);
		UpdateLabels();
		FadeLabels();
		break;
	}
	
}

void GameScene::UpdateTime(float deltaTime)
{
	// If a minute has gone by, or we're in the final 10 seconds of the game, then beep to alert the user.
	if((m_Time < TimeLimit) && 
		AMinuteHasGoneBy(deltaTime) || 
		InTheFinal10Seconds(deltaTime))
	{
		g_pAudio->PlaySound(g_pResources->GetTimeSoundFilename());
	}
	
	//If there is no time left, then clean up a few variables and change to the results scene
	if( ( m_Time) <= 0 )
	{
		CleanUpAndChangeScene();
	}

	//Update the timer
	m_Time -= deltaTime;
}

void GameScene::Render()
{
	Scene::Render();
}

void GameScene::SetupCharactersArray(std::vector<CharacterBuilder> &characterTypes)
{
	//Fill vector with exactly 2 of each character type
	int numberOfPairs = (GridHeight*GridWidth)/2;
	for(int i = 0; i < numberOfPairs; i++)
	{
		CharacterBuilder charToMake(i);
		float randNum = ((float) rand() / RAND_MAX );
		if(randNum <= GOLD_PROB)
		{
			charToMake.SetGold(true);
		}
		else if(randNum <= SILVER_PROB)
		{
			charToMake.SetSilver(true);
		}
		characterTypes.push_back(charToMake);
		characterTypes.push_back(charToMake);
	}
}

void GameScene::FadeLabels()
{
	//Fade score bonus
	int scoreAlpha = m_UpdateToScoreLabel->m_Color.a;
	if(scoreAlpha > 0)
	{
		scoreAlpha -= 5;
	}
	if(scoreAlpha < 0)
	{
		scoreAlpha = 0;
	}
	m_UpdateToScoreLabel->m_Color = CColor(0, 0, 0, scoreAlpha);

	//Fade time bonus

	int timeAlpha = m_UpdateToTimeLabel->m_Color.a;
	if(timeAlpha > 0)
	{
		timeAlpha -= 5;
	}
	if(timeAlpha < 0)
	{
		timeAlpha = 0;
	}
	m_UpdateToTimeLabel->m_Color = CColor(0, 0, 0, timeAlpha);
}

void GameScene::AddGridToScene(std::vector<CharacterBuilder> &characterTypes)
{
	float x = STAR_X_OFFSET*m_XGraphicsScale;
	float y = STAR_Y_OFFSET*m_YGraphicsScale;
	for( int row = 0; row < GridHeight; row++ )
	{
		x = STAR_X_OFFSET*m_XGraphicsScale;
		for( int column = 0; column < GridWidth; column++ )
		{
			int characterTypeIndex = rand() % characterTypes.size();
			GridItem* grid = new GridItem( x, y, characterTypes.at(characterTypeIndex));
			characterTypes.erase(characterTypes.begin() + characterTypeIndex);

			m_Grid[(row*GridWidth)+column] = grid; 
			AddChild( grid->GetStarSprite() );
			AddChild(grid->GetCharacterSprite());

			x += STAR_SPACING*m_XGraphicsScale;
		}

		y += STAR_SPACING*m_YGraphicsScale;
	}
}

void GameScene::InitBoard()
{
	std::vector<CharacterBuilder> characterTypes;
	SetupCharactersArray(characterTypes);	
	AddGridToScene(characterTypes);
}

void GameScene::ProcessGoldMatch()
{
	g_pAudio->PlaySound(g_pResources->GetGoldPickupSoundFilename());
	if(m_DoublePoints)
	{
		DisplayUpdateToScore("+50x2 Gold Match!");
		IncrementScore(100);
	}
	else
	{
		DisplayUpdateToScore("+50 Gold Match!");
		IncrementScore(50);
	}
	
	m_Time += 20;
}

void GameScene::ProcessSilverMatch()
{
	g_pAudio->PlaySound(g_pResources->GetSilverPickupSoundFilename());
	m_DoublePoints = true;
	if(m_DoublePointsTimer != NULL)
	{
		m_Timers.Cancel(m_DoublePointsTimer);
		m_DoublePointsTimer = NULL;
		DisplayUpdateToScore("+20x2 Silver Match!");
		IncrementScore(40);
	}
	else
	{
		DisplayUpdateToScore("+20 Silver Match!");
		IncrementScore(20);
	}
	m_DoublePointsTimer = new Timer(10.0f, 1, &GameScene::ResetDoublePoints, (void*)this);
	m_Timers.Add(m_DoublePointsTimer);
}

void GameScene::ProcessNormalMatch()
{
	g_pAudio->PlaySound(g_pResources->GetMatchSoundFilename());
	if(m_DoublePoints)
	{
		DisplayUpdateToScore("+10x2 Match!");
		IncrementScore(20);
	}
	else
	{
		DisplayUpdateToScore("+10 Match!");
		IncrementScore(10);
	}
	
}

void GameScene::IncrementScore(int amount)
{
	((GameSceneManager*) m_Manager)->IncrementScore(amount, 0);
}

void GameScene::RemoveCharactersAfterDelay()
{
	m_CharactersToRemove.push_back(m_FirstSelectedItem);
	m_CharactersToRemove.push_back(m_SecondSelectedItem);
	m_FirstSelectedItem = NULL;
	m_SecondSelectedItem = NULL;
	m_Timers.Add(new Timer(0.5f, 1, &GameScene::RemoveMatchedCharacters, (void*)this));
}

void GameScene::ProcessMatch()
{
	//Both characters have to both be gold, both be silver, or both be the same normal character
	if((m_FirstSelectedItem->IsGold() == m_SecondSelectedItem->IsGold())  && (m_FirstSelectedItem->IsSilver() == m_SecondSelectedItem->IsSilver()))
	{
		if(m_FirstSelectedItem->IsGold())
		{
			ProcessGoldMatch();
		}
		else if(m_FirstSelectedItem->IsSilver())
		{
			ProcessSilverMatch();
		}
		else
		{
			ProcessNormalMatch();
		}
					
		RemoveCharactersAfterDelay();
	}
}

bool GameScene::StarHasBeenTouched(int gridIndex)
{
	return (m_Grid[gridIndex]->GetStarSprite()->m_IsVisible && m_Grid[gridIndex]->GetStarSprite()->HitTest( g_pInput->m_X, g_pInput->m_Y )); 
}

void GameScene::ShowCharacter(GridItem * gridItem)
{
	gridItem->GetStarSprite()->m_IsVisible = false;
	gridItem->GetCharacterSprite()->m_IsVisible = true;
}

void GameScene::ProcessIncorrectMatch()
{
	g_pAudio->PlaySound(g_pResources->GetNonmatchSoundFilename());
	m_DelayTime = 0.5f;
	m_GameState = keNonMatch;
}

void GameScene::ProcessOddPowerupMatch()
{
	//This is for the case where the player has matched up two gold or silver characters, but these characters have underlying different character indexes,
	//meaning that when they are matched and removed they will leave odd corresponding pairs. The second left over character is changed to have the same
	//character index as the first left over character, so that there are no odd characters left on the board.
	CharacterBuilder charToMake(m_FirstSelectedItem->GetCharacterIndex());
	charToMake.SetGold(m_FirstSelectedItem->IsGold());
	charToMake.SetSilver(m_FirstSelectedItem->IsSilver());
	FindOtherHalfOfPair(m_FirstSelectedItem)->RemovePowerup();
	FindOtherHalfOfPair(m_SecondSelectedItem)->SetCharacterImage(charToMake);

	//Then process match like normal
	ProcessMatch();
}

void GameScene::CheckForMatches()
{
	//If the screen has been touched, then cycle through each grid item and see if it has been touched.
	if(m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		for(int gridIndex = 0; gridIndex < GridWidth*GridHeight; gridIndex++ )
		{
			g_pInput->Reset();
			if(StarHasBeenTouched(gridIndex))
			{
				//if the star has been touched then show the character underneath. If the player has already selected a star
				//then see if we have a match or not. Else set m_FirstSelectedItem to the touched star
				ShowCharacter(m_Grid[gridIndex]);
				if(m_FirstSelectedItem)
				{
					m_SecondSelectedItem = m_Grid[gridIndex];
					//If the character indexes match up, then we have a normal, silver or gold match
					if(m_FirstSelectedItem->GetCharacterIndex() == m_Grid[gridIndex]->GetCharacterIndex())
					{
						ProcessMatch();
					}
					//If the character indexes don't match, but the player has selected two characters which are both gold or both silver, then we have an odd match,
					//which we need to handle a little differently.
					else if((m_FirstSelectedItem->IsGold() && m_SecondSelectedItem->IsGold()) || (m_FirstSelectedItem->IsSilver() && m_SecondSelectedItem->IsSilver()))
					{
						ProcessOddPowerupMatch();
					}
					//Else we have no match
					else
					{
						ProcessIncorrectMatch();
					}
				}
				else
				{
					m_FirstSelectedItem = m_Grid[gridIndex];
				}	
				break;
			}
		}
	}
}

void GameScene::HideCharacter(GridItem * gridItem)
{
	gridItem->GetCharacterSprite()->m_IsVisible = false;
	gridItem->GetStarSprite()->m_IsVisible = true;
}

void GameScene::DelayGameForNonmatch(float deltaTime)
{
	g_pInput->Reset();
	if(m_DelayTime <= 0)
	{
		if(m_FirstSelectedItem->IsGold() || m_FirstSelectedItem->IsSilver())
		{
			RemovePairsPowerUp(m_FirstSelectedItem);
			
		}
		else if(m_SecondSelectedItem->IsGold() || m_SecondSelectedItem->IsSilver())
		{
			RemovePairsPowerUp(m_SecondSelectedItem);
		}

		HideCharacter(m_FirstSelectedItem);
		m_FirstSelectedItem = NULL;

		HideCharacter(m_SecondSelectedItem);
		m_SecondSelectedItem = NULL;

		m_DelayTime = 0;
		m_GameState = keGamePlaying;
	}
	else
	{
		m_DelayTime -= deltaTime;	
	}
}

void GameScene::RemoveMatchedCharacterPairFromList()
{
	GridItem * char1 = m_CharactersToRemove.at(0);
	GridItem * char2 = m_CharactersToRemove.at(1);
	RemoveChild(char1->GetCharacterSprite());
	RemoveChild(char2->GetCharacterSprite());
	m_CharactersToRemove.erase(m_CharactersToRemove.begin());
	m_CharactersToRemove.erase(m_CharactersToRemove.begin());
}

void GameScene::RemoveMatchedCharacters(Timer* timer, void* userData)
{
	GameScene * self = (GameScene*)userData;
	//Remove characters from scene and from list of characters to remove.
	self->RemoveMatchedCharacterPairFromList();

	self->m_NoOfMatchedPairs++;

	//If the player has matched 12 pairs then reset the board.
	if(self->m_NoOfMatchedPairs == 12)
	{
		g_pAudio->PlaySound(g_pResources->GetBoardCompleteSoundFilename());
		self->m_NoOfMatchedPairs = 0;
		self->ResetBoard();
	}
	
}

void GameScene::ResetBoard()
{
	std::vector<CharacterBuilder> characterTypes;
	SetupCharactersArray(characterTypes);

	//Cycle through each grid item, make the star visible and add a new random character underneath
	for(int i = 0; i < GridHeight*GridWidth; i++)
	{
		int characterTypeIndex = rand() % characterTypes.size();
		
		CharacterBuilder charToMake = characterTypes.at(characterTypeIndex);
		m_Grid[i]->GetStarSprite()->m_IsVisible = true;
		m_Grid[i]->SetCharacterImage(charToMake);
		AddChild(m_Grid[i]->GetCharacterSprite());

		characterTypes.erase(characterTypes.begin() + characterTypeIndex);
	}
}

void GameScene::InitButtons()
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

GridItem * GameScene::FindOtherHalfOfPair(GridItem* gridItem)
{
	for(int i = 0; i < GridHeight*GridWidth; i++)
	{
		if(gridItem->GetCharacterIndex() == m_Grid[i]->GetCharacterIndex() && m_Grid[i] != gridItem)
		{
			return m_Grid[i];
		}
	}
}

void GameScene::RemovePairsPowerUp(GridItem * selected)
{
	selected->RemovePowerup();
	int charIndex = selected->GetCharacterIndex();

	FindOtherHalfOfPair(selected)->RemovePowerup();
	//Find the other half of the powerup pair and remove it.
	
}

void GameScene::ResetDoublePoints(Timer* timer, void* userData)
{
	GameScene* self = (GameScene*) userData;
	self->m_DoublePoints = false;
}

void GameScene::InitUI()
{
	//Add background
	m_Background = new CSprite();
	m_Background->m_X = 0;
	m_Background->m_Y = 0;
	m_Background->SetImage(g_pResources->getGameBackground());
	m_Background->m_W = m_Background->GetImage()->GetWidth();
	m_Background->m_H = m_Background->GetImage()->GetHeight();

	// Fit background to screen size
	m_Background->m_ScaleX = (float)IwGxGetScreenWidth() / m_Background->m_W;
	m_Background->m_ScaleY = (float)IwGxGetScreenHeight() / m_Background->m_H;
	AddChild(m_Background);
}

void GameScene::InitLabels()
{
	// Create the score text
	m_ScoreLabel = new CLabel();
	m_ScoreLabel->m_H = TIME_TEXT_HEIGHT*m_YGraphicsScale;
	m_ScoreLabel->m_W = TIME_TEXT_WIDTH*m_XGraphicsScale;
	m_ScoreLabel->m_X = SCORE_TEXT_X * m_XGraphicsScale;
	m_ScoreLabel->m_Y = SCORE_TEXT_Y * m_YGraphicsScale;
	m_ScoreLabel->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
	m_ScoreLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_ScoreLabel->SetFont(g_pResources->getSize20Font());
	m_ScoreLabel->SetText("0000");
	m_ScoreLabel->m_Color = CColor(0,0,0,255);
	m_ScoreLabel->m_ScaleX = m_XGraphicsScale;
	m_ScoreLabel->m_ScaleY = m_YGraphicsScale;
	AddChild(m_ScoreLabel);

	// Create the time text
	m_TimeLabel = new CLabel();
	m_TimeLabel->m_X = TIME_TEXT_X*m_XGraphicsScale;
	m_TimeLabel->m_Y = TIME_TEXT_Y*m_YGraphicsScale;
	m_TimeLabel->m_H = TIME_TEXT_HEIGHT*m_XGraphicsScale;
	m_TimeLabel->m_W = TIME_TEXT_WIDTH*m_YGraphicsScale;
	m_TimeLabel->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
	m_TimeLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_TimeLabel->SetFont(g_pResources->getSize20Font());
	m_TimeLabel->SetText("02:00");
	m_TimeLabel->m_Color = CColor(0,0,0,255);
	m_TimeLabel->m_ScaleX = m_XGraphicsScale;
	m_TimeLabel->m_ScaleY = m_YGraphicsScale;
	AddChild(m_TimeLabel);

	m_UpdateToScoreLabel = new CLabel();
	m_UpdateToScoreLabel->m_X = UPDATE_TO_SCORE_X * m_XGraphicsScale;
	m_UpdateToScoreLabel->m_Y = UPDATE_TO_SCORE_Y * m_YGraphicsScale;
	m_UpdateToScoreLabel->m_H = UPDATE_TO_SCORE_HEIGHT * m_YGraphicsScale;
	m_UpdateToScoreLabel->m_W = UPDATE_TO_SCORE_WIDTH * m_XGraphicsScale;
	m_UpdateToScoreLabel->m_AlignHor = IW_2D_FONT_ALIGN_RIGHT;
	m_UpdateToScoreLabel->SetFont(g_pResources->getSize8Font());
	m_UpdateToScoreLabel->m_Color = CColor(0,0,0,255);
	AddChild(m_UpdateToScoreLabel);

	m_UpdateToTimeLabel = new CLabel();
	m_UpdateToTimeLabel->m_X = UPDATE_TO_TIME_X * m_XGraphicsScale;
	m_UpdateToTimeLabel->m_Y = UPDATE_TO_TIME_Y * m_YGraphicsScale;
	m_UpdateToTimeLabel->m_H = UPDATE_TO_TIME_HEIGHT * m_YGraphicsScale;
	m_UpdateToTimeLabel->m_W = UPDATE_TO_TIME_WIDTH * m_XGraphicsScale;
	m_UpdateToTimeLabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	m_UpdateToTimeLabel->SetFont(g_pResources->getSize8Font());
	m_UpdateToTimeLabel->m_Color = CColor(0,0,0,255);
	AddChild(m_UpdateToTimeLabel);
}

void GameScene::InitSound()
{
	//Known bug in Marmalade SDK, need to play a sound first before sound starts working in some environments. We turn off sound first, so that this sound never plays.
	g_pAudio->MuteSound();
	g_pAudio->PlaySound(g_pResources->GetMatchSoundFilename());
	g_pAudio->UnmuteSound();
}

void GameScene::ToggleButtons()
{
	if(m_SettingsMenu->GetPlayButton()->HitTest(g_pInput->m_X, g_pInput->m_Y))
	{
		g_pInput->Reset();
		ToggleSettingMenu();
	}
	else if(m_SettingsMenu->GetMusicButton()->HitTest(g_pInput->m_X, g_pInput->m_Y))
	{
		g_pInput->Reset();
		m_SettingsMenu->ToggleMusic();
			
	}
	else if(m_SettingsMenu->GetSoundButton()->HitTest(g_pInput->m_X, g_pInput->m_Y))
	{
		g_pInput->Reset();
		m_SettingsMenu->ToggleSound();
	}
	else if(m_SettingsMenu->GetExitButton()->HitTest(g_pInput->m_X, g_pInput->m_Y))
	{
		g_pInput->Reset();
		ToggleSettingMenu();
		CleanUpAndChangeScene();
	}
}

bool GameScene::AMinuteHasGoneBy(float deltaTime)
{
	return ((((int)m_Time % 60) == 0) && ((int)m_Time > (int)(m_Time - deltaTime)));
}

bool GameScene::InTheFinal10Seconds(float deltaTime)
{
	return ((m_Time <= 11) && ((int)m_Time > (int)(m_Time - deltaTime)));
}

void GameScene::CleanUpAndChangeScene()
{
	m_Timers.Cancel(m_DoublePointsTimer);
	m_DoublePointsTimer = NULL;
	m_FirstSelectedItem = NULL;
	m_SecondSelectedItem = NULL;
	ResultsScene * resultsScene= (ResultsScene*) m_Manager->Find("ResultsState");
	Audio::StopMusic();
	m_Manager->SwitchTo(resultsScene);	
	m_GameState = keGameOver;
	m_NoOfMatchedPairs = 0;
}

void GameScene::UpdateLabels()
{
	char scoreBuffer[5];
	sprintf(scoreBuffer, "%.4d", ((GameSceneManager*) m_Manager)->GetScore(0) );
	m_ScoreLabel->SetText(scoreBuffer);

	int minutes, seconds;
	minutes = (int)( m_Time / 60 );
	seconds = (int)( m_Time - ( minutes * 60.0f ) );
	
	char timeBuffer[256];
	sprintf(timeBuffer, "%.2d:%.2d", minutes, seconds );
	m_TimeLabel->SetText(timeBuffer);
}

void GameScene::ToggleSettingMenu()
{
	if(m_SettingsMenu->m_IsVisible)
	{
		m_SettingsMenu->m_IsVisible = false;
		ResumeGame();
	}
	else
	{
		m_SettingsMenu->m_IsVisible = true;
		PauseGame();
	}
	g_pInput->Reset();
}

void GameScene::PauseGame()
{
	m_GameState = keGamePause;
	if(m_DoublePointsTimer)
	{
		m_DoublePointsTimer->Pause();
	}
}

void GameScene::ResumeGame()
{
	m_GameState = keGamePlaying;
	if(m_DoublePointsTimer)
	{
		m_DoublePointsTimer->Resume();
	}
}

void GameScene::DisplayUpdateToScore(char scoreBonus[])
{
	m_UpdateToScoreLabel->m_Color = CColor(0, 0, 0, 255);
	m_UpdateToScoreLabel->m_Text = scoreBonus;
}

void GameScene::DisplayUpdateToTime(char timeBonus[])
{
	m_UpdateToTimeLabel->m_Color = CColor(0, 0, 0, 255);
	m_UpdateToTimeLabel->m_Text = timeBonus;
}