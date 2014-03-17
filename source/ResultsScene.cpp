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
	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
	background->SetImage(g_pResources->getBackground());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
 
	// Fit background to screen size
	background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
	AddChild(background);

	// Create the title text
	gameOver = new CLabel();
	gameOver->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	gameOver->m_Y = (float)IwGxGetScreenHeight() * 0.15f;
	gameOver->SetFont(g_pResources->getFont());
	gameOver->SetText("GAME OVER!");
	gameOver->m_AnchorX = 0.5;
	gameOver->m_AnchorY = 0.5;
	gameOver->m_Color = CColor(255,255,255,255);
	AddChild(gameOver);

	// Create the title text
	tapContinue = new CLabel();
	tapContinue->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	tapContinue->m_Y = (float)IwGxGetScreenHeight() * 0.65f;
	tapContinue->SetFont(g_pResources->getFont());
	tapContinue->SetText("TAP TO CONTINUE");
	tapContinue->m_AnchorX = 0.5;
	tapContinue->m_AnchorY = 0.5;
	tapContinue->m_Color = CColor(0,0,0,255);
	AddChild(tapContinue);
}

void ResultsScene::Update(float deltaTime, float alphaMul)
{
	//if not current scene, don't bother updating.
	if(!(m_Manager->GetCurrent() == this))
	{
		return;
	}
	Scene::Update(deltaTime, alphaMul);
	if(m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		g_pInput->Reset();
		TitleScene * titleScene = (TitleScene *) m_Manager->Find("TitleState");
		m_Manager->SwitchTo(titleScene);
	}
}

void ResultsScene::Render()
{
	Scene::Render();
}

