/*
 * (C) 2014 Search for a Star
 * 
 */

#include "GameScene.h"
#include "resources.h"
#include "IwGx.h"
#include "GridItem.h"
#include "input.h"

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
	mpBackground->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	mpBackground->m_Y = (float)IwGxGetScreenHeight() * 0.5f;
	mpBackground->SetImage(g_pResources->getGameBackground());
	mpBackground->m_W = mpBackground->GetImage()->GetWidth();
	
	mpBackground->m_H = mpBackground->GetImage()->GetHeight();
	
	mpBackground->m_AnchorX = 0.5;
	mpBackground->m_AnchorY = 0.5;
 
	float backgroundScale = (float)IwGxGetScreenWidth() / mpBackground->m_W;
	// Fit background to screen size
	mpBackground->m_ScaleX = backgroundScale;
	mpBackground->m_ScaleY = backgroundScale;
	AddChild(mpBackground);
	

	// Create the title text
	mpScoreText = new CLabel();
	mpScoreText->m_X = (float)IwGxGetScreenWidth() - mpScoreText->m_W;
	mpScoreText->m_Y = mpScoreText->m_H;
	mpScoreText->SetFont(g_pResources->getFont());
	mpScoreText->SetText("00000000");
	mpScoreText->m_AnchorX = 1.0;
	mpScoreText->m_AnchorY = 0.0;
	mpScoreText->m_Color = CColor(255,255,255,255);
	AddChild(mpScoreText);

	// Create the title text
	mpTimeText = new CLabel();
	mpTimeText->m_X = mpTimeText->m_W;
	mpTimeText->m_Y = mpTimeText->m_H;
	mpTimeText->SetFont(g_pResources->getFont());
	mpTimeText->SetText("02:00");
	mpTimeText->m_AnchorX = 0.0;
	mpTimeText->m_AnchorY = 0.0;
	mpTimeText->m_Color = CColor(255,255,255,255);
	AddChild(mpTimeText);

	m_GameState = keGameStart;
	mNoOfMatchedPairs = 0;
}

void GameScene::Reset()
{
	mTime = (float)TimeLimit;
	((GameSceneManager*) m_Manager)->SetScore(0);
}

void GameScene::Update(float deltaTime, float alphaMul)
{
	//if not current scene, don't bother updating.
	if(!(m_Manager->GetCurrent() == this))
	{
		return;
	}
	Scene::Update( deltaTime, alphaMul);

	switch(m_GameState)
	{
	case keGameStart:
		initialiseBoard();
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
	mTime -= deltaTime;
	if( ( mTime) <= 0 )
	{
		mTime = 0;
		ResultsScene * resultsScene= (ResultsScene*) m_Manager->Find("ResultsState");
		m_Manager->SwitchTo(resultsScene);
		ResetBoard();
		
	}

	// Update the hud strings

	char scoreBuffer[9];
	sprintf(scoreBuffer, "%.8d", ((GameSceneManager*) m_Manager)->GetScore() );
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

void GameScene::initialiseBoard()
{
	std::vector<int> characterTypes;
	//Fill vector with exactly 2 of each character type
	for(int i = 0; i < GridHeight*GridWidth; i++)
	{
		characterTypes.push_back((i%(12))); 
	}

	float x = 55.0f;
	float y = 95.0f;
	for( int row = 0; row < GridHeight; row++ )
	{
		x = 55.0f;
		for( int column = 0; column < GridWidth; column++ )
		{
			int characterTypeIndex = rand() % characterTypes.size();
			int characterIndex = characterTypes.at(characterTypeIndex);
			GridItem* grid = new GridItem( x, y, (characterIndex));
			characterTypes.erase(characterTypes.begin() + characterTypeIndex);

			mGrid[(row*GridWidth)+column] = grid; 
			AddChild( grid->GetStarSprite() );
			AddChild(grid->GetCharacterSprite());

			x += 70.0f;
		}

		y += 70.0f;
	}

	//Set time and score to starting values;
	mTime = (float)TimeLimit;
	((GameSceneManager*) m_Manager)->SetScore(0);
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

						selected1 = NULL;
						selected2 = NULL;
						m_Timers.Add(new Timer(0.5f, 1, &GameScene::removeMatchedCharacters, (void*)this));
					}
					else
					{
						/*selectedStar->GetCharacterSprite()->m_IsVisible = false;
						selectedStar->GetStarSprite()->m_IsVisible = true;
						selectedStar = NULL;*/
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