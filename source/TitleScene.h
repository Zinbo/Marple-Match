#pragma once
/*
 * (C) 2014 Search for a Star
 * 
 */

#include "MasterScene.h"
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
class TitleScene : public MasterScene
{

public:
	TitleScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * SettingsMenu);
	~TitleScene() {};

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

private: 

	//Init methods
	void InitButtons();
	void InitUI();

	//Sprites
	CSprite* m_Player1Button;
	CSprite* m_Player2Button;
	CSprite* m_InstructionsButton;

	//Methods for cleaning up
	void ExitScene();

	//Method for game control
	void ResumeGame();
	void PauseGame();

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



