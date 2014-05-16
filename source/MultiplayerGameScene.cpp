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
const float MultiplayerGameScene::kStarSize = 50.0f;

const float MultiplayerGameScene::kGoldProb = 0.2f;
const float MultiplayerGameScene::kSilverProb = 0.3f;

MultiplayerGameScene::MultiplayerGameScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingMenu)
	: m_Time((float) TimeLimit), m_GameState(keGamePlaying)
{
	IwRandSeed( time( 0 ) );

	m_DoublePointsTimer[0] = NULL;
	m_DoublePointsTimer[1] = NULL;
	m_TriplePointsTimer[0] = NULL;
	m_TriplePointsTimer[1] = NULL;

	m_DoublePoints[0] = false;
	m_DoublePoints[1] = false;
	m_TriplePoints[0] = false;
	m_TriplePoints[1] = false;

	m_DelayTime[0] = 0;
	m_DelayTime[1] = 0;

	m_Delayed[0] = false;
	m_Delayed[1] = false;

	m_NoOfMatchedPairs[0] = 0;
	m_NoOfMatchedPairs[1] = 0;

	m_XGraphicsScale = xGraphicsScale;
	m_YGraphicsScale = yGraphicsScale;
	m_SettingsMenu = settingMenu;

	m_FirstSelectedItem[0] = NULL;
	m_FirstSelectedItem[1] = NULL;
	m_SecondSelectedItem[0] = NULL;
	m_SecondSelectedItem[1] = NULL;
}


MultiplayerGameScene::~MultiplayerGameScene(void)
{
	delete m_DoublePointsTimer[0];
	delete m_DoublePointsTimer[1];
	delete m_TriplePointsTimer[0];
	delete m_TriplePointsTimer[1];

	for(int i = 0; i < GridHeight*GridWidth; i++)
	{
		if(m_Grid[0][i] !=0)
		{
			delete m_Grid[0][i];
		}
		if(m_Grid[1][i] !=0)
		{
			delete m_Grid[1][i];
		}
	}

}

void MultiplayerGameScene::Init()
{
	Scene::Init();

	//Initialise background
	InitUI();

	//Initialise buttons for controlling sound and music
	InitButtons();

	//Initialise labels for score and time
	InitLabels();

	//Initialise the game board
	InitBoard();
}

void MultiplayerGameScene::Reset()
{
	Scene::Reset();
	if(keGameOver == m_GameState)
	{
		ResetBoard(0);
		ResetBoard(1);
	}
	
	m_Time = (float)TimeLimit;
	((GameSceneManager*) m_Manager)->SetScore(0, 0);
	((GameSceneManager*) m_Manager)->SetScore(0, 1);
	Audio::PlayMusic(g_pResources->GetGameMusicFilename(), true);
	UpdateLabels();
	//If the sound and music has been turned off in another scene then set the buttons on this scene to reflect this.
	//SetSoundAndMusicButtons();
	
}

void MultiplayerGameScene::Update(float deltaTime, float alphaMul)
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
		if(m_Delayed[0])
		{
			DelayGameForNonmatch(deltaTime, 0);
		}
		if(m_Delayed[1])
		{
			DelayGameForNonmatch(deltaTime, 1);
		}
		CheckForMatches();
		UpdateTime(deltaTime);
		UpdateLabels();
		break;
	}
	
	//If the user has clicked elsewhere jsut swallow the touch
	if( m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		g_pInput->Reset();
	}
}

void MultiplayerGameScene::UpdateTime(float deltaTime)
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

void MultiplayerGameScene::DelayGameForNonmatch(float deltaTime, int player)
{
	if(m_DelayTime[player] <= 0)
	{
		if(m_FirstSelectedItem[player]->IsGold() || m_FirstSelectedItem[player]->IsSilver())
		{
			RemovePairsPowerUp(m_FirstSelectedItem[player], player);
			
		}
		else if(m_SecondSelectedItem[player]->IsGold() || m_SecondSelectedItem[player]->IsSilver())
		{
			RemovePairsPowerUp(m_SecondSelectedItem[player], player);
		}

		HideCharacter(m_FirstSelectedItem[player]);
		m_FirstSelectedItem[player] = NULL;

		HideCharacter(m_SecondSelectedItem[player]);
		m_SecondSelectedItem[player] = NULL;

		m_DelayTime[player] = 0;

		m_Delayed[player] = false;
	}
	else
	{
		m_DelayTime[player] -= deltaTime;	
	}
}

void MultiplayerGameScene::RemovePairsPowerUp(GridItem * selected, int player)
{
	selected->RemovePowerup();
	int charIndex = selected->GetCharacterIndex();

	FindOtherHalfOfPair(selected, player)->RemovePowerup();
	//Find the other half of the powerup pair and remove it.
	
}

void MultiplayerGameScene::CheckGridForMatch(int player)
{
	if(!m_Delayed[player])
	{
		for(int gridIndex = 0; gridIndex < GridWidth*GridHeight; gridIndex++ )
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

void MultiplayerGameScene::ProcessIncorrectMatch(int player)
{
	g_pAudio->PlaySound(g_pResources->GetNonmatchSoundFilename());
	m_DelayTime[player] = 0.5f;
	m_Delayed[player] = true;
}

void MultiplayerGameScene::ProcessOddPowerupMatch(int player)
{
	//This is for the case where the player has matched up two gold or silver characters, but these characters have underlying different character indexes,
	//meaning that when they are matched and removed they will leave odd corresponding pairs. The second left over character is changed to have the same
	//character index as the first left over character, so that there are no odd characters left on the board.
	CharacterBuilder charToMake(m_FirstSelectedItem[player]->GetCharacterIndex());
	charToMake.SetGold(m_FirstSelectedItem[player]->IsGold());
	charToMake.SetSilver(m_FirstSelectedItem[player]->IsSilver());
	FindOtherHalfOfPair(m_FirstSelectedItem[player], player)->RemovePowerup();
	FindOtherHalfOfPair(m_SecondSelectedItem[player], player)->SetCharacterImage(charToMake);

	//Then process match like normal
	ProcessMatch(player);
}

GridItem * MultiplayerGameScene::FindOtherHalfOfPair(GridItem* gridItem, int player)
{
	for(int i = 0; i < GridHeight*GridWidth; i++)
	{
		if(gridItem->GetCharacterIndex() == m_Grid[player][i]->GetCharacterIndex() && m_Grid[player][i] != gridItem)
		{
			return m_Grid[player][i];
		}
	}
	return NULL;
}

void MultiplayerGameScene::RemoveMatchedCharacterPairFromList(int player)
{
	GridItem * char1;
	GridItem * char2;
	
	if(0 == player)
	{
		char1 = m_Player1CharactersToRemove.at(0);
		char2 = m_Player1CharactersToRemove.at(1);
		m_Player1CharactersToRemove.erase(m_Player1CharactersToRemove.begin());
		m_Player1CharactersToRemove.erase(m_Player1CharactersToRemove.begin());
	}
	else
	{
		char1 = m_Player2CharactersToRemove.at(0);
		char2 = m_Player2CharactersToRemove.at(1);
		m_Player2CharactersToRemove.erase(m_Player2CharactersToRemove.begin());
		m_Player2CharactersToRemove.erase(m_Player2CharactersToRemove.begin());
	}

	RemoveChild(char1->GetCharacterSprite());
	RemoveChild(char2->GetCharacterSprite());
	
}

void MultiplayerGameScene::Render()
{
	Scene::Render();
}

void MultiplayerGameScene::ShowCharacter(GridItem * gridItem)
{
	gridItem->GetStarSprite()->m_IsVisible = false;
	gridItem->GetCharacterSprite()->m_IsVisible = true;
}

bool MultiplayerGameScene::StarHasBeenTouched(GridItem * gridItem)
{
	return (gridItem->GetStarSprite()->m_IsVisible && gridItem->GetStarSprite()->HitTest( g_pInput->m_X, g_pInput->m_Y )); 
}

void MultiplayerGameScene::ProcessMatch(int player)
{
	//Both characters have to both be gold, both be silver, or both be the same normal character
	if((m_FirstSelectedItem[player]->IsGold() == m_SecondSelectedItem[player]->IsGold())  && (m_FirstSelectedItem[player]->IsSilver() == m_SecondSelectedItem[player]->IsSilver()))
	{
		if(m_FirstSelectedItem[player]->IsGold())
		{
			ProcessGoldMatch(player);
		}
		else if(m_FirstSelectedItem[player]->IsSilver())
		{
			ProcessSilverMatch(player);
		}
		else
		{
			ProcessNormalMatch(player);
		}
					
		RemoveCharactersAfterDelay(player);
	}
}

void MultiplayerGameScene::RemoveCharactersAfterDelay(int player)
{
	if(0 ==player)
	{
		m_Player1CharactersToRemove.push_back(m_FirstSelectedItem[player]);
		m_Player1CharactersToRemove.push_back(m_SecondSelectedItem[player]);
		m_Timers.Add(new Timer(0.5f, 1, &MultiplayerGameScene::remove_player_1_matched_characters, (void*)this));
	}
	else
	{
		m_Player2CharactersToRemove.push_back(m_FirstSelectedItem[player]);
		m_Player2CharactersToRemove.push_back(m_SecondSelectedItem[player]);
		m_Timers.Add(new Timer(0.5f, 1, &MultiplayerGameScene::remove_player_2_matched_characters, (void*)this));
	}
	m_FirstSelectedItem[player] = NULL;
	m_SecondSelectedItem[player] = NULL;
	
}

void MultiplayerGameScene::remove_player_1_matched_characters(Timer* timer, void* userData)
{
	MultiplayerGameScene * self = (MultiplayerGameScene*)userData;
	//Remove characters from scene and from list of characters to remove.
	self->RemoveMatchedCharacterPairFromList(0);

	self->m_NoOfMatchedPairs[0]++;

	//If the player has matched 12 pairs then reset the board.
	if(6 == self->m_NoOfMatchedPairs[0])
	{
		g_pAudio->PlaySound(g_pResources->GetBoardCompleteSoundFilename());
		self->m_NoOfMatchedPairs[0] = 0;
		self->ResetBoard(0);
	}
	
}

void MultiplayerGameScene::HideCharacter(GridItem * gridItem)
{
	gridItem->GetCharacterSprite()->m_IsVisible = false;
	gridItem->GetStarSprite()->m_IsVisible = true;
}

bool MultiplayerGameScene::AMinuteHasGoneBy(float deltaTime)
{
	return ((0 == ((int)m_Time % 60)) && ((int)m_Time > (int)(m_Time - deltaTime)));
}

bool MultiplayerGameScene::InTheFinal10Seconds(float deltaTime)
{
	return ((m_Time <= 11) && ((int)m_Time > (int)(m_Time - deltaTime)));
}

void MultiplayerGameScene::remove_player_2_matched_characters(Timer* timer, void* userData)
{
	MultiplayerGameScene * self = (MultiplayerGameScene*)userData;
	//Remove characters from scene and from list of characters to remove.
	self->RemoveMatchedCharacterPairFromList(1);

	self->m_NoOfMatchedPairs[1]++;

	//If the player has matched 12 pairs then reset the board.
	if(6 == self->m_NoOfMatchedPairs[1])
	{
		g_pAudio->PlaySound(g_pResources->GetBoardCompleteSoundFilename());
		self->m_NoOfMatchedPairs[1] = 0;
		self->ResetBoard(1);
	}
	
}

void MultiplayerGameScene::ProcessNormalMatch(int player)
{
	g_pAudio->PlaySound(g_pResources->GetMatchSoundFilename());
	if(m_TriplePoints[player])
	{
		IncrementScore(30, player);
	}
	else if(m_DoublePoints[player])
	{
		IncrementScore(20, player);
	}
	else
	{
		IncrementScore(10, player);
	}
	
}

void MultiplayerGameScene::ProcessGoldMatch(int player)
{
	g_pAudio->PlaySound(g_pResources->GetGoldPickupSoundFilename());
	m_TriplePoints[player] = true;
	if(m_TriplePointsTimer[player] != NULL)
	{
		m_Timers.Cancel(m_TriplePointsTimer[player]);
		m_TriplePointsTimer[player] = NULL;
		IncrementScore(150, player);
	}
	if(m_DoublePoints[player])
	{
		IncrementScore(100, player);
	}
	else
	{
		IncrementScore(50, player);
	}

	if(0 == player)
	{
		m_TriplePointsTimer[player] = new Timer(10.0f, 1, &MultiplayerGameScene::reset_player_1_triple_points, (void*)this);
		m_Timers.Add(m_TriplePointsTimer[player]);
	}
	else
	{
		m_TriplePointsTimer[player] = new Timer(10.0f, 1, &MultiplayerGameScene::reset_player_2_triple_points, (void*)this);
		m_Timers.Add(m_TriplePointsTimer[player]);
	}
}

void MultiplayerGameScene::CheckForMatches()
{
	//If the screen has been touched, then cycle through each grid item and see if it has been touched.
	if( m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		g_pInput->Reset();
		CheckGridForMatch(0);
		CheckGridForMatch(1);
	}
		
}

void MultiplayerGameScene::ProcessSilverMatch(int player)
{
	g_pAudio->PlaySound(g_pResources->GetSilverPickupSoundFilename());
	
	if(m_DoublePointsTimer[player] != NULL)
	{
		m_Timers.Cancel(m_DoublePointsTimer[player]);
		m_DoublePointsTimer[player] = NULL;
		
	}
	if(m_TriplePoints[player])
	{
		IncrementScore(60, player);
	}
	else if(m_DoublePoints[player])
	{
		IncrementScore(40, player);
	}
	else
	{
		IncrementScore(20, player);
	}
	m_DoublePoints[player] = true;
	if(0 == player)
	{
		m_DoublePointsTimer[player] = new Timer(10.0f, 1, &MultiplayerGameScene::reset_player_1_double_points, (void*)this);
		m_Timers.Add(m_DoublePointsTimer[player]);
	}
	else
	{
		m_DoublePointsTimer[player] = new Timer(10.0f, 1, &MultiplayerGameScene::reset_player_2_double_points, (void*)this);
		m_Timers.Add(m_DoublePointsTimer[player]);
	}
	
}

void MultiplayerGameScene::reset_player_1_double_points(Timer* timer, void* userData)
{
	MultiplayerGameScene* self = (MultiplayerGameScene*) userData;
	self->m_DoublePoints[0] = false;
}

void MultiplayerGameScene::reset_player_2_double_points(Timer* timer, void* userData){
	MultiplayerGameScene* self = (MultiplayerGameScene*) userData;
	self->m_DoublePoints[1] = false;
}

void MultiplayerGameScene::reset_player_1_triple_points(Timer* timer, void* userData)
{
	MultiplayerGameScene* self = (MultiplayerGameScene*) userData;
	self->m_TriplePoints[0] = false;
}

void MultiplayerGameScene::reset_player_2_triple_points(Timer* timer, void* userData){
	MultiplayerGameScene* self = (MultiplayerGameScene*) userData;
	self->m_TriplePoints[1] = false;
}

void MultiplayerGameScene::IncrementScore(int amount, int player)
{
	((GameSceneManager*) m_Manager)->IncrementScore(amount, player);
}

void MultiplayerGameScene::ToggleButtons()
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

void MultiplayerGameScene::ToggleSettingMenu()
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
}

void MultiplayerGameScene::PauseGame()
{
	m_GameState = keGamePause;
	if(m_DoublePointsTimer[0])
	{
		m_DoublePointsTimer[0]->Pause();
	}
	if(m_DoublePointsTimer[1])
	{
		m_DoublePointsTimer[1]->Pause();
	}
}

void MultiplayerGameScene::ResumeGame()
{
	m_GameState = keGamePlaying;
	if(m_DoublePointsTimer[0])
	{
		m_DoublePointsTimer[0]->Resume();
	}
	if(m_DoublePointsTimer[1])
	{
		m_DoublePointsTimer[1]->Resume();
	}
}

void MultiplayerGameScene::CleanUpAndChangeScene()
{
	m_Timers.Cancel(m_DoublePointsTimer[0]);
	m_Timers.Cancel(m_DoublePointsTimer[1]);
	m_DoublePointsTimer[0] = NULL;
	m_DoublePointsTimer[1] = NULL;
	m_FirstSelectedItem[0] = NULL;
	m_FirstSelectedItem[1] = NULL;
	m_SecondSelectedItem[0] = NULL;
	m_SecondSelectedItem[1] = NULL;
	m_NoOfMatchedPairs[0] = 0;
	m_NoOfMatchedPairs[1] = 0;
	MultiplayerResultsScene * resultsScene= (MultiplayerResultsScene*) m_Manager->Find("MultiplayerResultsState");
	Audio::StopMusic();
	m_Manager->SwitchTo(resultsScene);	
	m_GameState = keGameOver;
}

void MultiplayerGameScene::UpdateLabels()
{
	char p1ScoreBuffer[5];
	sprintf(p1ScoreBuffer, "%.4d", ((GameSceneManager*) m_Manager)->GetScore(0) );
	m_Player1ScoreLabel->SetText(p1ScoreBuffer);

	char p2ScoreBuffer[5];
	sprintf(p2ScoreBuffer, "%.4d", ((GameSceneManager*) m_Manager)->GetScore(1) );
	m_Player2ScoreLabel->SetText(p2ScoreBuffer);

	int minutes, seconds;
	minutes = (int)( m_Time / 60 );
	seconds = (int)( m_Time - ( minutes * 60.0f ) );
	
	char timeBuffer[256];
	sprintf(timeBuffer, "%.2d:%.2d", minutes, seconds );
	m_Player1TimeLabel->SetText(timeBuffer);
	m_Player2TimeLabel->SetText(timeBuffer);
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
	m_Player1ScoreLabel = new CLabel();
	m_Player1ScoreLabel->m_X = kPlayer1ScoreTextX * m_XGraphicsScale;
	m_Player1ScoreLabel->m_Y = kPlayer1ScoreTextY * m_YGraphicsScale;
	m_Player1ScoreLabel->m_W = kLabelWidth;
	m_Player1ScoreLabel->m_H = kLabelHeight;
	m_Player1ScoreLabel->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
	m_Player1ScoreLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_Player1ScoreLabel->SetFont(g_pResources->GetSize20Font());
	m_Player1ScoreLabel->SetText("0000");
	m_Player1ScoreLabel->m_Color = CColor(0,0,0,255);
	m_Player1ScoreLabel->m_ScaleX = m_XGraphicsScale;
	m_Player1ScoreLabel->m_ScaleY = m_YGraphicsScale;
	AddChild(m_Player1ScoreLabel);

	// Create the time text
	m_Player1TimeLabel = new CLabel();
	m_Player1TimeLabel->m_X = kPlayer1TimeTextX*m_XGraphicsScale;
	m_Player1TimeLabel->m_Y = kPlayer1TimeTextY*m_YGraphicsScale;
	m_Player1TimeLabel->m_W = kLabelWidth;
	m_Player1TimeLabel->m_H = kLabelHeight;
	m_Player1TimeLabel->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
	m_Player1TimeLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_Player1TimeLabel->SetFont(g_pResources->GetSize20Font());
	m_Player1TimeLabel->SetText("02:00");
	m_Player1TimeLabel->m_Color = CColor(0,0,0,255);
	m_Player1TimeLabel->m_ScaleX = m_XGraphicsScale;
	m_Player1TimeLabel->m_ScaleY = m_YGraphicsScale;
	AddChild(m_Player1TimeLabel);

	// Create the score text
	m_Player2ScoreLabel = new CLabel();
	m_Player2ScoreLabel->m_X = kPlayer2ScoreTextX * m_XGraphicsScale + (kLabelWidth*m_XGraphicsScale)/2;
	m_Player2ScoreLabel->m_Y = kPlayer2ScoreTextY * m_YGraphicsScale + (kLabelHeight*m_YGraphicsScale)/2;
	m_Player2ScoreLabel->m_H = kLabelHeight;
	m_Player2ScoreLabel->m_W = kLabelWidth;
	m_Player2ScoreLabel->m_AnchorX = 0.5f;
	m_Player2ScoreLabel->m_AnchorY = 0.5f;
	m_Player2ScoreLabel->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
	m_Player2ScoreLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_Player2ScoreLabel->SetFont(g_pResources->GetSize20Font());
	m_Player2ScoreLabel->SetText("0000");
	m_Player2ScoreLabel->m_Color = CColor(0,0,0,255);
	m_Player2ScoreLabel->m_Angle = 180.0f;
	m_Player2ScoreLabel->m_ScaleX = m_XGraphicsScale;
	m_Player2ScoreLabel->m_ScaleY = m_YGraphicsScale;
	AddChild(m_Player2ScoreLabel);

	// Create the time text
	m_Player2TimeLabel = new CLabel();
	m_Player2TimeLabel->m_X = kPlayer2TimeTextX*m_XGraphicsScale + (kLabelWidth*m_XGraphicsScale)/2;
	m_Player2TimeLabel->m_Y = kPlayer2TimeTextY*m_YGraphicsScale + (kLabelHeight*m_YGraphicsScale)/2;
	m_Player2TimeLabel->m_H = kLabelHeight;
	m_Player2TimeLabel->m_W = kLabelWidth;
	m_Player2TimeLabel->m_AnchorX = 0.5f;
	m_Player2TimeLabel->m_AnchorY = 0.5f;
	m_Player2TimeLabel->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
	m_Player2TimeLabel->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_Player2TimeLabel->SetFont(g_pResources->GetSize20Font());
	m_Player2TimeLabel->SetText("02:00");
	m_Player2TimeLabel->m_Color = CColor(0,0,0,255);
	m_Player2TimeLabel->m_Angle = 180.0f;
	m_Player2TimeLabel->m_ScaleX = m_XGraphicsScale;
	m_Player2TimeLabel->m_ScaleY = m_YGraphicsScale;
	AddChild(m_Player2TimeLabel);

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

void MultiplayerGameScene::InitBoard()
{
	std::vector<CharacterBuilder> player1CharacterTypes;
	SetupCharactersArray(player1CharacterTypes);	
	AddGridToScene(player1CharacterTypes, 0);

	std::vector<CharacterBuilder> player2CharacterTypes;
	SetupCharactersArray(player2CharacterTypes);	
	AddGridToScene(player2CharacterTypes, 1);
}
void MultiplayerGameScene::ResetBoard(int player)
{
	std::vector<CharacterBuilder> characterTypes;
	SetupCharactersArray(characterTypes);	
	ResetGrid(characterTypes, player);
}

void MultiplayerGameScene::ResetGrid(std::vector<CharacterBuilder> characterTypes, int player)
{
	for(int i = 0; i < GridHeight*GridWidth; i++)
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

void MultiplayerGameScene::SetupCharactersArray(std::vector<CharacterBuilder> &characterTypes)
{
	//Fill vector with exactly 2 of each character type
	int numberOfPairs = (GridHeight*GridWidth)/2;
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
	for( int row = 0; row < GridHeight; row++ )
	{
		x = xOffset;
		for( int column = 0; column < GridWidth; column++ )
		{
			int characterTypeIndex = rand() % characterTypes.size();
			GridItem* grid = new GridItem( x, y, characterTypes.at(characterTypeIndex));
			characterTypes.erase(characterTypes.begin() + characterTypeIndex);
			m_Grid[player][(row*GridWidth)+column] = grid; 
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