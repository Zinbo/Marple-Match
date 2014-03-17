/*
 * (C) 2014 Search for a Star
 * 
 */

#include "TitleScene.h"
#include "IwGx.h"
#include "resources.h"

using namespace SFAS2014;

//
//
// TitleScene class
//
//
TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Init()
{
	Scene::Init();

	// Create background sprite
	
	mpBackground = new CSprite();
	mpBackground->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	mpBackground->m_Y = (float)IwGxGetScreenHeight() * 0.5f;
	mpBackground->SetImage(g_pResources->getTitleBackground());
	mpBackground->m_W = mpBackground->GetImage()->GetWidth();
	
	mpBackground->m_H = mpBackground->GetImage()->GetHeight();
	
	mpBackground->m_AnchorX = 0.5;
	mpBackground->m_AnchorY = 0.5;
 
	float backgroundScale = (float)IwGxGetScreenWidth() / mpBackground->m_W;
	// Fit background to screen size
	mpBackground->m_ScaleX = backgroundScale;
	mpBackground->m_ScaleY = backgroundScale;
	AddChild(mpBackground);

	// Create the title text
	mpTitleText = new CLabel();
	mpTitleText->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	mpTitleText->m_Y = (float)IwGxGetScreenHeight() * 0.65f;
	mpTitleText->SetFont(g_pResources->getFont());
	mpTitleText->SetText("TAP TO BEGIN");
	mpTitleText->m_AnchorX = 0.5;
	mpTitleText->m_AnchorY = 0.5;
	mpTitleText->m_Color = CColor(0,0,0,255);
	AddChild(mpTitleText);
}

void TitleScene::Update(float deltaTime, float alphaMul)
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
		GameScene * gameScene = (GameScene *) m_Manager->Find("GameState");
		m_Manager->SwitchTo(gameScene);
	}
}

void TitleScene::Render()
{
	Scene::Render();
}
