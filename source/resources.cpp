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
    Circle = Iw2DCreateImage("textures/Circle.png");
    Square = Iw2DCreateImage("textures/Square.png");
    Triangle= Iw2DCreateImage("textures/Triangle.png");
    Star = Iw2DCreateImage("textures/Star.png");
	Background = Iw2DCreateImage( "textures/background.png" );

	// Load fonts
    Font = Iw2DCreateFont("fonts/arial8.gxfont");
}

Resources::~Resources()
{
    delete Circle;
    delete Square;
    delete Triangle;
	delete Star;
    delete Background;

	delete Font;
}

// Global resources
Resources* g_pResources = 0;



