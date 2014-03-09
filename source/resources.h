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
    CIw2DImage*     Circle;
    CIw2DImage*     Square;
    CIw2DImage*     Triangle;
    CIw2DImage*     Star;
	CIw2DImage*		Background;
    CIw2DFont*      Font;

public:
    CIw2DImage*     getCircle()					{ return Circle; }
    CIw2DImage*     getSquare()					{ return Square; }
    CIw2DImage*     getTriangle()				{ return Triangle; }
    CIw2DImage*     getStar()					{ return Star; }
    CIw2DImage*     getBackground()				{ return Background; }
	CIw2DFont*		getFont()					{ return Font; }

public:
    Resources();
    ~Resources();
};

extern Resources* g_pResources;




#endif  // __RESOURCES_H__


