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
GameScene::GameScene() : mTime( 0.0f ), mScore(0)
{

}

GameScene::~GameScene()
{

}

void GameScene::Init()
{
	Scene::Init();

	IwRandSeed( time( 0 ) );

	// Create grid sprites
	float x = 32.0f;
	float y = 32.0f;
	for( int row = 0; row < GridHeight; row++ )
	{
		x = 32.0f;
		for( int column = 0; column < GridWidth; column++ )
		{
			int shape = IwRand() % 4;
			GridItem* grid = new GridItem( x, y, (GridItem::Shape)shape );

			mGrid[(row*GridWidth)+column] = grid; 
			AddChild( grid->GetSprite() );

			x += 64.0f;
		}

		y += 64.0f;
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
	mpTimeText->SetText("00:00");
	mpTimeText->m_AnchorX = 0.0;
	mpTimeText->m_AnchorY = 0.0;
	mpTimeText->m_Color = CColor(255,255,255,255);
	AddChild(mpTimeText);
}

void GameScene::Reset()
{
	mTime = 0.0f;
	mScore = 0;
}

void GameScene::Update(float deltaTime, float alphaMul)
{
	Scene::Update( deltaTime, alphaMul);

	// Update time in state
	mTime += deltaTime;

	// If it is time to exit then go in active
	if( ( mTime / 60.0f ) >= TimeLimitInMinutes )
	{
		m_IsActive = false;
		mTime = TimeLimitInMinutes * 60.0f;
	}
	else
	{
		// Highlight shape being touched
		for( int count = 0; count < GridWidth*GridHeight; count++ )
		{
			if( g_pInput->m_Touched )
			{
				if( mGrid[count]->GetSprite()->HitTest( g_pInput->m_X, g_pInput->m_Y ) )
				{
					mGrid[count]->Highlight();
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

	char scoreBuffer[2];
	sprintf(scoreBuffer, "%.8d", mScore );
	mpScoreText->SetText(scoreBuffer);

	int minutes, seconds;
	minutes = ( mTime / 60 );
	seconds = ( mTime - ( minutes * 60.0f ) );
	char timeBuffer[256];
	sprintf(timeBuffer, "%.2d:%.2d", minutes, seconds );
	mpTimeText->SetText(timeBuffer);
}

void GameScene::Render()
{
	Scene::Render();
}

