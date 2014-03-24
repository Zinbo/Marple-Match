#pragma once
#include "ResultsScene.h"
namespace SFAS2014
{
	class MultiplayerResultsScene  : public ResultsScene
{
public:
	MultiplayerResultsScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingMenu);
	~MultiplayerResultsScene(void);

	    /**
     * @fn    virtual void ResultsScene::Init();
     *
     * @brief Initialise the scene.
     */
	void Init();

	void Reset();

	void Update(float deltaTime, float alphaMul);

private:
	//Labels
	CSprite* m_Background;
	CLabel * m_Player1ScoreLabel;
	CLabel * m_Player2ScoreLabel;

	//methods
	void InitRecentScoreLabels();
	void SetupRecentScoreLabels();
	void InitUI();
	void UpdateForNewScore();
};
}

