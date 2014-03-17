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
GameSceneManager::GameSceneManager()
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
}

void GameSceneManager::SwitchTo(GameSceneManager::State state)
{
	SceneManager::SwitchTo( m_pScenes[state] );
}
