/*
 * (C) 2014 Search for a Star
 * 
 */

#include "GameSceneManager.h"

#include "TitleScene.h"
#include "GameScene.h"
#include "ResultsScene.h"
#include "input.h"

using namespace SFAS2014;

//
//
// GameSceneManager class
//
//
GameSceneManager::GameSceneManager() : mTimeInGame( 0.0f )
{
	// Create the game scenes 
	m_pScenes[TitleState] = new TitleScene();
	m_pScenes[GameState] = new GameScene();
	m_pScenes[ResultsState] = new ResultsScene();

	// Set the scene names
	m_pScenes[TitleState]->SetName( "TitleState" );
	m_pScenes[GameState]->SetName( "GameState" );
	m_pScenes[ResultsState]->SetName( "ResultsState" );

	// Add and init all the scenes
	for( int count = 0; count < NumberOfStates; count++ )
	{
		m_pScenes[count]->Init();
		Add( m_pScenes[count] );
	}

	SwitchTo( GameSceneManager::TitleState );
}

GameSceneManager::~GameSceneManager()
{
	// Scenes are deleted by the scene manager destructor
}

void GameSceneManager::Update(float deltaTime)
{
	SceneManager::Update( deltaTime );	
	bool pressed = false;

	// Detect screen tap
    if(!g_pInput->m_Touched && g_pInput->m_PrevTouched)
    {
		g_pInput->Reset();
		pressed = true;
	}

	if( pressed && m_Current == m_pScenes[TitleState] )
	{
		m_Current->Reset();
		SwitchTo( GameState );
	}
	else if( m_Current == m_pScenes[GameState] )
	{
		if( !m_Current->IsActive() )
		{
			m_Current->Reset();
			SwitchTo( ResultsState );
		}
		mTimeInGame += deltaTime;
	}
	else if( pressed && m_Current == m_pScenes[ResultsState] )
	{
		m_Current->Reset();
		SwitchTo( TitleState );
		mTimeInGame = 0.0f;
	}
}

void GameSceneManager::SwitchTo(GameSceneManager::State state)
{
	SceneManager::SwitchTo( m_pScenes[state] );
}
