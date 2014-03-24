#pragma once
#include "scene.h"
#include "input.h"
#include "TitleScene.h"
#include "resources.h"
#include "audio.h"
#include "input.h"

namespace SFAS2014
{

class InstructionsScene : public Scene
{
public:
	InstructionsScene(float xGraphicsScale, float yGraphicsScale);
	~InstructionsScene(void);
	
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
	CSprite* m_Background;
	CSprite* m_MainMenuButton;

	//Init helpers
	void InitUI();
	void InitButtons();

	//Scene helpers
	void CleanUp();
	void SwitchScene(Scene *scene);
};
}
