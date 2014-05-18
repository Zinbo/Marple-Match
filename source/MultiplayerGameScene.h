#pragma once
#include "scene.h"
#include "GameScene.h"
#include "CharacterBuilder.h"
#include "audio.h"
#include "resources.h"
#include "IwGx.h"
#include "input.h"
#include "GridItem.h"
#include "GameSceneManager.h"
#include "MultiplayerResultsScene.h"

namespace SFAS2014
{

class GridItem;

class MultiplayerGameScene : public MasterScene
{
public:
	MultiplayerGameScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingMenu);
	~MultiplayerGameScene(void);

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
	enum { GridWidth = 4, GridHeight = 3 };
	enum { TimeLimit = 120 };

	enum GameState
	{                                                                                                                                                                                                                                                                
		keGamePlaying,
		keGamePause,
		keNonMatch,
		keGameOver
	};

	GameState m_GameState;

	//Labels
	CLabel* m_Player1ScoreLabel;
	CLabel* m_Player2ScoreLabel;
	CLabel* m_Player1TimeLabel;
	CLabel* m_Player2TimeLabel;

	//Flags
	bool m_DoublePoints[2];
	bool m_TriplePoints[2];
	bool m_Delayed[2];

	//Variables for grid
	SFAS2014::GridItem * m_Grid[2][GridWidth*GridHeight];
	SFAS2014::GridItem * m_FirstSelectedItem[2];
	SFAS2014::GridItem * m_SecondSelectedItem[2];
	std::vector<GridItem *> m_Player1CharactersToRemove;
	std::vector<GridItem *> m_Player2CharactersToRemove;
	int m_NoOfMatchedPairs[2];

	//Variables for time
	float m_Time;
	float m_DelayTime[2];
	Timer* m_DoublePointsTimer[2];
	Timer* m_TriplePointsTimer[2];

	//Methods
	//Matching characters
	void CheckForMatches();
	void CheckGridForMatch(int player);
	void ProcessMatch(int player);
	void ProcessGoldMatch(int player);
	void ProcessSilverMatch(int player);
	void ProcessNormalMatch(int player);
	void DelayGameForNonmatch(float deltaTime, int player);
	void RemoveMatchedCharacterPairFromList(int player);
	static void remove_player_1_matched_characters(Timer* timer, void* userData);
	static void remove_player_2_matched_characters(Timer* timer, void* userData);
	bool StarHasBeenTouched(GridItem * gridItem);
	void IncrementScore(int amount, int player);
	void ProcessIncorrectMatch(int player);
	void ProcessOddPowerupMatch(int player);
	GridItem* FindOtherHalfOfPair(GridItem* gridItem, int player);
	

	//Init helpers
	void InitBoard();
	void InitButtons();
	void InitLabels();
	void InitUI();

	//Reset helpers
	void ResetBoard(int player);
	void ResetGrid(std::vector<CharacterBuilder> characterTypes, int player);

	//Settings helpers
	void PauseGame();
	void ResumeGame();
	
	//Powerup helpers
	void RemovePairsPowerUp(GridItem* selected, int player);
	static void reset_player_1_double_points(Timer* timer, void* userData);
	static void reset_player_2_double_points(Timer* timer, void* userData);
	static void reset_player_1_triple_points(Timer* timer, void* userData);
	static void reset_player_2_triple_points(Timer* timer, void* userData);
	
	//Time helpers 
	bool AMinuteHasGoneBy(float deltaTime);
	bool InTheFinal10Seconds(float deltaTime);
	void UpdateTime(float deltaTime);

	//Endgame helpers
	void ExitScene();

	//Update scene helpers
	void UpdateLabels();
	void SetupCharactersArray(std::vector<CharacterBuilder> &characterTypes);
	void AddGridToScene(std::vector<CharacterBuilder> &characterTypes, int player);
	void RemoveCharactersAfterDelay(int player);
	void HideCharacter(GridItem * gridItem);
	void ShowCharacter(GridItem * gridItem);

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
	static const float kStarSize;

	static const float kGoldProb;
	static const float kSilverProb;
};

}