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

#include "Iw2D.h"
#include "input.h"
#include "audio.h"
#include "resources.h"

#include "TitleScene.h"
#include "GameScene.h"
#include "ResultsScene.h"
#include "GameSceneManager.h"

// FRAME_TIME is the amount of time that a single frame should last in seconds
#define FRAME_TIME  (30.0f / 1000.0f)

using namespace SFAS2014;
int main()
{
    // Initialise the 2D graphics system
    Iw2DInit();

    // Create resources
    g_pResources = new Resources();

    // Set up input systems
    g_pInput = new Input();

    // Set up audio systems
    g_pAudio = new Audio();

    // Create scene manager
    GameSceneManager * pSceneManager = new GameSceneManager();

    // Loop forever, until the user or the OS performs some action to quit the app
    while (!s3eDeviceCheckQuitRequest())
    {
        // Update input system
        g_pInput->Update();

        // Update audio system
        g_pAudio->Update();

        // Update scene manager
        pSceneManager->Update(FRAME_TIME);

        // Clear the drawing surface
        Iw2DSurfaceClear(0xffff0000);

        // Render scene manager
        pSceneManager->Render();

        // Show the drawing surface
        Iw2DSurfaceShow();

        // Yield to the OS
        s3eDeviceYield(0);
    }

    // Clean-up
    delete g_pAudio;
    delete g_pInput;
    delete g_pResources;
	delete pSceneManager;
    Iw2DTerminate();

    return 0;
}
