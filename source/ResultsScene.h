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
	//Sprites
	CSprite* background;
	CSprite* m_MusicButton;
	CSprite* m_MuteMusicButton;
	CSprite* m_SoundButton;
	CSprite* m_MuteSoundButton;

	//Labels
	CLabel * m_ScoreLabel;
	CLabel * m_TapLabel;

	//Helper methods

	//Init helpers
	void InitUI();
	void InitLabels();
	void InitButtons();

	//Button helpers
	void ToggleMusic();
	void ToggleSound();
	void SetSoundAndMusicButtons();

	//Scene helpers
	void ChangeSceneAndCleanUp();
	void UpdateLabels();

	float m_Delay;
};
}

#endif  // __RESULTSSCENE_H__


