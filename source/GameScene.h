/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__GAMESCENE_H__)
#define __GAMESCENE_H__

#include "scene.h"

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
	enum { TouchScore = 10, TimeLimitInMinutes = 2 };

	SFAS2014::GridItem * mGrid[GridWidth*GridHeight];
	CLabel* mpScoreText;
	CLabel* mpTimeText;

	float mTime;
	int mScore;
};
}

#endif  // __GAMESCENE_H__


