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

#define NUMBER_OF_CHARACTER_TYPES 3
#define NUMBER_OF_CHARACTER_COLOURS 4
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
protected:
    CIw2DImage*     Star;
	CIw2DImage*		Background;
	CIw2DImage*		TitleBackground;
	CIw2DImage*		ResultBackground;
	CIw2DImage*		GameBackground;
	CIw2DImage*		m_SettingsMenuDialog;
    CIw2DFont*      m_Size15Font;
	CIw2DFont*		m_Size20Font;
	CIw2DFont*		m_Size30Font;
	CIw2DImage*		Characters[(NUMBER_OF_CHARACTER_TYPES*NUMBER_OF_CHARACTER_COLOURS)+2];
	
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
	
	char*			m_MatchSound;
	char*			m_NonmatchSound;
	char*			m_GoldPickupSound;
	char*			m_SilverPickupSound;
	char*			m_GameMusic;
	char*			m_TimeSound;
	char*			m_MenuMusic;
	char*			m_BoardComplete;

public:
    CIw2DImage*     getStar()									{ return Star; }
    CIw2DImage*     getBackground()								{ return Background; }
	CIw2DImage*     getTitleBackground()						{ return TitleBackground; }
	CIw2DImage*     getGameBackground()							{ return GameBackground; }
	CIw2DImage*     getResultBackground()						{ return ResultBackground; }
	CIw2DFont*		getSize15Font()								{ return m_Size15Font; }
	CIw2DFont*		getSize20Font()								{ return m_Size20Font; }
	CIw2DFont*		getSize30Font()								{ return m_Size30Font; }
	CIw2DImage*		GetCharacter(int index)						{ return Characters[index]; }
	CIw2DImage*		GetSettingsMenuDialog()						{ return m_SettingsMenuDialog; }
	
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
	
	char*			GetMatchSoundFilename()						{ return m_MatchSound; }
	char*			GetNonmatchSoundFilename()					{ return m_NonmatchSound; }
	char*			GetGoldPickupSoundFilename()				{ return m_GoldPickupSound; }
	char*			GetSilverPickupSoundFilename()				{ return m_SilverPickupSound; }
	char*			GetGameMusicFilename()						{ return m_GameMusic; }
	char*			GetTimeSoundFilename()						{ return m_TimeSound; }
	char*			GetMenuMusicFilename()						{ return m_MenuMusic; }
	char*			GetBoardCompleteSoundFilename()				{ return m_BoardComplete; }


public:
    Resources();
    ~Resources();
};

extern Resources* g_pResources;




#endif  // __RESOURCES_H__


