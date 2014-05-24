#pragma once
#include "MultiplayerResultsScene.h"
#include "GameScene.h"

using namespace SFAS2014;

namespace SFAS2014
{

class GridItem;

class MultiplayerGameScene : public GameScene
{
public:
	MultiplayerGameScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingMenu);

private:
	
	//Init helpers
	void InitLabels();
	void InitUI();
	void InitButtons();

	//Powerup helpers
	void RemovePairsPowerUp(GridItem* selected, int player);
	static void reset_player_1_double_points(Timer* timer, void* userData);
	static void reset_player_2_double_points(Timer* timer, void* userData);
	static void reset_player_1_triple_points(Timer* timer, void* userData);
	static void reset_player_2_triple_points(Timer* timer, void* userData);
	
	//Endgame helpers
	void ExitScene();

	//Update scene helpers
	void AddGridToScene(std::vector<CharacterBuilder> &characterTypes, int player);

	static const float kPlayer1TimeTextX;
	static const float kPlayer1TimeTextY;
	static const float kLabelHeight;
	static const float kLabelWidth;
	static const float kPlayer1ScoreTextX;
	static const float kPlayer1ScoreTextY;

	static const float kPlayer2TimeTextX;
	static const float kPlayer2TimeTextY;
	static const float kPlayer2ScoreTextX;
	static const float kPlayer2ScoreTextY;
	
	static const float kPlayer1StarXOffset;
	static const float kPlayer1StarYOffset;
	static const float kPlayer2StarXOffset;
	static const float kPlayer2StarYOffset;
	static const float kStarXSpacing;
	static const float kStarYSpacing;

};

}