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
#include "Iw2D.h"


Resources::Resources()
{
    // Load images
    Star = Iw2DCreateImage("textures/Star.png");
	TitleBackground = Iw2DCreateImage( "textures/startMenu.png" );
	GameBackground = Iw2DCreateImage( "textures/gameBackground.png" );
	m_MultiplayerGameBackground = Iw2DCreateImage( "textures/multiplayerGameBackground.png" );
	ResultBackground = Iw2DCreateImage( "textures/resultScreen.png" );
	m_MultiplayerResultBackground = Iw2DCreateImage( "textures/multiplayerResultScreen.png" );
	m_SettingsMenuDialog = Iw2DCreateImage("textures/settingsMenuDialog.png");
	m_InstructionsBackground = Iw2DCreateImage("textures/instructionsBackground.png");
	for(int i = 0; i < NUMBER_OF_CHARACTER_COLOURS; i++)
	{
		for(int j = 0; j < NUMBER_OF_CHARACTER_TYPES; j++)
		{
			char filename[50];
			sprintf(filename, "textures/char-%i-%i.png", j, i);
			Characters[(i*NUMBER_OF_CHARACTER_TYPES)+j] = Iw2DCreateImage(filename);
		}
		
	}
	Characters[(NUMBER_OF_CHARACTER_COLOURS*NUMBER_OF_CHARACTER_TYPES)] = Iw2DCreateImage("textures/char-gold.png");
	Characters[(NUMBER_OF_CHARACTER_COLOURS*NUMBER_OF_CHARACTER_TYPES)+1] = Iw2DCreateImage("textures/char-silver.png");


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

	//Store sound filenames;
	m_MatchSound = "audio/Match.wav";
	m_NonmatchSound = "audio/Nonmatch.wav";
	m_GoldPickupSound = "audio/GoldPickup.wav";
	m_SilverPickupSound = "audio/SilverPickup.wav";
	m_BoardComplete = "audio/boardComplete.wav";
	m_TimeSound = "audio/time.wav";
	m_GameMusic = "audio/gameMusic.mp3";
	m_MenuMusic = "audio/menuMusic.mp3";
	
}

Resources::~Resources()
{
	delete     Star;
	delete		TitleBackground;
	delete		ResultBackground;
	delete		GameBackground;
	delete		m_SettingsMenuDialog;
    delete      m_Size8Font;
	delete      m_Size15Font;
	delete		m_Size20Font;
	delete		m_Size30Font;
	
	//Buttons
	delete	m_MusicButton;
	delete	m_MuteMusicButton;
	delete	m_SoundButton;
	delete	m_MuteSoundButton;
	delete	m_PlayButton;
	delete	m_ExitButton;
	delete		m_SettingsButton;
	delete		m_Player1Button;
	delete		m_Player2Button;
	delete		m_InstructionsButton;
	delete		m_PlayAgainButton;
	delete		m_MainMenuButton;


	for(int i = 0; i < NUMBER_OF_CHARACTER_TYPES*NUMBER_OF_CHARACTER_COLOURS; i++)
	{
		delete Characters[i];
	}
	delete Characters[NUMBER_OF_CHARACTER_COLOURS*NUMBER_OF_CHARACTER_TYPES];
	delete Characters[NUMBER_OF_CHARACTER_COLOURS*NUMBER_OF_CHARACTER_TYPES+1];
}

// Global resources
Resources* g_pResources = 0;



