#pragma once
/*
 * (C) 2014 Search for a Star
 * 
 */

#include "scene.h"
#include "input.h"
#include "GameScene.h"
#include "MultiplayerGameScene.h"

#include "InstructionsScene.h"
#include "IwGx.h"
#include "resources.h"
#include "audio.h"
#include "ResultsScene.h"
#include "MultiplayerResultsScene.h"

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
	CSprite* m_Player1Button;
	CSprite* m_Player2Button;
	CSprite* m_InstructionsButton;

	//Helper methods

	//Init helpers
	void InitUI();
	void InitButtons();

	//Button helpers
	void ToggleButtons();
	void ToggleSettingMenu();

	//Scene helpers
	void CleanUp();
	void SwitchScene(Scene *scene);

	static const float kButtonSpacing;
	static const float kButtonStartingX;
	static const float kButtonStartingY;
	static const float kPlayer1X;
	static const float kPlayer1Y;
	static const float kPlayer2X;
	static const float kPlayer2Y;
	static const float kInstructionsX;
	static const float kInstructionsY;
};
}



