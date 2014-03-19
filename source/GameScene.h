/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__GAMESCENE_H__)
#define __GAMESCENE_H__

#include "scene.h"
#include "ResultsScene.h"
#include "GameSceneManager.h"
#include "audio.h"

namespace SFAS2014
{
	
class GridItem;

/**
 * @class GameScene
 *
 * @brief Displays and updates the game
 *
 */
class GameScene : public Scene
{

public:
    GameScene();
    ~GameScene();

    /**
     * @fn    void GameScene::Init();
     *
     * @brief Initialise the scene.
     */
    void    Init();

    /**
     * @fn    void GameScene::Reset();
     *
     * @brief Resets the scene.
     */
    void    Reset();

    /**
     * @fn    virtual void GameScene::Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
     *
     * @brief Update the scene.
     *
     * @brief Updates this scene
     *
     * @param deltaTime   Number of seconds that has passed since Update() was last called.
     * @param alphaMul    The alpha value being passed down to this node. Default value is 1.
     */
    void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

    /**
     * @fn    virtual void GameScene::Render();
     *
     * @brief Render the scene.
     */
    void Render();

private: 

	enum { GridWidth = 4, GridHeight = 6 };
	enum { TouchScore = 10, TimeLimit = 5 };
	enum GameState
	{
		keGameStart,
		keGamePlaying,
		keNonMatch,
		keMatch,
		keBoardReset
	};
	GameState m_GameState;
	SFAS2014::GridItem * mGrid[GridWidth*GridHeight];
	CLabel* mpScoreText;
	CLabel* mpTimeText;
	CSprite * mpBackground;

	float mTime;
	int mNoOfMatchedPairs;
	SFAS2014::GridItem * selected1;
	SFAS2014::GridItem * selected2;
	std::vector<GridItem *> charactersToRemove;
	void initialiseBoard();
	void checkForMatches();
	void delayGameForNonmatch(float deltaTime);
	void ResetBoard();

	static void removeMatchedCharacters(Timer* timer, void* userData);

	float delayTime;
};
}

#endif  // __GAMESCENE_H__


