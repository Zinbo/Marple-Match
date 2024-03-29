/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 *
 * Edited for the Search for a Star Competition 2014
 */

#if !defined(__RESOURCES_H__)
#define __RESOURCES_H__

#include "Iw2D.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraph;

/**
 * @class Resources
 *
 * @brief Resources class
 *
 * The that manages the lifetime of the following types of resources:
 * - Images
 * - Fonts
 * - Atlases
 */
class Resources
{
private:
	enum characterElements { keNoOfCharacterColours = 4, keNoOfCharacterTypes = 3};

    //Backgrounds
	CIw2DImage*		m_TitleBackground;
	CIw2DImage*		m_ResultBackground;
	CIw2DImage*		m_MultiplayerResultBackground;
	CIw2DImage*		m_GameBackground;
	CIw2DImage*		m_InstructionsBackground;
	CIw2DImage*		m_MultiplayerGameBackground;

	//Dialogs
	CIw2DImage*		m_SettingsMenuDialog;
	CIw2DImage*		m_GameStartDialog;
	CIw2DImage*		m_GameOverDialog;
	CIw2DImage*		m_LevelWonDialog;
	CIw2DImage*		m_ExitGameDialog;
	CIw2DImage*		m_PauseMenu;

	//Fonts
    CIw2DFont*      m_Size8Font;
	CIw2DFont*      m_Size15Font;
	CIw2DFont*		m_Size20Font;
	CIw2DFont*		m_Size30Font;

	//Board Elements
	CIw2DImage*     m_Star;
	CIw2DImage*		m_Characters[(keNoOfCharacterColours*keNoOfCharacterTypes)+2];
	
	//Buttons
	CIw2DImage *	m_MusicButton;
	CIw2DImage *	m_MuteMusicButton;
	CIw2DImage *	m_SoundButton;
	CIw2DImage *	m_MuteSoundButton;
	CIw2DImage *	m_PlayButton;
	CIw2DImage *	m_ExitButton;
	CIw2DImage*		m_SettingsButton;
	CIw2DImage*		m_Player1Button;
	CIw2DImage*		m_Player2Button;
	CIw2DImage*		m_InstructionsButton;
	CIw2DImage*		m_PlayAgainButton;
	CIw2DImage*		m_MainMenuButton;
	CIw2DImage*		m_CancelButton;
	CIw2DImage*		m_ConfirmButton;
	CIw2DImage*		m_InvButton;
	CIw2DImage*		m_StartButton;
	CIw2DImage*		m_ScoreBoardButton;
	CIw2DImage*		m_ItemShopButton;
	CIw2DImage*		m_NextLevelButton;
	CIw2DImage*		m_TimeAttackButton;

	//Misc
	CIw2DImage*		m_FacebookIcon;

	//Sound paths
	char*			m_MatchSound;
	char*			m_NonmatchSound;
	char*			m_GoldPickupSound;
	char*			m_SilverPickupSound;
	char*			m_GameMusic;
	char*			m_TimeSound;
	char*			m_MenuMusic;
	char*			m_BoardComplete;
	char*			m_EmptySound;

public:
	//backgrounds
	CIw2DImage*     GetTitleBackground()						{ return m_TitleBackground; }
	CIw2DImage*     GetInstructionsBackground()					{ return m_InstructionsBackground; }
	CIw2DImage*     GetGameBackground()							{ return m_GameBackground; }
	CIw2DImage*		GetMultiplayerGameBackground()				{ return m_MultiplayerGameBackground; }
	CIw2DImage*     GetResultBackground()						{ return m_ResultBackground; }
	CIw2DImage*     GetMultiplayerResultBackground()			{ return m_MultiplayerResultBackground; }
	
	//font
	CIw2DFont*		GetSize8Font()								{ return m_Size8Font; }
	CIw2DFont*		GetSize15Font()								{ return m_Size15Font; }
	CIw2DFont*		GetSize20Font()								{ return m_Size20Font; }
	CIw2DFont*		GetSize30Font()								{ return m_Size30Font; }

	//Board Elements
	CIw2DImage*		GetCharacter(int index)						{ return m_Characters[index]; }
	CIw2DImage*     GetStar()									{ return m_Star; }

	//dialogs
	CIw2DImage*		GetSettingsMenuDialog()						{ return m_SettingsMenuDialog; }
	CIw2DImage*		GetGameStartDialog()						{ return m_GameStartDialog; }
	CIw2DImage*		GetGameOverDialog()							{ return m_GameOverDialog; }
	CIw2DImage*		GetLevelWonDialog()							{ return m_LevelWonDialog; }
	CIw2DImage*		GetExitGameDialog()							{ return m_ExitGameDialog; }
	CIw2DImage*		GetPauseMenu()								{ return m_PauseMenu; }

	//buttons
	CIw2DImage*		GetMusicButton()							{ return m_MusicButton; }
	CIw2DImage*		GetMuteMusicButton()						{ return m_MuteMusicButton; }
	CIw2DImage*		GetSoundButton()							{ return m_SoundButton; }
	CIw2DImage*		GetMuteSoundButton()						{ return m_MuteSoundButton; }
	CIw2DImage*		GetPlayButton()								{ return m_PlayButton; }
	CIw2DImage*		GetExitButton()								{ return m_ExitButton; }
	CIw2DImage*		GetSettingsButton()							{ return m_SettingsButton; }
	CIw2DImage*		GetPlayer1Button()							{ return m_Player1Button; }
	CIw2DImage*		GetPlayer2Button()							{ return m_Player2Button; }
	CIw2DImage*		GetInstructionsButton()						{ return m_InstructionsButton; }
	CIw2DImage*		GetPlayAgainButton()						{ return m_PlayAgainButton; }
	CIw2DImage*		GetMainMenuButton()							{ return m_MainMenuButton; }
	CIw2DImage*		GetCancelButton()							{ return m_CancelButton; }
	CIw2DImage*		GetConfirmButton()							{ return m_ConfirmButton; }
	CIw2DImage*		GetInvButton()								{ return m_InvButton; }
	CIw2DImage*		GetStartButton()							{ return m_StartButton; }
	CIw2DImage*		GetScoreBoardButton()						{ return m_ScoreBoardButton; }
	CIw2DImage*		GetNextLevelButton()						{ return m_NextLevelButton; }
	CIw2DImage*		GetItemShopButton()							{ return m_ItemShopButton; }
	CIw2DImage*		GetTimeAttackButton()						{ return m_TimeAttackButton; }

	//Misc
	CIw2DImage*		GetFacebookIcon()							{ return m_FacebookIcon; }

	char*			GetMatchSoundFilename()						{ return m_MatchSound; }
	char*			GetNonmatchSoundFilename()					{ return m_NonmatchSound; }
	char*			GetGoldPickupSoundFilename()				{ return m_GoldPickupSound; }
	char*			GetSilverPickupSoundFilename()				{ return m_SilverPickupSound; }
	char*			GetGameMusicFilename()						{ return m_GameMusic; }
	char*			GetTimeSoundFilename()						{ return m_TimeSound; }
	char*			GetMenuMusicFilename()						{ return m_MenuMusic; }
	char*			GetBoardCompleteSoundFilename()				{ return m_BoardComplete; }
	char*			GetEmptySoundFilename()						{ return m_EmptySound; }

    Resources();
    ~Resources();
};

extern Resources* g_pResources;




#endif  // __RESOURCES_H__


