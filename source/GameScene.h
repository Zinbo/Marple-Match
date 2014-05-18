#pragma once
#include "MasterScene.h"
#include "CharacterBuilder.h"
#include "audio.h"
#include "resources.h"
#include "IwGx.h"
#include "input.h"
#include "GridItem.h"
#include "GameSceneManager.h"

namespace SFAS2014
{

class GridItem;
	
class GameScene : public MasterScene
{
public: 
	GameScene(int noOfPlayers, float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingMenu, const float starSize);
	~GameScene();

	void Init();
	void Reset();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

private:
	void Create();
	void Destroy();

	enum GridElements 
	{
		keGridWidth = 4,
		keGridHeight = 6
	};

	enum GameElements 
	{
		keTimeLimit = 120
	};

	enum GameState
	{                                                                                                                                                                                                                                                                
		keGamePlaying,
		keGamePause,
		keNonMatch,
		keGameOver
	};

	GameState m_GameState;
	int m_NoOfPlayers;

	vector<CLabel*> m_ScoreLabel;
	vector<CLabel*> m_TimeLabel;

	vector<bool> m_DoublePoints;
	vector<bool> m_TriplePoints;
	vector<bool> m_Delayed;

	vector<vector<GridItem*>> m_Grid;
	vector<GridItem*> m_FirstSelectedItem;
	vector<GridItem*> m_SecondSelectedItem;
	vector<vector<GridItem*>> m_CharactersToRemove;

	vector<int> m_NoOfMatchedPairs;

	float m_Time;
	vector<float> m_DelayTime;
	vector<Timer*> m_DoublePointsTimer;
	vector<Timer*> m_TriplePointsTimer;

	//Methods

	//Matching characters
	void CheckForAnyMatches();
	void CheckGridForMatch(int player);
	void ProcessMatch(int player);
	void ProcessGoldMatch(int player);
	void ProcessSilverMatch(int player);
	void ProcessNormalMatch(int player);
	void DelayGameForNonmatch(float deltaTime, int player);
	void RemoveMatchedCharacterPairFromList(int player);
	static void remove_player_1_matched_characters(Timer* timer, void* userData);
	static void remove_player_2_matched_characters(Timer* timer, void* userData);
	bool StarHasBeenTouched(GridItem* gridItem);
	void IncrementScore(int amount, int player);
	void ProcessIncorrectMatch(int player);
	void ProcessOddPowerupMatch(int player);
	GridItem* FindOtherHalfOfPair(GridItem* gridItem, int player);

	//Init helpers
	void InitBoard();
	virtual void InitLabels() = 0;

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
	void ExitScene() = 0;

	//Update scene helpers
	void UpdateLabels();
	void SetupCharactersArray(std::vector<CharacterBuilder> &characterTypes);
	virtual void AddGridToScene(std::vector<CharacterBuilder> &characterTypes, int player) = 0;
	void RemoveCharactersAfterDelay(int player);
	void HideCharacter(GridItem * gridItem);
	void ShowCharacter(GridItem * gridItem);

	//consts
	/*
	static const float kLabelHeight;
	static const float kLabelWidth;

	static const vector<float> kTimeTextX;
	static const vector<float> kTimeTextY;
	static const vector<float> kScoreTextX;
	static const vector<float> kScoreTextY;
	
	static const vector<float> kStarXOffset;
	static const vector<float> kStarYOffset;
	static const float kStarXSpacing;
	static const float kStarYSpacing;
	*/
	const float kStarSize;

	const float kGoldProb;
	const float kSilverProb;
};
}