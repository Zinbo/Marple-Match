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
GameScene::GameScene() : mTime( (float)TimeLimit ), mScore(0)
{

}

GameScene::~GameScene()
{

}

void GameScene::Init()
{
	Scene::Init();

	IwRandSeed( time( 0 ) );

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
}

void GameScene::Reset()
{
	mTime = (float)TimeLimit;
	mScore = 0;
}

void GameScene::Update(float deltaTime, float alphaMul)
{
	//if not current scene, don't bother updating.
	if(!(m_Manager->GetCurrent() == this))
	{
		return;
	}
	Scene::Update( deltaTime, alphaMul);

	// Update time in state
	// If it is time to exit then go in active
	mTime -= deltaTime;
	if( ( mTime) <= 0 )
	{
		mTime = 0;
		ResultsScene * resultsScene= (ResultsScene*) m_Manager->Find("ResultsState");
		m_Manager->SwitchTo(resultsScene);
		
	}
	else
	{
		// Highlight shape being touched
		for( int count = 0; count < GridWidth*GridHeight; count++ )
		{
			if( g_pInput->m_Touched )
			{
				if( mGrid[count]->GetStarSprite()->HitTest( g_pInput->m_X, g_pInput->m_Y ) )
				{
					mGrid[count]->GetStarSprite()->m_IsVisible = false;
					mGrid[count]->GetCharacterSprite()->m_IsVisible = true;
					mScore += TouchScore;
				}
			}
			else
			{
				mGrid[count]->Reset();
			}
		}
	}

	// Update the hud strings

	char scoreBuffer[9];
	sprintf(scoreBuffer, "%.8d", mScore );
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

