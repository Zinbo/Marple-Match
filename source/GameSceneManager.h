/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__GAMESCENEMANAGER_H__)
#define __GAMESCENEMANAGER_H__

#include "scene.h"
#include "SettingsMenu.h"

namespace SFAS2014
{
/**
 * @class GameSceneManager
 *
 * @brief Manages the state of the game.
 *
 */
class GameSceneManager : public SceneManager
{

public:
    GameSceneManager();
    ~GameSceneManager();

	enum State
	{
		TitleState,
		GameState,
		ResultsState,
		MultiplayerGameState,
		NumberOfStates
	};

    /**
     * @fn    void GameSceneManager::Update(float deltaTime = 0.0f);
     *
     * @brief Updates the state of the game
     *
     * @param deltaTime   Number of seconds that has passed since Update() was last called.
     */
    void    Update(float deltaTime = 0.0f);

    /**
     * @fn    void GameSceneManager::SwitchTo(GameSceneManager::State state);
     *
     * @brief Switches the state of the game
     *
     * @param state  The state to switch to.
     */
	void    SwitchTo(GameSceneManager::State state);

	void IncrementScore(int incrementValue, int player);
	int GetScore(int player);
	void SetScore(int score, int player);


private: 
	
	Scene * m_pScenes[NumberOfStates];
	int m_GameScore[2];
	bool	m_MusicPlaying;
	bool	m_SoundPlaying;
	SettingsMenu* settingsMenu;

	void CreateSettingsMenu();

};
}

#endif  // __GAMESCENEMANAGER_H__


