/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__GAMESCENE_H__)
#define __GAMESCENE_H__

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
 * @class GameScene
 *
 * @brief Displays and updates the game
 *
 */
class GameScene : public Scene
{

public:
	GameScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingMenu);
    ~GameScene();

    /**
     * @fn    void GameScene::Init();
     *
     * @brief Initialise the scene.
     */
    void    Init();

    /**
     * @fn    void GameScene::Reset();
     *
     * @brief Resets the scene.
     */
    void    Reset();

    /**
     * @fn    virtual void GameScene::Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
     *
     * @brief Update the scene.
     *
     * @brief Updates this scene
     *
     * @param deltaTime   Number of seconds that has passed since Update() was last called.
     * @param alphaMul    The alpha value being passed down to this node. Default value is 1.
     */
    void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

    /**
     * @fn    virtual void GameScene::Render();
     *
     * @brief Render the scene.
     */
    void Render(); 

private: 
	//Enums
	enum { GridWidth = 4, GridHeight = 6 };
	enum { TouchScore = 10, TimeLimit = 5 };
	enum GameState
	{
		keGameStart,
		keGamePlaying,
		keGamePause,
		keNonMatch,
		keGameOver
	};
	GameState m_GameState;

	//Sprites
	CSprite* m_Background;
	CSprite* m_SettingsButton;

	//Labels
	CLabel* m_ScoreLabel;
	CLabel* m_TimeLabel;
	
	//Flags
	bool m_DoublePoints;

	//Variables for grid
	SFAS2014::GridItem * m_Grid[GridWidth*GridHeight];
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
	void IncrementScore();
	void ProcessIncorrectMatch();
	void ProcessOddPowerupMatch();
	GridItem* FindOtherHalfOfPair(GridItem* gridItem);

	//Init helpers
	void InitBoard();
	void InitButtons();
	void InitLabels();
	void InitUI();
	void InitSound();
	void StartGame();

	//Reset helpers
	void ResetBoard();

	//Settings helpers
	void ToggleButtons();
	void ToggleSettingMenu();
	void PauseGame();
	void ResumeGame();
	
	//Powerup helpers
	void RemovePairsPowerUp(GridItem* selected);
	static void ResetDoublePoints(Timer* timer, void* userData);
	
	//Time helpers 
	bool AMinuteHasGoneBy(float deltaTime);
	bool InTheFinal10Seconds(float deltaTime);
	void UpdateTime(float deltaTime);

	//Endgame helpers
	void CleanUpAndChangeScene();

	//Update scene helpers
	void UpdateLabels();
	void SetupCharactersArray(std::vector<CharacterBuilder> &characterTypes);
	void AddGridToScene(std::vector<CharacterBuilder> &characterTypes);
	void RemoveCharactersAfterDelay();
	void HideCharacter(GridItem * gridItem);
	void ShowCharacter(GridItem * gridItem);
	
};
}

#endif  // __GAMESCENE_H__


