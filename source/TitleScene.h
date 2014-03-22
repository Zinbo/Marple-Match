/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__TITLESCENE_H__)
#define __TITLESCENE_H__

#include "scene.h"
#include "input.h"
#include "GameScene.h"

namespace SFAS2014
{

/**
 * @class TitleScene
 *
 * @brief Displays the title screen 
 *
 */
class TitleScene : public Scene
{

public:
	TitleScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * SettingsMenu);
    ~TitleScene();

    /**
     * @fn    virtual void TitleScene::Init();
     *
     * @brief Initialise the scene.
     */
    void    Init();

    /**
     * @fn    virtual void TitleScene::Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
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
     * @fn    virtual void TitleScene::Render();
     *
     * @brief Render the scene.
     */
    void Render();

	void Reset();

private: 

	//Sprites
	CSprite* m_Background;
	CSprite* m_SettingsButton;

	//Labels
	CLabel* m_TitleText;

	//Helper methods

	//Init helpers
	void InitUI();
	void InitLabels();
	void InitButtons();

	//Button helpers
	void ToggleButtons();
	void ToggleSettingMenu();

	//Scene helpers
	void ChangeSceneAndCleanUp();
};
}

#endif  // __TITLESCENE_H__


