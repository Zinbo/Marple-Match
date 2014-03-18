/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__RESULTSSCENE_H__)
#define __RESULTSSCENE_H__

#include "scene.h"
#include <sstream>

namespace SFAS2014
{

/**
 * @class ResultsScene
 *
 * @brief Displays the results of the game
 *
 */
class ResultsScene : public Scene
{

public:
    ResultsScene();
    ~ResultsScene();

    /**
     * @fn    virtual void ResultsScene::Init();
     *
     * @brief Initialise the scene.
     */
    void    Init();

    /**
     * @fn    virtual void ResultsScene::Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
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
     * @fn    virtual void ResultsScene::Render();
     *
     * @brief Render the scene.
     */
    void Render();

	void    Reset();

private: 
	CLabel * scoreText;
	CLabel * tapToContinue;
	CSprite* background;
	float delay;
};
}

#endif  // __RESULTSSCENE_H__


