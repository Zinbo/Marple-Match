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
 *
 */

#include "resources.h"


Resources::Resources()
{
    // Load images
    //Backgrounds
	m_TitleBackground = Iw2DCreateImage( "textures/startMenu.png" );
	m_GameBackground = Iw2DCreateImage( "textures/gameBackground.png" );
	m_MultiplayerGameBackground = Iw2DCreateImage( "textures/multiplayerGameBackground.png" );
	m_ResultBackground = Iw2DCreateImage( "textures/resultScreen.png" );
	m_MultiplayerResultBackground = Iw2DCreateImage( "textures/multiplayerResultScreen.png" );
	m_InstructionsBackground = Iw2DCreateImage("textures/instructionsBackground.png");
	
	//Board Elements
	m_Star = Iw2DCreateImage("textures/Star.png");
	for(int i = 0; i < keNoOfCharacterColours; i++)
	{
		for(int j = 0; j < keNoOfCharacterTypes; j++)
		{
			char filename[50];
			sprintf(filename, "textures/char-%i-%i.png", j, i);
			m_Characters[(i*keNoOfCharacterTypes)+j] = Iw2DCreateImage(filename);
		}
		
	}
	m_Characters[(keNoOfCharacterColours*keNoOfCharacterTypes)] = Iw2DCreateImage("textures/char-gold.png");
	m_Characters[(keNoOfCharacterColours*keNoOfCharacterTypes)+1] = Iw2DCreateImage("textures/char-silver.png");


	// Load fonts
    m_Size8Font = Iw2DCreateFont("fonts/zorque8.gxfont");
	m_Size15Font = Iw2DCreateFont("fonts/zorque15.gxfont");
	m_Size20Font = Iw2DCreateFont("fonts/zorque20.gxfont");
	m_Size30Font = Iw2DCreateFont("fonts/zorque30.gxfont");

	//Load Buttons
	m_MusicButton = Iw2DCreateImage("textures/musicButton.png");
	m_MuteMusicButton = Iw2DCreateImage("textures/muteMusicButton.png");
	m_SoundButton = Iw2DCreateImage("textures/soundButton.png");
	m_MuteSoundButton = Iw2DCreateImage("textures/muteSoundButton.png");
	m_PlayButton = Iw2DCreateImage("textures/playButton.png");
	m_ExitButton = Iw2DCreateImage("textures/exitButton.png");
	m_SettingsButton = Iw2DCreateImage("textures/settingsButton.png");
	m_Player1Button = Iw2DCreateImage("textures/player1Button.png");
	m_Player2Button = Iw2DCreateImage("textures/player2Button.png");
	m_InstructionsButton  = Iw2DCreateImage("textures/instructionsButton.png");
	m_PlayAgainButton = Iw2DCreateImage("textures/PlayAgainButton.png");
	m_MainMenuButton  = Iw2DCreateImage("textures/MainMenuButton.png");
	m_StartButton  = Iw2DCreateImage("textures/StartButton.png");
	m_ConfirmButton  = Iw2DCreateImage("textures/ConfirmationButton.png");
	m_CancelButton  = Iw2DCreateImage("textures/CancellationButton.png");
	m_InvButton  = Iw2DCreateImage("textures/InvButton.png");
	m_ScoreBoardButton = Iw2DCreateImage("textures/ScoreBoardButton.png");
	m_ItemShopButton = Iw2DCreateImage("textures/ItemShopButton.png");
	m_NextLevelButton = Iw2DCreateImage("textures/NextLevelButton.png");
	m_TimeAttackButton = Iw2DCreateImage("textures/TimeAttackButton.png");

	//Load Dialogs
	m_SettingsMenuDialog = Iw2DCreateImage("textures/settingsMenuDialog.png");
	m_PauseMenu = Iw2DCreateImage("textures/pauseMenu.png");
	m_GameStartDialog = Iw2DCreateImage("textures/gameStartDialog.png");
	m_LevelWonDialog = Iw2DCreateImage("textures/LevelClearedDialog.png");
	m_GameOverDialog = Iw2DCreateImage("textures/GameOverDialog.png");
	m_ExitGameDialog = Iw2DCreateImage("textures/ExitGameDialog.png");


	//Store sound filenames;
	m_MatchSound = "audio/Match.wav";
	m_NonmatchSound = "audio/Nonmatch.wav";
	m_GoldPickupSound = "audio/GoldPickup.wav";
	m_SilverPickupSound = "audio/SilverPickup.wav";
	m_BoardComplete = "audio/boardComplete.wav";
	m_TimeSound = "audio/time.wav";
	m_GameMusic = "audio/gameMusic.mp3";
	m_MenuMusic = "audio/menuMusic.mp3";
	m_EmptySound = "audio/emptySound.wav";
	
}

Resources::~Resources()
{
	delete      m_Star;
	delete		m_TitleBackground;
	delete		m_ResultBackground;
	delete		m_MultiplayerResultBackground;
	delete		m_InstructionsBackground;
	delete		m_GameBackground;
	delete		m_MultiplayerGameBackground;
	delete		m_SettingsMenuDialog;
    delete      m_Size8Font;
	delete      m_Size15Font;
	delete		m_Size20Font;
	delete		m_Size30Font;
	
	//Buttons
	delete		m_MusicButton;
	delete		m_MuteMusicButton;
	delete		m_SoundButton;
	delete		m_MuteSoundButton;
	delete		m_PlayButton;
	delete		m_ExitButton;
	delete		m_SettingsButton;
	delete		m_Player1Button;
	delete		m_Player2Button;
	delete		m_InstructionsButton;
	delete		m_PlayAgainButton;
	delete		m_MainMenuButton;


	for(int i = 0; i < keNoOfCharacterTypes*keNoOfCharacterColours; i++)
	{
		delete m_Characters[i];
	}
	//Delete gold and silver characters
	delete m_Characters[keNoOfCharacterColours*keNoOfCharacterTypes];
	delete m_Characters[keNoOfCharacterColours*keNoOfCharacterTypes+1];
}

// Global resources
Resources* g_pResources = 0;



