#pragma once
/*
 * (C) 2014 Search for a Star
 * 
 */


#include "scene.h"
#include "ResultsScene.h"
#include "GameSceneManager.h"
#include "audio.h"
#include "resources.h"
#include "IwGx.h"
#include "GridItem.h"
#include "input.h"
#include "CharacterBuilder.h"


namespace SFAS2014
{
	
class GridItem;

/**
 * @class SinglePlayerGameScene
 *
 * @brief Displays and updates the game
 *
 */
class SinglePlayerGameScene : public MasterScene
{

public:
	SinglePlayerGameScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingMenu);
    ~SinglePlayerGameScene();

    /**
     * @fn    void SinglePlayerGameScene::Init();
     *
     * @brief Initialise the scene.
     */
    void    Init();

    /**
     * @fn    void SinglePlayerGameScene::Reset();
     *
     * @brief Resets the scene.
     */
    void    Reset();

    /**
     * @fn    virtual void SinglePlayerGameScene::Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
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
	//Enums
	enum GridSize { keGridWidth = 4, keGridHeight = 6 };
	enum GameElements { keTimeLimit = 120 };
	enum GameState
	{                                                                                                                                                                                                                                                                
		keGamePlaying,
		keGamePause,
		keNonMatch,
		keGameOver
	};
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
	static const float kGoldProb;
	static const float kSilverProb;

	static const float kUpdateToScoreX;
	static const float kUpdateToScoreY;
	static const float kUpdateToScoreHeight;
	static const float kUpdateToScoreWidth;

	static const float kUpdateToTimeX;
	static const float kUpdateToTimeY;
	static const float kUpdateToTimeHeight;
	static const float kUpdateToTimeWidth;

	GameState m_GameState;

	//Labels
	CLabel* m_ScoreLabel;
	CLabel* m_TimeLabel;
	CLabel* m_UpdateToScoreLabel;
	CLabel* m_UpdateToTimeLabel;
	
	//Flags
	bool m_DoublePoints;

	//Variables for grid
	SFAS2014::GridItem * m_Grid[keGridWidth*keGridHeight];
	SFAS2014::GridItem * m_FirstSelectedItem;
	SFAS2014::GridItem * m_SecondSelectedItem;
	std::vector<GridItem *> m_CharactersToRemove;
	int m_NoOfMatchedPairs;	

	//Variables for time
	float m_Time;
	float m_DelayTime;
	Timer* m_DoublePointsTimer;

	//Methods

	//Matching characters
	void CheckForMatches();
	void ProcessMatch();
	void ProcessGoldMatch();
	void ProcessSilverMatch();
	void ProcessNormalMatch();
	void DelayGameForNonmatch(float deltaTime);
	void RemoveMatchedCharacterPairFromList();
	static void RemoveMatchedCharacters(Timer* timer, void* userData);
	bool StarHasBeenTouched(int gridIndex);
	void IncrementScore(int amount);
	void ProcessIncorrectMatch();
	void ProcessOddPowerupMatch();
	void DisplayUpdateToScore(char scoreBonus[]);
	void DisplayUpdateToTime(char timeBonus[]);
	GridItem* FindOtherHalfOfPair(static const GridItem* gridItem) const;
	void FadeLabels();

	//Init helpers
	void InitBoard();
	void InitButtons();
	void InitLabels();
	void InitUI();
	void StartGame();

	//Reset helpers
	void ResetBoard();

	//Settings helpers
	void PauseGame();
	void ResumeGame();
	
	//Powerup helpers
	void RemovePairsPowerUp(GridItem* selected);
	static void ResetDoublePoints(Timer* timer, void* userData);
	
	//Time helpers 
	bool AMinuteHasGoneBy(float deltaTime) const;
	bool InTheFinal10Seconds(float deltaTime) const;
	void UpdateTime(float deltaTime);

	//Endgame helpers
	void ExitScene();

	//Update scene helpers
	void UpdateLabels();
	void SetupCharactersArray(std::vector<CharacterBuilder> &characterTypes);
	void AddGridToScene(std::vector<CharacterBuilder> &characterTypes);
	void RemoveCharactersAfterDelay();
	void HideCharacter(GridItem * gridItem);
	void ShowCharacter(GridItem * gridItem);
	
};
}



