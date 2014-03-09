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
	mpBackground->SetImage(g_pResources->getBackground());
	mpBackground->m_W = mpBackground->GetImage()->GetWidth();
	mpBackground->m_H = mpBackground->GetImage()->GetHeight();
	mpBackground->m_AnchorX = 0.5;
	mpBackground->m_AnchorY = 0.5;
 
	// Fit background to screen size
	mpBackground->m_ScaleX = (float)IwGxGetScreenWidth() / mpBackground->GetImage()->GetWidth();
	mpBackground->m_ScaleY = (float)IwGxGetScreenHeight() / mpBackground->GetImage()->GetHeight();
	mpBackground->m_Color = CColor(255,255,255,255);

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
	Scene::Update(deltaTime, alphaMul);
}

void TitleScene::Render()
{
	Scene::Render();
}
