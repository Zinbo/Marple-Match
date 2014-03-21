/*
 * (C) 2014 Search for a Star
 * 
 */

#include "GameScene.h"

#define TIME_TEXT_X 2.0f
#define TIME_TEXT_Y 13.0f
#define TIME_TEXT_HEIGHT 19.0f
#define TIME_TEXT_WIDTH 71.0f
#define STAR_X_OFFSET 55.0f
#define STAR_Y_OFFSET 85.0f
#define STAR_SPACING 70.0f
#define BUTTON_SPACING 25.0F
#define BUTTON_X_OFFSET 36.0f
#define BUTTON_STARTING_X 94.0f
#define BUTTON_STARTING_Y 7.0f
#define GOLD_PROB 0.1
#define SILVER_PROB 0.2
using namespace SFAS2014;

//
//
// GameScene class
//
//
GameScene::GameScene() 
	: m_Time((float) TimeLimit), m_DoublePointsTimer(NULL), m_FirstSelectedItem(NULL), 
	m_SecondSelectedItem(NULL), m_DelayTime(0), m_DoublePoints(false),
	m_GameState(keGameStart), m_NoOfMatchedPairs(0)
{
	IwRandSeed( time( 0 ) );
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
	//If we need to restart the game, then set the game state to gameStart
	if(m_GameState == keGameOver)
	{
		m_GameState = keGameStart;
	}

	//If the sound and music has been turned off in another scene then set the buttons on this scene to reflect this.
	SetSoundAndMusicButtons();
	
}

void GameScene::Update(float deltaTime, float alphaMul)
{
	//if not current scene, don't bother updating.
	if(!(m_Manager->GetCurrent() == this))
	{
		return;
	}
	Scene::Update(deltaTime, alphaMul);

	//Check to see if any buttons have been pressed.
	if(m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		ToggleButtons();
	}

	//call the right method for the correct game state
	switch(m_GameState)
	{
	case keGameStart:
		StartGame();
		m_GameState = keGamePlaying;
		break;
	case keGamePlaying:
		CheckForMatches();
		break;
	case keNonMatch:
		DelayGameForNonmatch(deltaTime);
		break;
	}

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

	// Update the hud strings
	UpdateLabels();
	
}

void GameScene::Render()
{
	Scene::Render();
}

void GameScene::StartGame()
{
	//Reset all of the stars to visible and randomise the character pairs.
	ResetBoard();
	
	m_Time = (float)TimeLimit;
	((GameSceneManager*) m_Manager)->SetScore(0);
	Audio::PlayMusic(g_pResources->GetGameMusicFilename(), true);
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
		else if(randNum <= 0.5)
		{
			charToMake.SetSilver(true);
		}
		characterTypes.push_back(charToMake);
		characterTypes.push_back(charToMake);
	}
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
	}
	m_Timers.Add(new Timer(10.0f, 1, &GameScene::ResetDoublePoints, (void*)this));
}

void GameScene::ProcessNormalMatch()
{
	g_pAudio->PlaySound(g_pResources->GetMatchSoundFilename());
}

void GameScene::IncrementScore()
{
	if(m_DoublePoints)
	{
		((GameSceneManager*) m_Manager)->IncrementScore(20);
	}
	else
	{
		((GameSceneManager*) m_Manager)->IncrementScore(10);
	}
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
		
		IncrementScore();			
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
	//add Pause button first at the starting x and y position.
	m_PauseButton = new CSprite();
	m_PauseButton->m_X = BUTTON_STARTING_X*m_XGraphicsScale;
	m_PauseButton->m_Y = BUTTON_STARTING_Y*m_YGraphicsScale;
	m_PauseButton->SetImage(g_pResources->GetPauseButton());
	m_PauseButton->m_H = m_PauseButton->GetImage()->GetHeight();
	m_PauseButton->m_W = m_PauseButton->GetImage()->GetWidth();

	//Set the scale for all buttons here. The button image should be scaled to be the size of BUTTON_SPACING, and then scaled to match the size of the screen.
	float buttonScale = BUTTON_SPACING / m_PauseButton->m_H;
	float buttonXScale = m_XGraphicsScale * buttonScale;
	float buttonYScale = m_YGraphicsScale * buttonScale;
	
	m_PauseButton->m_ScaleX = buttonXScale;
	m_PauseButton->m_ScaleY = buttonYScale;
	AddChild(m_PauseButton);

	//Add music button next, with BUTTON_X_OFFSET difference in space between the pause and the music button.
	m_MusicButton = new CSprite();
	m_MusicButton->m_X = m_PauseButton->m_X + (BUTTON_X_OFFSET*m_XGraphicsScale);
	m_MusicButton->m_Y = m_PauseButton->m_Y;
	m_MusicButton->SetImage(g_pResources->GetMusicButton());
	m_MusicButton->m_H = m_MusicButton->GetImage()->GetHeight();
	m_MusicButton->m_W = m_MusicButton->GetImage()->GetWidth();
	m_MusicButton->m_ScaleX = buttonXScale;
	m_MusicButton->m_ScaleY = buttonYScale;
	AddChild(m_MusicButton);

	//Add the mute music button in the same location as the music button, but make it invisible at first.
	m_MuteMusicButton = new CSprite();
	m_MuteMusicButton->m_X = m_MusicButton->m_X;
	m_MuteMusicButton->m_Y = m_PauseButton->m_Y;
	m_MuteMusicButton->SetImage(g_pResources->GetMuteMusicButton());
	m_MuteMusicButton->m_H = m_MuteMusicButton->GetImage()->GetHeight();
	m_MuteMusicButton->m_W = m_MuteMusicButton->GetImage()->GetWidth();
	m_MuteMusicButton->m_ScaleX = buttonXScale;
	m_MuteMusicButton->m_ScaleY = buttonYScale;
	m_MuteMusicButton->m_IsVisible = false;
	AddChild(m_MuteMusicButton);

	//Add the sound button next, with BUTTON_X_OFFSET difference in space between the music and the sound button.
	m_SoundButton = new CSprite();
	m_SoundButton->m_X = m_MusicButton->m_X + (BUTTON_X_OFFSET*m_XGraphicsScale);
	m_SoundButton->m_Y = m_PauseButton->m_Y;
	m_SoundButton->SetImage(g_pResources->GetSoundButton());
	m_SoundButton->m_H = m_SoundButton->GetImage()->GetHeight();
	m_SoundButton->m_W = m_SoundButton->GetImage()->GetWidth();
	m_SoundButton->m_ScaleX = buttonXScale;
	m_SoundButton->m_ScaleY = buttonYScale;
	AddChild(m_SoundButton);

	//Add the mute sound button in the same location as the sound button, but make it invisible at first.
	m_MuteSoundButton = new CSprite();
	m_MuteSoundButton->m_X = m_SoundButton->m_X;
	m_MuteSoundButton->m_Y = m_PauseButton->m_Y;
	m_MuteSoundButton->SetImage(g_pResources->GetMuteSoundButton());
	m_MuteSoundButton->m_H = m_MuteSoundButton->GetImage()->GetHeight();
	m_MuteSoundButton->m_W = m_MuteSoundButton->GetImage()->GetWidth();
	m_MuteSoundButton->m_ScaleX = buttonXScale;
	m_MuteSoundButton->m_ScaleY = buttonYScale;
	m_MuteSoundButton->m_IsVisible = false;
	AddChild(m_MuteSoundButton);

	//Finally add the exit button, with BUTTON_X_OFFSET difference in space between the sound and the exit button.
	m_ExitButton = new CSprite();
	m_ExitButton->m_X = m_SoundButton->m_X + (BUTTON_X_OFFSET*m_XGraphicsScale);
	m_ExitButton->m_Y = m_PauseButton->m_Y;
	m_ExitButton->SetImage(g_pResources->GetExitButton());
	m_ExitButton->m_H = m_ExitButton->GetImage()->GetHeight();
	m_ExitButton->m_W = m_ExitButton->GetImage()->GetWidth();
	m_ExitButton->m_ScaleX = buttonXScale;
	m_ExitButton->m_ScaleY = buttonYScale;
	AddChild(m_ExitButton);
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
	m_ScoreLabel->m_X = (float)IwGxGetScreenWidth() - (TIME_TEXT_X*m_XGraphicsScale) - m_ScoreLabel->m_W;
	m_ScoreLabel->m_Y = TIME_TEXT_Y*m_YGraphicsScale;
	m_ScoreLabel->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
	m_ScoreLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_ScoreLabel->SetFont(g_pResources->getFont());
	m_ScoreLabel->SetText("0000");
	m_ScoreLabel->m_Color = CColor(0,0,0,255);
	AddChild(m_ScoreLabel);

	// Create the time text
	m_TimeLabel = new CLabel();
	m_TimeLabel->m_X = TIME_TEXT_X*m_XGraphicsScale;
	m_TimeLabel->m_Y = TIME_TEXT_Y*m_YGraphicsScale;
	m_TimeLabel->m_H = TIME_TEXT_HEIGHT*m_XGraphicsScale;
	m_TimeLabel->m_W = TIME_TEXT_WIDTH*m_YGraphicsScale;
	m_TimeLabel->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
	m_TimeLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_TimeLabel->SetFont(g_pResources->getFont());
	m_TimeLabel->SetText("02:00");
	m_TimeLabel->m_Color = CColor(0,0,0,255);
	AddChild(m_TimeLabel);
}

void GameScene::InitSound()
{
	//Known bug in Marmalade SDK, need to play a sound first before sound starts working in some environments. We turn off sound first, so that this sound never plays.
	g_pAudio->MuteSound();
	g_pAudio->PlaySound(g_pResources->GetMatchSoundFilename());
	g_pAudio->UnmuteSound();
}

void GameScene::SetSoundAndMusicButtons()
{
	//If the music isn't muted, then show the music button, else show the mute music button
	if(Audio::m_musicIsOn)
	{
		m_MusicButton->m_IsVisible = true;
		m_MuteMusicButton->m_IsVisible = false;
	}
	else
	{
		m_MusicButton->m_IsVisible = false;
		m_MuteMusicButton->m_IsVisible = true;
	}

	//If the sound isn't muted, then show the sound button, else show the mute sound button.
	if(Audio::m_soundIsOn)
	{
		m_SoundButton->m_IsVisible = true;
		m_MuteSoundButton->m_IsVisible = false;
	}
	else
	{
		m_SoundButton->m_IsVisible = false;
		m_MuteSoundButton->m_IsVisible = true;
	}
}

void GameScene::ToggleMusicButton()
{
	//If the music button is showing, then show the mute music button and turn off the music 
	if(m_MusicButton->m_IsVisible)
	{
		m_MusicButton->m_IsVisible = false;
		m_MuteMusicButton->m_IsVisible = true;
		Audio::MuteMusic();
	}
	//Else the mute music button is showing, so show the music button and turn on the music
	else
	{
		m_MusicButton->m_IsVisible = true;
		m_MuteMusicButton->m_IsVisible = false;
		Audio::UnmuteMusic();
	}
}

void GameScene::ToggleSoundButton()
{
	//If the sound button is showing, then show the mute sound button and turn off the sound 
	if(m_SoundButton->m_IsVisible)
	{
		g_pInput->Reset();
		m_SoundButton->m_IsVisible = false;
		m_MuteSoundButton->m_IsVisible = true;
		Audio::MuteSound();
	}
	//Else the mute sound button is showing, so show the sound button and turn on the sound
	else
	{
		m_SoundButton->m_IsVisible = true;
		m_MuteSoundButton->m_IsVisible = false;
		Audio::UnmuteSound();
	}
}

void GameScene::ToggleButtons()
{
	if(m_PauseButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
	{
		//TODO
		g_pInput->Reset();
	}
	else if(m_MusicButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
	{
		g_pInput->Reset();
		ToggleMusicButton();
			
	}
	else if(m_SoundButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
	{
		g_pInput->Reset();
		ToggleSoundButton();
	}
	else if(m_ExitButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
	{
		//TODO
		g_pInput->Reset();
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
	m_Time = 0;
	ResultsScene * resultsScene= (ResultsScene*) m_Manager->Find("ResultsState");
	Audio::StopMusic();
	m_Manager->SwitchTo(resultsScene);	
	m_GameState = keGameOver;
}

void GameScene::UpdateLabels()
{
	char scoreBuffer[9];
	sprintf(scoreBuffer, "%.4d", ((GameSceneManager*) m_Manager)->GetScore() );
	m_ScoreLabel->SetText(scoreBuffer);

	int minutes, seconds;
	minutes = (int)( m_Time / 60 );
	seconds = (int)( m_Time - ( minutes * 60.0f ) );
	
	char timeBuffer[256];
	sprintf(timeBuffer, "%.2d:%.2d", minutes, seconds );
	m_TimeLabel->SetText(timeBuffer);
}