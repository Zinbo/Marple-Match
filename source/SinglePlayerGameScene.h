#pragma once
/*
 * (C) 2014 Search for a Star
 * 
 */

#include "GameScene.h"
#include "ResultsScene.h"

namespace SFAS2014
{
	
class GridItem;

/**
 * @class SinglePlayerGameScene
 *
 * @brief Displays and updates the game
 *
 */
class SinglePlayerGameScene : public GameScene
{

public:
	SinglePlayerGameScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingMenu);

private: 
	
	//Labels
	CLabel * m_UpdateToScoreLabel;
	CLabel * m_UpdateToTimeLabel;

	//Init Helpers
	void InitLabels();
	void InitButtons();
	void InitUI();

	//Powerup helpers
	void RemovePairsPowerUp(GridItem* selected);
	static void ResetDoublePoints(Timer* timer, void* userData);

	//Update scene helpers
	void AddGridToScene(std::vector<CharacterBuilder> &characterTypes, int player);

	//Endgame helpers
	void ExitScene();

	//consts for labels and stars
	static const float kTimeTextX;
	static const float kTimeTextY;

	static const float kScoreTextX;
	static const float kScoreTextY;

	static const float kLabelHeight;
	static const float kLabelWidth;

	static const float kStarXOffset;
	static const float kStarYOffset;
	static const float kStarSpacing;
	static const float kButtonSpacing;
	static const float kButtonStartingX;
	static const float kButtonStartingY;

	static const float kUpdateToScoreX;
	static const float kUpdateToScoreY;
	static const float kUpdateToScoreHeight;
	static const float kUpdateToScoreWidth;

	static const float kUpdateToTimeX;
	static const float kUpdateToTimeY;
	static const float kUpdateToTimeHeight;
	static const float kUpdateToTimeWidth;
};
}



