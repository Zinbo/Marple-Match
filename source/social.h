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
 */

#ifndef __SOCIAL_H
#define __SOCIAL_H

#include <string>
#include "s3eFacebook.h"

/**
 * @class Social
 *
 * @brief Social class handles social interactions
 *
 * The social class currently enables users to log into Facebook and post a textual status update
 *
 * Example usage:
 *
 *    // Set up social system
 *    g_pSocial = new Social();
 *    g_pSocial->Init();
 *
 *    // Post an update (note that this call is blocking)
 *    g_pSocial->PostUpdate("Hello Facebook World");
 *
 * Note that you will need to define the following in order for Facebook post to work:
 * * In Game.cpp change FACEBOOK_APP_ID to your Facebook app ID
 * * In the project mkb file change the following lines:
 *    iphone-bundle-url-name="com.yourcompany.yourappname"
 *    iphone-bundle-url-schemes="fb<Your FACEBOOK_APP_ID>"
 */
class Social
{
public:
    bool            LoggedIn;           // Logged in status
    bool            Waiting;            // Waiting for request to complete
protected:
    std::string     StatusUpdate;       // Update to post to Facenook
    s3eFBSession*   CurrentSession;     // Facebook session
    s3eFBRequest*   Request;            // Facebook request
    bool            LogIn();
    void            WaitUntilCompleted();

public:
    Social() : CurrentSession(0), Request(NULL), LoggedIn(false), Waiting(false) {}
    ~Social();

    /**
     * @fn    bool Social::Init();
     *
     * @brief Initialises the Facebook API
     *
     * @return    true if it succeeds, false if it fails.
     */
    bool        Init();

    /**
     * @fn    bool Social::PostUpdate(const char* update);
     *
     * @brief Posts an update to the users Facebook wall.
     *
     * @param update  Text update to post to users wall.
     *
     * @return    true if it succeeds, false if it fails.
     */
    bool        PostUpdate(const char* update);

    // Internal
    bool        PostUpdate();
    static void LoginCallback(s3eFBSession *session, s3eResult *result, void *data);
    static void RequestCallback(s3eFBRequest *request, s3eResult *result, void *data);

};

extern Social* g_pSocial;

#endif // !__SOCIAL_H
