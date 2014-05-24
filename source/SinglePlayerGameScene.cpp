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
const float SinglePlayerGameScene::kGoldProb = 0.2f;
const float SinglePlayerGameScene::kSilverProb = 0.3f;

const float SinglePlayerGameScene::kUpdateToScoreX = 160.0f;
const float SinglePlayerGameScene::kUpdateToScoreY = 55.0f;
const float SinglePlayerGameScene::kUpdateToScoreHeight = 15.0f;
const float SinglePlayerGameScene::kUpdateToScoreWidth = 150.0f;

const float SinglePlayerGameScene::kUpdateToTimeX = 10.0f;
const float SinglePlayerGameScene::kUpdateToTimeY = 55.0f;
const float SinglePlayerGameScene::kUpdateToTimeHeight = 15.0f;
const float SinglePlayerGameScene::kUpdateToTimeWidth = 150.0f;

SinglePlayerGameScene::SinglePlayerGameScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingMenu) 
	: m_Time((float) keTimeLimit), m_DoublePointsTimer(NULL), m_FirstSelectedItem(NULL), 
	m_SecondSelectedItem(NULL), m_DelayTime(0), m_DoublePoints(false),
	m_GameState(keGamePlaying), m_NoOfMatchedPairs(0), MasterScene(xGraphicsScale, yGraphicsScale, settingMenu)
	
{
	IwRandSeed( time( 0 ) );
}

SinglePlayerGameScene::~SinglePlayerGameScene()
{
	delete m_DoublePointsTimer;

	for(int i = 0; i < keGridHeight*keGridWidth; i++)
	{
		if(m_Grid[i] !=0)
		{
			delete m_Grid[i];
		}
	}
}

void SinglePlayerGameScene::Init()
{
	MasterScene::Init();

	//Initialise labels for score and time
	InitLabels();

	//Initialise the game board
	InitBoard();

}

void SinglePlayerGameScene::Reset()
{
	MasterScene::Reset();
	if(m_GameState = keGameOver)
	{
		ResetBoard();
	}
	
	m_Time = (float)keTimeLimit;
	((GameSceneManager*) m_Manager)->SetScore(0, 0);
	UpdateLabels();
}

void SinglePlayerGameScene::Update(float deltaTime, float alphaMul)
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
	
	//If the user has clicked elsewhere just swallow the touch
	if( m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		g_pInput->Reset();
	}
}

void SinglePlayerGameScene::UpdateTime(float deltaTime)
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
		ExitScene();
	}

	//Update the timer
	m_Time -= deltaTime;
}

void SinglePlayerGameScene::SetupCharactersArray(std::vector<CharacterBuilder> &characterTypes)
{
	//Fill vector with exactly 2 of each character type
	int numberOfPairs = (keGridHeight*keGridWidth)/2;
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

void SinglePlayerGameScene::FadeLabels()
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

void SinglePlayerGameScene::AddGridToScene(std::vector<CharacterBuilder> &characterTypes)
{
	float x = kStarXOffset*m_XGraphicsScale;
	float y = kStarYOffset*m_YGraphicsScale;
	for( int row = 0; row < keGridHeight; row++ )
	{
		x = kStarXOffset*m_XGraphicsScale;
		for( int column = 0; column < keGridWidth; column++ )
		{
			int characterTypeIndex = rand() % characterTypes.size();
			GridItem* grid = new GridItem( x, y, characterTypes.at(characterTypeIndex));
			characterTypes.erase(characterTypes.begin() + characterTypeIndex);

			m_Grid[(row*keGridWidth)+column] = grid; 
			AddChild( grid->GetStarSprite() );
			AddChild(grid->GetCharacterSprite());

			x += kStarSpacing*m_XGraphicsScale;
		}

		y += kStarSpacing*m_YGraphicsScale;
	}
}

void SinglePlayerGameScene::InitBoard()
{
	std::vector<CharacterBuilder> characterTypes;
	SetupCharactersArray(characterTypes);	
	AddGridToScene(characterTypes);
}

void SinglePlayerGameScene::ProcessGoldMatch()
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

void SinglePlayerGameScene::ProcessSilverMatch()
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
	m_DoublePointsTimer = new Timer(10.0f, 1, &SinglePlayerGameScene::ResetDoublePoints, (void*)this);
	m_Timers.Add(m_DoublePointsTimer);
}

void SinglePlayerGameScene::ProcessNormalMatch()
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

void SinglePlayerGameScene::IncrementScore(int amount)
{
	((GameSceneManager*) m_Manager)->IncrementScore(amount, 0);
}

void SinglePlayerGameScene::RemoveCharactersAfterDelay()
{
	m_CharactersToRemove.push_back(m_FirstSelectedItem);
	m_CharactersToRemove.push_back(m_SecondSelectedItem);
	m_FirstSelectedItem = NULL;
	m_SecondSelectedItem = NULL;
	m_Timers.Add(new Timer(0.5f, 1, &SinglePlayerGameScene::RemoveMatchedCharacters, (void*)this));
}

void SinglePlayerGameScene::ProcessMatch()
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

bool SinglePlayerGameScene::StarHasBeenTouched(int gridIndex)
{
	return (m_Grid[gridIndex]->GetStarSprite()->m_IsVisible && m_Grid[gridIndex]->GetStarSprite()->HitTest( g_pInput->m_X, g_pInput->m_Y )); 
}

void SinglePlayerGameScene::ShowCharacter(GridItem * gridItem)
{
	gridItem->GetStarSprite()->m_IsVisible = false;
	gridItem->GetCharacterSprite()->m_IsVisible = true;
}

void SinglePlayerGameScene::ProcessIncorrectMatch()
{
	g_pAudio->PlaySound(g_pResources->GetNonmatchSoundFilename());
	m_DelayTime = 0.5f;
	m_GameState = keNonMatch;
}

void SinglePlayerGameScene::ProcessOddPowerupMatch()
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

void SinglePlayerGameScene::CheckForMatches()
{
	//If the screen has been touched, then cycle through each grid item and see if it has been touched.
	if(m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		for(int gridIndex = 0; gridIndex < keGridWidth*keGridHeight; gridIndex++ )
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

void SinglePlayerGameScene::HideCharacter(GridItem * gridItem)
{
	gridItem->GetCharacterSprite()->m_IsVisible = false;
	gridItem->GetStarSprite()->m_IsVisible = true;
}

void SinglePlayerGameScene::DelayGameForNonmatch(float deltaTime)
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

void SinglePlayerGameScene::RemoveMatchedCharacterPairFromList()
{
	GridItem * char1 = m_CharactersToRemove.at(0);
	GridItem * char2 = m_CharactersToRemove.at(1);
	RemoveChild(char1->GetCharacterSprite());
	RemoveChild(char2->GetCharacterSprite());
	m_CharactersToRemove.erase(m_CharactersToRemove.begin());
	m_CharactersToRemove.erase(m_CharactersToRemove.begin());
}

void SinglePlayerGameScene::RemoveMatchedCharacters(Timer* timer, void* userData)
{
	SinglePlayerGameScene * self = (SinglePlayerGameScene*)userData;
	//Remove characters from scene and from list of characters to remove.
	self->RemoveMatchedCharacterPairFromList();

	self->m_NoOfMatchedPairs++;

	//If the player has matched 12 pairs then reset the board.
	if(12 == self->m_NoOfMatchedPairs)
	{
		g_pAudio->PlaySound(g_pResources->GetBoardCompleteSoundFilename());
		self->m_NoOfMatchedPairs = 0;
		self->ResetBoard();
	}
	
}

void SinglePlayerGameScene::ResetBoard()
{
	std::vector<CharacterBuilder> characterTypes;
	SetupCharactersArray(characterTypes);

	//Cycle through each grid item, make the star visible and add a new random character underneath
	for(int i = 0; i < keGridHeight*keGridWidth; i++)
	{
		int characterTypeIndex = rand() % characterTypes.size();
		
		CharacterBuilder charToMake = characterTypes.at(characterTypeIndex);
		m_Grid[i]->GetStarSprite()->m_IsVisible = true;
		m_Grid[i]->SetCharacterImage(charToMake);
		AddChild(m_Grid[i]->GetCharacterSprite());

		characterTypes.erase(characterTypes.begin() + characterTypeIndex);
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

GridItem * SinglePlayerGameScene::FindOtherHalfOfPair(const GridItem* gridItem) const
{
	for(int i = 0; i < keGridHeight*keGridWidth; i++)
	{
		if(gridItem->GetCharacterIndex() == m_Grid[i]->GetCharacterIndex() && m_Grid[i] != gridItem)
		{
			return m_Grid[i];
		}
	}
	return NULL;
}

void SinglePlayerGameScene::RemovePairsPowerUp(GridItem * selected)
{
	selected->RemovePowerup();
	int charIndex = selected->GetCharacterIndex();

	FindOtherHalfOfPair(selected)->RemovePowerup();
	//Find the other half of the powerup pair and remove it.
	
}

void SinglePlayerGameScene::ResetDoublePoints(Timer* timer, void* userData)
{
	SinglePlayerGameScene* self = (SinglePlayerGameScene*) userData;
	self->m_DoublePoints = false;
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
	m_ScoreLabel = new CLabel();
	m_ScoreLabel->m_X = kScoreTextX * m_XGraphicsScale;
	m_ScoreLabel->m_Y = kScoreTextY * m_YGraphicsScale;
	m_ScoreLabel->m_W = kLabelWidth;
	m_ScoreLabel->m_H = kLabelHeight;
	m_ScoreLabel->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
	m_ScoreLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_ScoreLabel->SetFont(g_pResources->GetSize20Font());
	m_ScoreLabel->SetText("0000");
	m_ScoreLabel->m_Color = CColor(0,0,0,255);
	m_ScoreLabel->m_ScaleX = m_XGraphicsScale;
	m_ScoreLabel->m_ScaleY = m_YGraphicsScale;
	AddChild(m_ScoreLabel);

	// Create the time text
	m_TimeLabel = new CLabel();
	m_TimeLabel->m_X = kTimeTextX*m_XGraphicsScale;
	m_TimeLabel->m_Y = kTimeTextY*m_YGraphicsScale;
	m_TimeLabel->m_W = kLabelWidth;
	m_TimeLabel->m_H = kLabelHeight;
	m_TimeLabel->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
	m_TimeLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_TimeLabel->SetFont(g_pResources->GetSize20Font());
	m_TimeLabel->SetText("02:00");
	m_TimeLabel->m_Color = CColor(0,0,0,255);
	m_TimeLabel->m_ScaleX = m_XGraphicsScale;
	m_TimeLabel->m_ScaleY = m_YGraphicsScale;
	AddChild(m_TimeLabel);

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

bool SinglePlayerGameScene::AMinuteHasGoneBy(float deltaTime) const
{
	return ((0 == ((int)m_Time % 60)) && ((int)m_Time > (int)(m_Time - deltaTime)));
}

bool SinglePlayerGameScene::InTheFinal10Seconds(float deltaTime) const
{
	return ((m_Time <= 11) && ((int)m_Time > (int)(m_Time - deltaTime)));
}

void SinglePlayerGameScene::ExitScene()
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

void SinglePlayerGameScene::UpdateLabels()
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

void SinglePlayerGameScene::PauseGame()
{
	m_GameState = keGamePause;
	if(m_DoublePointsTimer)
	{
		m_DoublePointsTimer->Pause();
	}
}

void SinglePlayerGameScene::ResumeGame()
{
	m_GameState = keGamePlaying;
	if(m_DoublePointsTimer)
	{
		m_DoublePointsTimer->Resume();
	}
}

void SinglePlayerGameScene::DisplayUpdateToScore(char scoreBonus[])
{
	m_UpdateToScoreLabel->m_Color = CColor(0, 0, 0, 255);
	m_UpdateToScoreLabel->m_Text = scoreBonus;
}

void SinglePlayerGameScene::DisplayUpdateToTime(char timeBonus[])
{
	m_UpdateToTimeLabel->m_Color = CColor(0, 0, 0, 255);
	m_UpdateToTimeLabel->m_Text = timeBonus;
}