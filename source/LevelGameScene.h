#pragma once
/*
 * (C) 2014 Search for a Star
 * 
 */

#include "GameScene.h"
#include "ResultsScene.h"
#include "LevelClearedDialog.h"
#include "GameStartDialog.h"
#include "GameOverDialog.h"

namespace SFAS2014
{
	
class GridItem;

/**
 * @class LevelGameScene
 *
 * @brief Displays and updates the game
 *
 */
class LevelGameScene : public GameScene
{

public:
	LevelGameScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingMenu);

private: 
	
	//Labels
	CLabel * m_UpdateToScoreLabel;
	CLabel * m_UpdateToTimeLabel;

	//Dialog boxes
	GameStartDialog * m_GameStartDialog;
	GameOverDialog * m_GameOverDialog;
	LevelClearedDialog * m_LevelClearedDialog;
	CSprite * m_ExitGameDialog;

	//Init Helpers
	void Init();
	void InitLabels();
	void InitButtons();
	void InitUI();
	void InitDialogs();
	void InitLevels();
	void InitGameOverDialog();
	void InitGameStartDialog();
	void InitLevelWonDialog();
	void InitExitDialog();
	void InitBoard();

	void ClearBoard();

	void UpdateLabels();

	void UpdateTime(float time);

	//Powerup helpers
	void RemovePairsPowerUp(GridItem* selected);
	static void ResetDoublePoints(Timer* timer, void* userData);

	//Update scene helpers
	void ResetBoard(int player);
	void ResetGrid(std::vector<CharacterBuilder> characterTypes, int player);
	void SetupCharactersArray(std::vector<CharacterBuilder> &characterTypes);
	void AddGridToScene(std::vector<CharacterBuilder> &characterTypes, int player);
	static void remove_player_1_matched_characters(Timer* timer, void* userData);
	void CheckGridForMatch(int player);
	void RemoveCharactersAfterDelay(int player);
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	bool NextLevelButtonPressed();
	bool GameStartButtonPressed();
	bool ScoreButtonPressed();

	//Endgame helpers
	void ExitScene();

	void PostFacebookUpdate();
	bool FacebookButtonPressed();

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

	struct Level 
	{
		Level(int time, int matches, int pairs) {timeLimit = time; noOfMatchesToWin = matches; noOfPairsPerBoard = pairs; }; 
		int timeLimit; //seconds
		int noOfMatchesToWin;
		int noOfPairsPerBoard;
		static const int ratioLookUp[][2];
	};

	const int noOfLevels;
	std::vector<Level> m_Levels;
	int m_ActiveLevel;
	int m_TotalNumberOfPairs;
};
}



