/*
 * (C) 2014 Search for a Star
 * 
 */

#include "TitleScene.h"

using namespace SFAS2014;

const float TitleScene::kButtonSpacing = 50.0f;
const float TitleScene::kButtonStartingX = 1.0f;
const float TitleScene::kButtonStartingY = 1.0f;
const float TitleScene::kPlayer1X = 4.0f;
const float TitleScene::kPlayer1Y = 214.0f;
const float TitleScene::kPlayer2X = 164.0f;
const float TitleScene::kPlayer2Y = 214.0f;
const float TitleScene::kInstructionsX = 44.0f;
const float TitleScene::kInstructionsY = 259.0f;


TitleScene::TitleScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingsMenu)
	:MasterScene(xGraphicsScale, yGraphicsScale, settingsMenu)
{
}

void TitleScene::Update(float deltaTime, float alphaMul)
{
	//if not current scene, don't bother updating.
	if(!(m_Manager->GetCurrent() == this))
	{
		return;
	}
	
	Scene::Update(deltaTime, alphaMul);
	
	//Check to see if any buttons have been pressed if the menu is open.
	if( m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		//Check firstly to see if settings menu has been hit, if it hasn't go through each element to see if it has been hit.
		if(!SettingsMenuHitTest())
		{
			if(m_Player1Button->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				GameScene * gameScene = (GameScene *) m_Manager->Find("GameState");
				SwitchScene(gameScene);
			}
			else if(m_Player2Button->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				MultiplayerGameScene * multiplayerScene = (MultiplayerGameScene *) m_Manager->Find("MultiplayerState");
				SwitchScene(multiplayerScene);
			}
			else if(m_InstructionsButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				InstructionsScene * instructionsScene = (InstructionsScene *) m_Manager->Find("InstructionsState");
				SwitchScene(instructionsScene);
			}
			
		}
		g_pInput->Reset();
	}
}


void TitleScene::InitButtons()
{
	m_SettingsButton = new CSprite();
	m_SettingsButton->m_X = ((float) IwGxGetScreenWidth() - (kButtonStartingX*m_XGraphicsScale) - (kButtonSpacing*m_XGraphicsScale));
	m_SettingsButton->m_Y = kButtonStartingY*m_YGraphicsScale;
	m_SettingsButton->SetImage(g_pResources->GetSettingsButton());
	m_SettingsButton->m_H = m_SettingsButton->GetImage()->GetHeight();
	m_SettingsButton->m_W = m_SettingsButton->GetImage()->GetWidth();
	float buttonScale = (kButtonSpacing/m_SettingsButton->m_H);
	m_SettingsButton->m_ScaleX = (buttonScale * m_XGraphicsScale);
	m_SettingsButton->m_ScaleY = (buttonScale * m_YGraphicsScale);
	AddChild(m_SettingsButton);

	m_Player1Button = new CSprite();
	m_Player1Button->m_X = (kPlayer1X * m_XGraphicsScale);
	m_Player1Button->m_Y = (kPlayer1Y * m_YGraphicsScale);
	m_Player1Button->SetImage(g_pResources->GetPlayer1Button());
	m_Player1Button->m_H = m_Player1Button->GetImage()->GetHeight();
	m_Player1Button->m_W = m_Player1Button->GetImage()->GetWidth();
	m_Player1Button->m_ScaleX = m_XGraphicsScale;
	m_Player1Button->m_ScaleY = m_YGraphicsScale;
	AddChild(m_Player1Button);

	m_Player2Button = new CSprite();
	m_Player2Button->m_X = (kPlayer2X * m_XGraphicsScale);
	m_Player2Button->m_Y = (kPlayer2Y * m_YGraphicsScale);
	m_Player2Button->SetImage(g_pResources->GetPlayer2Button());
	m_Player2Button->m_H = m_Player2Button->GetImage()->GetHeight();
	m_Player2Button->m_W = m_Player2Button->GetImage()->GetWidth();
	m_Player2Button->m_ScaleX = m_XGraphicsScale;
	m_Player2Button->m_ScaleY = m_YGraphicsScale;
	AddChild(m_Player2Button);

	m_InstructionsButton = new CSprite();
	m_InstructionsButton->m_X = (kInstructionsX * m_XGraphicsScale);
	m_InstructionsButton->m_Y = (kInstructionsY * m_YGraphicsScale);
	m_InstructionsButton->SetImage(g_pResources->GetInstructionsButton());
	m_InstructionsButton->m_H = m_InstructionsButton->GetImage()->GetHeight();
	m_InstructionsButton->m_W = m_InstructionsButton->GetImage()->GetWidth();
	m_InstructionsButton->m_ScaleX = m_XGraphicsScale;
	m_InstructionsButton->m_ScaleY = m_YGraphicsScale;
	AddChild(m_InstructionsButton);
}

void TitleScene::InitUI()
{
	//Add background
	m_Background = new CSprite();
	m_Background->m_X = 0;
	m_Background->m_Y = 0;
	m_Background->SetImage(g_pResources->GetTitleBackground());
	m_Background->m_W = m_Background->GetImage()->GetWidth();
	m_Background->m_H = m_Background->GetImage()->GetHeight();

	// Fit background to screen size
	m_Background->m_ScaleX = (float)IwGxGetScreenWidth() / m_Background->m_W;
	m_Background->m_ScaleY = (float)IwGxGetScreenHeight() / m_Background->m_H;
	
	AddChild(m_Background);
}

void TitleScene::ExitScene()
{
	//No need to exit scene, always stay on title screen.
}

void TitleScene::ResumeGame()
{
	//Not needed
}

void TitleScene::PauseGame()
{
	//Not needed
}