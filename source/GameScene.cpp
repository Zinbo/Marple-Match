/*
 * (C) 2014 Search for a Star
 * 
 */

#include "GameScene.h"
#include "resources.h"
#include "IwGx.h"
#include "GridItem.h"
#include "input.h"

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
using namespace SFAS2014;

//
//
// GameScene class
//
//
GameScene::GameScene() : mTime( (float)TimeLimit )
{
}

GameScene::~GameScene()
{

}

void GameScene::Init()
{
	Scene::Init();

	IwRandSeed( time( 0 ) );
	selected1 = NULL;
	selected2 = NULL;
	delayTime = 0;

	//Add background
	mpBackground = new CSprite();
	mpBackground->m_X = 0;
	mpBackground->m_Y = 0;
	mpBackground->SetImage(g_pResources->getGameBackground());
	mpBackground->m_W = mpBackground->GetImage()->GetWidth();
	mpBackground->m_H = mpBackground->GetImage()->GetHeight();

	float backgroundXScale = (float)IwGxGetScreenWidth() / mpBackground->m_W;
	float backgroundYScale = (float)IwGxGetScreenHeight() / mpBackground->m_H;
	// Fit background to screen size
	mpBackground->m_ScaleX = backgroundXScale;
	mpBackground->m_ScaleY = backgroundYScale;
	AddChild(mpBackground);
	

	// Create the title text
	mpScoreText = new CLabel();
	mpScoreText->m_H = TIME_TEXT_HEIGHT*m_YGraphicsScale;
	mpScoreText->m_W = TIME_TEXT_WIDTH*m_XGraphicsScale;
	mpScoreText->m_X = (float)IwGxGetScreenWidth() - (TIME_TEXT_X*m_XGraphicsScale) - mpScoreText->m_W;
	mpScoreText->m_Y = TIME_TEXT_Y*m_YGraphicsScale;
	mpScoreText->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
	mpScoreText->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;

	mpScoreText->SetFont(g_pResources->getFont());
	mpScoreText->SetText("0000");
	mpScoreText->m_Color = CColor(0,0,0,255);
	AddChild(mpScoreText);

	// Create the title text
	mpTimeText = new CLabel();
	mpTimeText->m_X = TIME_TEXT_X*m_XGraphicsScale;
	mpTimeText->m_Y = TIME_TEXT_Y*m_YGraphicsScale;
	mpTimeText->m_H = TIME_TEXT_HEIGHT*m_XGraphicsScale;
	mpTimeText->m_W = TIME_TEXT_WIDTH*m_YGraphicsScale;
	mpTimeText->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
	mpTimeText->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	mpTimeText->SetFont(g_pResources->getFont());
	mpTimeText->SetText("02:00");
	//mpTimeText->m_AnchorX = 0.0;
	mpTimeText->m_AnchorY = 0.0;
	mpTimeText->m_Color = CColor(0,0,0,255);
	AddChild(mpTimeText);

	//Draw Buttons
	AddButtons();

	m_GameState = keGameStart;
	mNoOfMatchedPairs = 0;

	//Known bug in Marmalade SDK, need to play a sound first before sound starts working in some environments. We turn off sound first, so that this sound never plays.
	g_pAudio->MuteSound();
	g_pAudio->PlaySound(g_pResources->GetMatchSoundFilename());
	g_pAudio->UnmuteSound();

	initialiseBoard();
}

void GameScene::Reset()
{
	//If we need to restart the game, then set the game state to gameStart
	if(m_GameState == keGameOver)
	{
		m_GameState = keGameStart;
	}

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

void GameScene::Update(float deltaTime, float alphaMul)
{
	//if not current scene, don't bother updating.
	if(!(m_Manager->GetCurrent() == this))
	{
		return;
	}
	Scene::Update( deltaTime, alphaMul);

	//Check to see if any buttons have been pressed.
	if(m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		if(m_PauseButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			//TODO
			g_pInput->Reset();
		}
		else if(m_MusicButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			g_pInput->Reset();
			if(m_MusicButton->m_IsVisible)
			{
				m_MusicButton->m_IsVisible = false;
				m_MuteMusicButton->m_IsVisible = true;
				Audio::PauseMusic();
			}
			else
			{
				m_MusicButton->m_IsVisible = true;
				m_MuteMusicButton->m_IsVisible = false;
				Audio::ResumeMusic();
			}
		}
		else if(m_SoundButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			if(m_SoundButton->m_IsVisible)
			{
				g_pInput->Reset();
				m_SoundButton->m_IsVisible = false;
				m_MuteSoundButton->m_IsVisible = true;
				Audio::MuteSound();
			}
			else
			{
				m_SoundButton->m_IsVisible = true;
				m_MuteSoundButton->m_IsVisible = false;
				Audio::UnmuteSound();
			}
		}
		else if(m_ExitButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			//TODO
			g_pInput->Reset();
		}
	}

	switch(m_GameState)
	{
	case keGameStart:
		StartGame();
		m_GameState = keGamePlaying;
		break;
	case keGamePlaying:
		checkForMatches();
		break;
	case keNonMatch:
		delayGameForNonmatch(deltaTime);
		break;
	case keBoardReset:
		break;
	}
	// Update time in state
	// If it is time to exit then go in active

	// If a minute has gone by, or we're in the final 10 seconds of the game, then beep to alert the user.
	if((mTime < TimeLimit) && 
		((((int)mTime % 60) == 0) && ((int)mTime > (int)(mTime - deltaTime))) || 
		((mTime <= 11) && ((int)mTime > (int)(mTime - deltaTime))))
	{
		g_pAudio->PlaySound(g_pResources->GetTimeSoundFilename());
	}
	if( ( mTime) <= 0 )
	{
		mTime = 0;
		ResultsScene * resultsScene= (ResultsScene*) m_Manager->Find("ResultsState");
		Audio::StopMusic();
		m_Manager->SwitchTo(resultsScene);
		//ResetBoard();
			
		m_GameState = keGameOver;
	}

	mTime -= deltaTime;

	// Update the hud strings
	char scoreBuffer[9];
	sprintf(scoreBuffer, "%.4d", ((GameSceneManager*) m_Manager)->GetScore() );
	mpScoreText->SetText(scoreBuffer);

	int minutes, seconds;
	minutes = (int)( mTime / 60 );
	seconds = (int)( mTime - ( minutes * 60.0f ) );
	
	char timeBuffer[256];
	sprintf(timeBuffer, "%.2d:%.2d", minutes, seconds );
	mpTimeText->SetText(timeBuffer);
	
}

void GameScene::Render()
{
	Scene::Render();
}

void GameScene::StartGame()
{
	ResetBoard();
	//Set time and score to starting values;
	mTime = (float)TimeLimit;
	((GameSceneManager*) m_Manager)->SetScore(0);
	Audio::PlayMusic(g_pResources->GetGameMusicFilename(), true);
}

void GameScene::initialiseBoard()
{
	std::vector<int> characterTypes;
	//Fill vector with exactly 2 of each character type
	for(int i = 0; i < GridHeight*GridWidth; i++)
	{
		characterTypes.push_back((i%(12))); 
	}

	float x = STAR_X_OFFSET*m_XGraphicsScale;
	float y = STAR_Y_OFFSET*m_YGraphicsScale;
	for( int row = 0; row < GridHeight; row++ )
	{
		x = STAR_X_OFFSET*m_XGraphicsScale;
		for( int column = 0; column < GridWidth; column++ )
		{
			int characterTypeIndex = rand() % characterTypes.size();
			int characterIndex = characterTypes.at(characterTypeIndex);
			GridItem* grid = new GridItem( x, y, (characterIndex));
			characterTypes.erase(characterTypes.begin() + characterTypeIndex);

			mGrid[(row*GridWidth)+column] = grid; 
			AddChild( grid->GetStarSprite() );
			AddChild(grid->GetCharacterSprite());

			x += STAR_SPACING*m_XGraphicsScale;
		}

		y += STAR_SPACING*m_YGraphicsScale;
	}

	
}

void GameScene::checkForMatches()
{
	if(m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		for( int count = 0; count < GridWidth*GridHeight; count++ )
		{
			
			g_pInput->Reset();
			if( mGrid[count]->GetStarSprite()->m_IsVisible && mGrid[count]->GetStarSprite()->HitTest( g_pInput->m_X, g_pInput->m_Y ) )
			{
				if(selected1)
				{
					mGrid[count]->GetStarSprite()->m_IsVisible = false;
					mGrid[count]->GetCharacterSprite()->m_IsVisible = true;
					selected2 = mGrid[count];

					if(selected1->GetCharacterIndex() == mGrid[count]->GetCharacterIndex())
					{
						((GameSceneManager*) m_Manager)->IncrementScore(10);
						charactersToRemove.push_back(selected1);
						charactersToRemove.push_back(selected2);
						g_pAudio->PlaySound(g_pResources->GetMatchSoundFilename());
						selected1 = NULL;
						selected2 = NULL;
						m_Timers.Add(new Timer(0.5f, 1, &GameScene::removeMatchedCharacters, (void*)this));
					}
					else
					{
						/*selectedStar->GetCharacterSprite()->m_IsVisible = false;
						selectedStar->GetStarSprite()->m_IsVisible = true;
						selectedStar = NULL;*/
						g_pAudio->PlaySound(g_pResources->GetNonmatchSoundFilename());
						delayTime = 0.5f;
						m_GameState = keNonMatch;
					}
				}
				else
				{
					mGrid[count]->GetStarSprite()->m_IsVisible = false;
					mGrid[count]->GetCharacterSprite()->m_IsVisible = true;
					selected1 = mGrid[count];
				}	
				break;
			}
		}
	}
}

void GameScene::delayGameForNonmatch(float deltaTime)
{
	g_pInput->Reset();
	if(delayTime <= 0)
	{
		selected1->GetCharacterSprite()->m_IsVisible = false;
		selected1->GetStarSprite()->m_IsVisible = true;
		selected1 = NULL;

		selected2->GetCharacterSprite()->m_IsVisible = false;
		selected2->GetStarSprite()->m_IsVisible = true;
		selected2 = NULL;

		delayTime = 0;
		m_GameState = keGamePlaying;
	}
	else
	{
		delayTime -= deltaTime;	
	}
}

void GameScene::removeMatchedCharacters(Timer* timer, void* userData)
{
	GameScene * self = (GameScene*)userData;
	GridItem * char1 = self->charactersToRemove.at(0);
	GridItem * char2 = self->charactersToRemove.at(1);
	self->RemoveChild(char1->GetCharacterSprite());
	self->RemoveChild(char2->GetCharacterSprite());
	self->charactersToRemove.erase(self->charactersToRemove.begin());
	self->charactersToRemove.erase(self->charactersToRemove.begin());
	self->mNoOfMatchedPairs++;
	if(self->mNoOfMatchedPairs == 12)
	{
		g_pAudio->PlaySound(g_pResources->GetBoardCompleteSoundFilename());
		self->mNoOfMatchedPairs = 0;
		self->ResetBoard();
	}
	
}

void GameScene::ResetBoard()
{
	std::vector<int> characterTypes;
	//Fill vector with exactly 2 of each character type
	for(int i = 0; i < GridHeight*GridWidth; i++)
	{
		characterTypes.push_back((i%(12))); 
	}
	for(int i = 0; i < GridHeight*GridWidth; i++)
	{
		int characterTypeIndex = rand() % characterTypes.size();
		int characterIndex = characterTypes.at(characterTypeIndex);
		characterTypes.erase(characterTypes.begin() + characterTypeIndex);

		mGrid[i]->GetStarSprite()->m_IsVisible = true;
		mGrid[i]->SetCharacterImage(characterIndex);
		AddChild(mGrid[i]->GetCharacterSprite());
	}
}

void GameScene::AddButtons()
{
	m_PauseButton = new CSprite();
	m_PauseButton->m_X = BUTTON_STARTING_X*m_XGraphicsScale;
	m_PauseButton->m_Y = BUTTON_STARTING_Y*m_YGraphicsScale;
	m_PauseButton->SetImage(g_pResources->GetPauseButton());
	m_PauseButton->m_H = m_PauseButton->GetImage()->GetHeight();
	m_PauseButton->m_W = m_PauseButton->GetImage()->GetWidth();
	float buttonScale = BUTTON_SPACING / m_PauseButton->m_H;
	float buttonXScale = m_XGraphicsScale * buttonScale;
	float buttonYScale = m_YGraphicsScale * buttonScale;
	m_PauseButton->m_ScaleX = buttonXScale;
	m_PauseButton->m_ScaleY = buttonYScale;
	AddChild(m_PauseButton);

	m_MusicButton = new CSprite();
	m_MusicButton->m_X = (BUTTON_STARTING_X*m_XGraphicsScale) + (BUTTON_X_OFFSET*m_XGraphicsScale);
	m_MusicButton->m_Y = BUTTON_STARTING_Y*m_YGraphicsScale;
	m_MusicButton->SetImage(g_pResources->GetMusicButton());
	m_MusicButton->m_H = m_MusicButton->GetImage()->GetHeight();
	m_MusicButton->m_W = m_MusicButton->GetImage()->GetWidth();
	m_MusicButton->m_ScaleX = buttonXScale;
	m_MusicButton->m_ScaleY = buttonYScale;
	AddChild(m_MusicButton);

	m_MuteMusicButton = new CSprite();
	m_MuteMusicButton->m_X = (BUTTON_STARTING_X*m_XGraphicsScale) + (BUTTON_X_OFFSET*m_XGraphicsScale);
	m_MuteMusicButton->m_Y = BUTTON_STARTING_Y*m_YGraphicsScale;
	m_MuteMusicButton->SetImage(g_pResources->GetMuteMusicButton());
	m_MuteMusicButton->m_H = m_MuteMusicButton->GetImage()->GetHeight();
	m_MuteMusicButton->m_W = m_MuteMusicButton->GetImage()->GetWidth();
	m_MuteMusicButton->m_ScaleX = buttonXScale;
	m_MuteMusicButton->m_ScaleY = buttonYScale;
	m_MuteMusicButton->m_IsVisible = false;
	AddChild(m_MuteMusicButton);

	m_SoundButton = new CSprite();
	m_SoundButton->m_X = (BUTTON_STARTING_X*m_XGraphicsScale) + ((2*BUTTON_X_OFFSET)*m_XGraphicsScale);
	m_SoundButton->m_Y = BUTTON_STARTING_Y*m_YGraphicsScale;
	m_SoundButton->SetImage(g_pResources->GetSoundButton());
	m_SoundButton->m_H = m_SoundButton->GetImage()->GetHeight();
	m_SoundButton->m_W = m_SoundButton->GetImage()->GetWidth();
	m_SoundButton->m_ScaleX = buttonXScale;
	m_SoundButton->m_ScaleY = buttonYScale;
	AddChild(m_SoundButton);

	m_MuteSoundButton = new CSprite();
	m_MuteSoundButton->m_X = (BUTTON_STARTING_X*m_XGraphicsScale) + ((2*BUTTON_X_OFFSET)*m_XGraphicsScale);
	m_MuteSoundButton->m_Y = BUTTON_STARTING_Y*m_YGraphicsScale;
	m_MuteSoundButton->SetImage(g_pResources->GetMuteSoundButton());
	m_MuteSoundButton->m_H = m_MuteSoundButton->GetImage()->GetHeight();
	m_MuteSoundButton->m_W = m_MuteSoundButton->GetImage()->GetWidth();
	m_MuteSoundButton->m_ScaleX = buttonXScale;
	m_MuteSoundButton->m_ScaleY = buttonYScale;
	m_MuteSoundButton->m_IsVisible = false;
	AddChild(m_MuteSoundButton);

	m_ExitButton = new CSprite();
	m_ExitButton->m_X = (BUTTON_STARTING_X*m_XGraphicsScale) + ((3*BUTTON_X_OFFSET)*m_XGraphicsScale);
	m_ExitButton->m_Y = BUTTON_STARTING_Y*m_YGraphicsScale;
	m_ExitButton->SetImage(g_pResources->GetExitButton());
	m_ExitButton->m_H = m_ExitButton->GetImage()->GetHeight();
	m_ExitButton->m_W = m_ExitButton->GetImage()->GetWidth();
	m_ExitButton->m_ScaleX = buttonXScale;
	m_ExitButton->m_ScaleY = buttonYScale;
	AddChild(m_ExitButton);
}

