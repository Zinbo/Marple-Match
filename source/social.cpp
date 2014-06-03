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

#include "social.h"
#include "s3e.h"

#define FACEBOOK_APP_ID     "560063667439597"

Social* g_pSocial = 0;

Social::~Social()
{
}

bool Social::Init()
{
    // Check that Facebook support is available
    if (s3eFacebookAvailable() != S3E_TRUE)
        return false;

    return true;
}

bool Social::LogIn()
{
    // Check that Facebook support is available
    if (s3eFacebookAvailable() != S3E_TRUE)
        return false;

    // If no session then create one
    if (CurrentSession == 0)
        CurrentSession = s3eFBInit(FACEBOOK_APP_ID);

    if (CurrentSession)
    {
        // Log in to Facebook using the session
        const char* permissions[] = { "read_stream", "publish_stream" };
        if (s3eFBSession_Login(CurrentSession, LoginCallback, this, permissions, sizeof(permissions) / sizeof(permissions[0])) != S3E_TRUE)
            return false;
    }

    return true;
}

void Social::LoginCallback(s3eFBSession *session, s3eResult *result, void *data)
{
    // Recover the context
    Social *context = (Social *)data;

    if (*result == S3E_RESULT_SUCCESS)
    {
        context->LoggedIn = true;

        // Post update to users wall
        context->PostUpdate();
    }
    else
    {
        context->LoggedIn = false;
        context->Waiting = false;
    }
}

bool Social::PostUpdate(const char* update)
{
    Waiting = true;
    StatusUpdate = update;
    if (!PostUpdate())
        return false;
    WaitUntilCompleted();

    return true;
}

bool Social::PostUpdate()
{
    if (LoggedIn)
    {
        // Build a request that is used to post update to users wall
        Request = s3eFBRequest_WithMethodName(CurrentSession, "facebook.stream.publish", "POST");
        s3eFBRequest_AddParamString(Request, "message", StatusUpdate.c_str());
        s3eResult result = s3eFBRequest_Send(Request, RequestCallback, this);
        if (result != S3E_RESULT_SUCCESS)
        {
            s3eFBRequest_Delete(Request);
            Request = NULL;
            return false;
        }
    }
    else
        return LogIn();

    return true;
}

void Social::RequestCallback(s3eFBRequest *request, s3eResult *result, void *data)
{
    // Recover the context
    Social *context = (Social *)data;

    // Delete the request
    s3eFBRequest_Delete(context->Request);
    context->Request = NULL;
    context->Waiting = false;
}

void Social::WaitUntilCompleted()
{
    // Wait for request to complete
    while (Waiting && !s3eDeviceCheckQuitRequest())
    {
        s3eDeviceYield(100);
    }
}
