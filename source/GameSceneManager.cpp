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
	:m_GameScore(0), m_MusicPlaying(true), m_SoundPlaying(true)
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
		Add( m_pScenes[count] );
		m_pScenes[count]->Init();
		
	}

	SwitchTo( GameSceneManager::TitleState );

}

void GameSceneManager::IncrementScore(int incrementValue)
{
	m_GameScore += incrementValue;
}

void GameSceneManager::SetScore(int score)
{
	m_GameScore = score;
}

int GameSceneManager::GetScore()
{
	return m_GameScore;
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
