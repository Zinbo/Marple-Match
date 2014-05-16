#pragma once
#include "ResultsScene.h"
#include "IwGx.h"
#include "resources.h"
#include "TitleScene.h"
#include "s3eOSReadString.h"
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

	static const float kPlayer1ScoreX;
	static const float kPlayer1ScoreY;
	static const float kPlayer2ScoreX;
	static const float kPlayer2ScoreY;
	static const float kScoreWidth;
	static const float kScoreHeight;
};
}

