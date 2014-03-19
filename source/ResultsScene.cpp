/*
 * (C) 2014 Search for a Star
 * 
 */

#include "ResultsScene.h"
#include "IwGx.h"
#include "resources.h"
#include "TitleScene.h"
using namespace SFAS2014;

//
//
// ResultsScene class
//
//
ResultsScene::ResultsScene()
{

}

ResultsScene::~ResultsScene()
{

}

void ResultsScene::Init()
{
	Scene::Init();

	// Create background sprite
	background = new CSprite();
	background->m_X = 0;
	background->m_Y = 0;
	background->SetImage(g_pResources->getResultBackground());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
 
	// Fit background to screen size
	background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
	AddChild(background);

	// Create the score text
	scoreText = new CLabel();
	scoreText->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	scoreText->m_Y = (float)IwGxGetScreenHeight() * 0.65f;
	scoreText->SetFont(g_pResources->getFont());
	scoreText->m_AnchorX = 0.5;
	scoreText->m_AnchorY = 0.5;
	scoreText->m_Color = CColor(0,0,0,255);
	AddChild(scoreText);

	// Create the title text
	tapToContinue = new CLabel();
	tapToContinue->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	tapToContinue->m_Y = (float)IwGxGetScreenHeight() * 0.8f;
	tapToContinue->SetFont(g_pResources->getFont());
	tapToContinue->m_AnchorX = 0.5;
	tapToContinue->m_AnchorY = 0.5;
	tapToContinue->m_Color = CColor(0,0,0,255);
	tapToContinue->SetText("TAP TO CONTINUE");
	tapToContinue->m_IsVisible = false;
	AddChild(tapToContinue);
}

void ResultsScene::Update(float deltaTime, float alphaMul)
{
	//if not current scene, don't bother updating.
	if(!(m_Manager->GetCurrent() == this))
	{
		return;
	}
	char scoreBuffer[20];
	sprintf(scoreBuffer, "%i", ((GameSceneManager*) m_Manager)->GetScore());
	scoreText->SetText(scoreBuffer);

	Scene::Update(deltaTime, alphaMul);
	
	if(delay <= 0)
	{
		tapToContinue->m_IsVisible = true;
		if(m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
		{
			g_pInput->Reset();
			TitleScene * titleScene = (TitleScene *) m_Manager->Find("TitleState");
			m_Manager->SwitchTo(titleScene);
			tapToContinue->m_IsVisible = false;
		}
	}
	else
	{
		g_pInput->Reset();
		delay -= deltaTime;
	}
	

	
}

void ResultsScene::Reset()
{
	delay = 2.0f;
	
}

void ResultsScene::Render()
{
	Scene::Render();
}

