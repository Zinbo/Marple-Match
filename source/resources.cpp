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
	Char1Red = Iw2DCreateImage( "textures/char-1-r.png" );
	Char2Red = Iw2DCreateImage( "textures/char-2-r.png" );
	Char3Red = Iw2DCreateImage( "textures/char-3-r.png" );
	Char1Blue = Iw2DCreateImage( "textures/char-1-b.png" );
	Char2Blue = Iw2DCreateImage( "textures/char-2-b.png" );
	Char3Blue = Iw2DCreateImage( "textures/char-3-b.png" );
	Char1Green = Iw2DCreateImage( "textures/char-1-g.png" );
	Char2Green = Iw2DCreateImage( "textures/char-2-g.png" );
	Char3Green = Iw2DCreateImage( "textures/char-3-g.png" );
	Char1Orange = Iw2DCreateImage( "textures/char-1-o.png" );
	Char2Orange = Iw2DCreateImage( "textures/char-2-o.png" );
	Char3Orange = Iw2DCreateImage( "textures/char-3-o.png" );

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
	delete Char1Red;
	delete Char2Red;
	delete Char3Red;
	delete Char1Blue;
	delete Char2Blue;
	delete Char3Blue;
	delete Char1Green;
	delete Char2Green;
	delete Char3Green;
	delete Char1Orange;
	delete Char2Orange;
	delete Char3Orange;
}

// Global resources
Resources* g_pResources = 0;



