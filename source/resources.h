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

#define MAX_GEM_TYPES   5

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
    CIw2DFont*      Font;
	CIw2DImage*		Char1Red;
	CIw2DImage*		Char2Red;
	CIw2DImage*		Char3Red;
	CIw2DImage*		Char1Blue;
	CIw2DImage*		Char2Blue;
	CIw2DImage*		Char3Blue;
	CIw2DImage*		Char1Green;
	CIw2DImage*		Char2Green;
	CIw2DImage*		Char3Green;
	CIw2DImage*		Char1Orange;
	CIw2DImage*		Char2Orange;
	CIw2DImage*		Char3Orange;

public:
    CIw2DImage*     getStar()					{ return Star; }
    CIw2DImage*     getBackground()				{ return Background; }
	CIw2DImage*     getTitleBackground()		{ return TitleBackground; }
	CIw2DImage*     getGameBackground()			{ return GameBackground; }
	CIw2DImage*     getChar1Red()				{ return Char1Red; }
	CIw2DImage*     getChar2Red()				{ return Char2Red; }
	CIw2DImage*     getChar3Red()				{ return Char3Red; }
	CIw2DImage*     getChar1Blue()				{ return Char1Blue; }
	CIw2DImage*     getChar2Blue()				{ return Char2Blue; }
	CIw2DImage*     getChar3Blue()				{ return Char3Blue; }
	CIw2DImage*     getChar1Green()				{ return Char1Green; }
	CIw2DImage*     getChar2Green()				{ return Char2Green; }
	CIw2DImage*     getChar3Green()				{ return Char3Green; }
	CIw2DImage*     getChar1Orange()			{ return Char1Orange; }
	CIw2DImage*     getChar2Orange()			{ return Char2Orange; }
	CIw2DImage*     getChar3Orange()			{ return Char3Orange; }
	CIw2DImage*     getResultBackground()		{ return ResultBackground; }
	CIw2DFont*		getFont()					{ return Font; }

public:
    Resources();
    ~Resources();
};

extern Resources* g_pResources;




#endif  // __RESOURCES_H__


