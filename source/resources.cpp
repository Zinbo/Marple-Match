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
	ResultBackground = Iw2DCreateImage( "textures/resultScreen.png" );
	// Load fonts
    Font = Iw2DCreateFont("fonts/arial8.gxfont");
}

Resources::~Resources()
{
	delete Star;
	delete TitleBackground;
	delete GameBackground;
	delete ResultBackground;
	delete Font;
}

// Global resources
Resources* g_pResources = 0;



