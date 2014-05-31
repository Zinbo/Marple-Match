#if !defined(__GAMESCENE_H__)
#define __GAMESCENE_H__

#include "MasterScene.h"
#include "CharacterBuilder.h"
#include "audio.h"
#include "resources.h"
#include "IwGx.h"
#include "input.h"
#include "GridItem.h"
#include <vector>

namespace SFAS2014
{

class GridItem;
	
class GameScene : public MasterScene
{
public: 
	GameScene(int noOfPlayers, float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingMenu, const float starSize);
	~GameScene();

	virtual void Init();
	void Reset();
	virtual void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

protected:
	void Create();
	void Destroy();

	struct GridElements
	{
		int gridWidth;
		int gridHeight;
	};

	enum GameElements 
	{
		keTimeLimit = 120
	};

	enum GameState
	{
		keGameStart,
		keGamePlaying,
		keGamePause,
		keNonMatch,
		keGameWon,
		keGameOver
		
	};

	GameState m_GameState;
	int m_NoOfPlayers;
	GridElements m_GridElements;

	std::vector<CLabel*> m_ScoreLabel;
	std::vector<CLabel*> m_TimeLabel;

	std::vector<bool> m_DoublePoints;
	std::vector<bool> m_TriplePoints;
	std::vector<bool> m_Delayed;

	std::vector<std::vector<GridItem*>> m_Grid;
	std::vector<GridItem*> m_FirstSelectedItem;
	std::vector<GridItem*> m_SecondSelectedItem;
	std::vector<std::vector<GridItem*>> m_CharactersToRemove;

	std::vector<int> m_NoOfMatchedPairs;

	float m_Time;
	std::vector<float> m_DelayTime;
	std::vector<Timer*> m_DoublePointsTimer;
	std::vector<Timer*> m_TriplePointsTimer;

	//Methods

	//Matching characters
	void CheckForAnyMatches();
	virtual void CheckGridForMatch(int player);
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
	virtual void ResetGrid(std::vector<CharacterBuilder> characterTypes, int player);
	void Clear();

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
	virtual void UpdateTime(float deltaTime);

	//Endgame helpers
	void ExitScene() = 0;

	//Update scene helpers
	virtual void UpdateLabels();
	virtual void SetupCharactersArray(std::vector<CharacterBuilder> &characterTypes);
	virtual void AddGridToScene(std::vector<CharacterBuilder> &characterTypes, int player) = 0;
	virtual void RemoveCharactersAfterDelay(int player);
	void HideCharacter(GridItem * gridItem);
	void ShowCharacter(GridItem * gridItem);

	const float kStarSize;

	const float kGoldProb;
	const float kSilverProb;
};
}

#endif  // __GAMESCENE_H__