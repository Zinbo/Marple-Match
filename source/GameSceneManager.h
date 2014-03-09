/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__GAMESCENEMANAGER_H__)
#define __GAMESCENEMANAGER_H__

#include "scene.h"

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

private: 
	
	Scene * m_pScenes[NumberOfStates];
	float mTimeInGame;

};
}

#endif  // __GAMESCENEMANAGER_H__


