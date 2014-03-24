/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__RESULTSSCENE_H__)
#define __RESULTSSCENE_H__

#include "scene.h"
#include <sstream>
#include "TopScores.h"

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
	ResultsScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingMenu);
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

protected: 
	//Sprites
	CSprite* m_Background;
	CSprite* m_SettingsButton;
	CSprite* m_PlayAgainButton;
	CSprite* m_MainMenuButton;
	TopScores* m_TopScores;

	//Labels
	CLabel * m_ScoreLabel;
	CLabel* m_TopScoreLabels[5];
	CLabel* m_TopScoreNames[5];

	//Helper methods

	//Init helpers
	void InitUI();
	void InitRecentScoreLabels();
	void InitLeaderboardLabels();
	void InitButtons();

	//Button helpers
	void ToggleButtons();
	void ToggleSettingMenu();

	//Scene helpers
	void CleanUp();
	void SwitchScene(Scene* scene);
	void SetupRecentScoreLabels();

	//Leaderboard helpers
	void SetupLeaderboard();
	void UpdateForNewScore();
	void PopulateScores();
	void ReadScores();
	void WriteScores();
};
}

#endif  // __RESULTSSCENE_H__


