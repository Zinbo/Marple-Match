/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__RESULTSSCENE_H__)
#define __RESULTSSCENE_H__

#include "scene.h"
#include <sstream>
#include "TopScores.h"
#include "MasterScene.h"


namespace SFAS2014
{

/**
 * @class ResultsScene
 *
 * @brief Displays the results of the game
 *
 */
class ResultsScene : public MasterScene
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

protected: 
	//Sprites
	CSprite* m_PlayAgainButton;
	CSprite* m_MainMenuButton;
	TopScores* m_TopScores;

	//Labels
	CLabel* m_ScoreLabel;
	CLabel* m_TopScoreLabels[5];
	CLabel* m_TopScoreNames[5];

	//Init helpers
	void InitUI();
	void InitRecentScoreLabels();
	void InitLeaderboardLabels();
	void InitButtons();

	//Leaderboard helpers
	void SetupLeaderboard();
	void SetupRecentScoreLabels();
	void UpdateForNewScore();
	void PopulateScores();
	void ReadScoresFromFile();
	void WriteScoresToFile();

	//Clean up helpers
	void ExitScene();
	void Reset();

	//Game control helpers
	void ResumeGame();
	void PauseGame();

	static const float kButtonSpacing;
	static const float kButtonStartingX;
	static const float kButtonStartingY;
	static const float kMainMenuButtonX;
	static const float kMainMenuButtonY;
	static const float kPlayAgainButtonX;
	static const float kPlayAgainButtonY;

};
}

#endif  // __RESULTSSCENE_H__


