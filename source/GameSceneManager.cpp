/*
 * (C) 2014 Search for a Star
 * 
 */

#include "GameSceneManager.h"

#include "TitleScene.h"
#include "GameScene.h"
#include "ResultsScene.h"
#include "MultiplayerGameScene.h"
#include "MultiplayerResultsScene.h"
#include "InstructionsScene.h"
#include "input.h"

#define GRAPHIC_DESIGN_WIDTH 320
#define GRAPHIC_DESIGN_HEIGHT 480
#define SETTINGS_MENU_X_SIZE 200.0f
#define SETTINGS_MENU_Y_SIZE 350.0f

using namespace SFAS2014;

//
//
// GameSceneManager class
//
//
GameSceneManager::GameSceneManager()
	:m_MusicPlaying(true), m_SoundPlaying(true)
{
	float xGraphicsScale = (float) IwGxGetScreenWidth() / GRAPHIC_DESIGN_WIDTH;
	float yGraphicsScale = (float) IwGxGetScreenHeight() / GRAPHIC_DESIGN_HEIGHT;

	m_GameScore[0] = 0;
	m_GameScore[1] = 0;

	settingsMenu = new SettingsMenu(xGraphicsScale, yGraphicsScale);
	settingsMenu->SetImage(g_pResources->GetSettingsMenuDialog());
	settingsMenu->m_X = 60*xGraphicsScale;
	settingsMenu->m_Y= 65*yGraphicsScale;
	settingsMenu->m_H = settingsMenu->GetImage()->GetHeight();
	settingsMenu->m_W = settingsMenu->GetImage()->GetWidth();
	settingsMenu->m_ScaleX = xGraphicsScale * ( SETTINGS_MENU_X_SIZE / settingsMenu->m_W);
	settingsMenu->m_ScaleY = yGraphicsScale * ( SETTINGS_MENU_Y_SIZE / settingsMenu->m_H);
	settingsMenu->m_IsVisible = false;

	// Create the game scenes 
	m_pScenes[TitleState] = new TitleScene(xGraphicsScale, yGraphicsScale, settingsMenu);
	m_pScenes[GameState] = new GameScene(xGraphicsScale, yGraphicsScale, settingsMenu);
	m_pScenes[ResultsState] = new ResultsScene(xGraphicsScale, yGraphicsScale, settingsMenu);
	m_pScenes[MultiplayerGameState] = new MultiplayerGameScene(xGraphicsScale, yGraphicsScale, settingsMenu);
	m_pScenes[InstructionState] = new InstructionsScene(xGraphicsScale, yGraphicsScale);
	m_pScenes[MultiplayerResultsState] = new MultiplayerResultsScene(xGraphicsScale, yGraphicsScale, settingsMenu);

	// Set the scene names
	m_pScenes[TitleState]->SetName( "TitleState" );
	m_pScenes[GameState]->SetName( "GameState" );
	m_pScenes[ResultsState]->SetName( "ResultsState" );
	m_pScenes[MultiplayerGameState]->SetName( "MultiplayerState" );
	m_pScenes[InstructionState]->SetName( "InstructionsState" );
	m_pScenes[MultiplayerResultsState]->SetName( "MultiplayerResultsState" );

	// Add and init all the scenes
	for( int count = 0; count < NumberOfStates; count++ )
	{
		Add( m_pScenes[count] );
		m_pScenes[count]->Init();
		
	}

	SwitchTo( GameSceneManager::TitleState );

}
void GameSceneManager::IncrementScore(int incrementValue, int player)
{
	m_GameScore[player] += incrementValue;
}

void GameSceneManager::SetScore(int score, int player)
{
	m_GameScore[player] = score;
}

int GameSceneManager::GetScore(int player)
{
	return m_GameScore[player];
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
