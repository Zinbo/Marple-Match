/*
 * (C) 2014 Search for a Star
 * 
 */

#include "TitleScene.h"
#include "IwGx.h"
#include "resources.h"
#include "audio.h"

#define BUTTON_SPACING 50.0f
#define BUTTON_STARTING_X 1.0f
#define BUTTON_STARTING_Y 1.0f

using namespace SFAS2014;

//
//
// TitleScene class
//
//
TitleScene::TitleScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingMenu)
{
	m_XGraphicsScale = xGraphicsScale;
	m_YGraphicsScale = yGraphicsScale;
	m_SettingsMenu = settingMenu;
}

TitleScene::~TitleScene()
{

}

void TitleScene::Init()
{
	Scene::Init();
	
	InitUI();
	InitLabels();
	InitButtons();
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
		if(m_SettingsMenu->m_IsVisible && m_SettingsMenu->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			ToggleButtons();
		}
		else if(m_SettingsButton->HitTest(g_pInput->m_X, g_pInput->m_Y) || m_SettingsMenu->m_IsVisible)
		{
			ToggleSettingMenu();
		}
		else
		{
			ChangeSceneAndCleanUp();
		}
		g_pInput->Reset();
	}

}

void TitleScene::Render()
{
	Scene::Render();
}

void TitleScene::Reset()
{
	Scene::Reset();
	Audio::PlayMusic(g_pResources->GetMenuMusicFilename(), true);
	AddChild(m_SettingsMenu);
	//If the sound and music has been turned off in another scene then set the buttons on this scene to reflect this.
}

void TitleScene::InitButtons()
{
	m_SettingsButton = new CSprite();
	m_SettingsButton->m_X = ((float) IwGxGetScreenWidth() - (BUTTON_STARTING_X*m_XGraphicsScale) - (BUTTON_SPACING*m_XGraphicsScale));
	m_SettingsButton->m_Y = BUTTON_STARTING_Y*m_YGraphicsScale;
	m_SettingsButton->SetImage(g_pResources->GetSettingsButton());
	m_SettingsButton->m_H = m_SettingsButton->GetImage()->GetHeight();
	m_SettingsButton->m_W = m_SettingsButton->GetImage()->GetWidth();
	float buttonScale = (m_SettingsButton->m_H / BUTTON_SPACING);
	m_SettingsButton->m_ScaleX = (buttonScale * m_XGraphicsScale);
	m_SettingsButton->m_ScaleY = (buttonScale * m_YGraphicsScale);
	AddChild(m_SettingsButton);

}

void TitleScene::ToggleButtons()
{
	if(m_SettingsMenu->GetPlayButton()->HitTest(g_pInput->m_X, g_pInput->m_Y))
	{
		//TODO
		g_pInput->Reset();
	}
	else if(m_SettingsMenu->GetMusicButton()->HitTest(g_pInput->m_X, g_pInput->m_Y))
	{
		g_pInput->Reset();
		m_SettingsMenu->ToggleMusic();
			
	}
	else if(m_SettingsMenu->GetSoundButton()->HitTest(g_pInput->m_X, g_pInput->m_Y))
	{
		g_pInput->Reset();
		m_SettingsMenu->ToggleSound();
	}
	else if(m_SettingsMenu->GetExitButton()->HitTest(g_pInput->m_X, g_pInput->m_Y))
	{
		//TODO
		g_pInput->Reset();
	}
}

void TitleScene::ToggleSettingMenu()
{
	if(m_SettingsMenu->m_IsVisible)
	{
		m_SettingsMenu->m_IsVisible = false;
	}
	else
	{
		m_SettingsMenu->m_IsVisible = true;
	}
}

void TitleScene::InitUI()
{
	m_Background = new CSprite();
	m_Background->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_Background->m_Y = (float)IwGxGetScreenHeight() * 0.5f;
	m_Background->SetImage(g_pResources->getTitleBackground());
	m_Background->m_W = m_Background->GetImage()->GetWidth();
	
	m_Background->m_H = m_Background->GetImage()->GetHeight();
	
	m_Background->m_AnchorX = 0.5;
	m_Background->m_AnchorY = 0.5;
 
	//Fit background to screen size
	m_Background->m_ScaleX = (float)IwGxGetScreenWidth() / m_Background->m_W;
	m_Background->m_ScaleY = (float)IwGxGetScreenHeight() / m_Background->m_H;
	AddChild(m_Background);
}

void TitleScene::InitLabels()
{
	m_TitleText = new CLabel();
	m_TitleText->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_TitleText->m_Y = (float)IwGxGetScreenHeight() * 0.65f;
	m_TitleText->SetFont(g_pResources->getFont());
	m_TitleText->SetText("TAP TO BEGIN");
	m_TitleText->m_AnchorX = 0.5;
	m_TitleText->m_AnchorY = 0.5;
	m_TitleText->m_Color = CColor(0,0,0,255);
	AddChild(m_TitleText);
}

void TitleScene::ChangeSceneAndCleanUp()
{
	GameScene * gameScene = (GameScene *) m_Manager->Find("GameState");
	Audio::StopMusic();
	m_Manager->SwitchTo(gameScene);
}

