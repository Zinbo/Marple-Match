/*
 * (C) 2014 Search for a Star
 * 
 */

#include "ResultsScene.h"
#include "IwGx.h"
#include "resources.h"
#include "TitleScene.h"

#define BUTTON_SPACING 50.0f
#define BUTTON_STARTING_X 1.0f
#define BUTTON_STARTING_Y 1.0f

using namespace SFAS2014;

//
//
// ResultsScene class
//
//
ResultsScene::ResultsScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingMenu)
{
	m_XGraphicsScale = xGraphicsScale;
	m_YGraphicsScale = yGraphicsScale;
	m_SettingsMenu = settingMenu;
}

ResultsScene::~ResultsScene()
{

}

void ResultsScene::Init()
{
	Scene::Init();

	InitUI();
	InitLabels();
	InitButtons();
}

void ResultsScene::Update(float deltaTime, float alphaMul)
{
	//if not current scene, don't bother updating.
	if(!(m_Manager->GetCurrent() == this))
	{
		return;
	}
	
	Scene::Update(deltaTime, alphaMul);
	
	if(m_Delay <= 0)
	{
		m_TapLabel->m_IsVisible = true;
	}

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
			if(m_TapLabel->m_IsVisible)
			{
				ChangeSceneAndCleanUp();
			}
		}
		g_pInput->Reset();
	}

	m_Delay -= deltaTime;

	UpdateLabels();
}

void ResultsScene::InitButtons()
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

void ResultsScene::ToggleButtons()
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

void ResultsScene::ToggleSettingMenu()
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

void ResultsScene::ChangeSceneAndCleanUp()
{
	TitleScene * titleScene = (TitleScene *) m_Manager->Find("TitleState");
	Audio::StopMusic();
	m_Manager->SwitchTo(titleScene);
	m_TapLabel->m_IsVisible = false;
}

void ResultsScene::Reset()
{
	Scene::Reset();
	m_Delay = 2.0f;
	Audio::PlayMusic(g_pResources->GetMenuMusicFilename(), true);
	//If the sound and music has been turned off in another scene then set the buttons on this scene to reflect this.
}
void ResultsScene::Render()
{
	Scene::Render();
}

void ResultsScene::InitUI()
{
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
}

void ResultsScene::InitLabels()
{
	// Create the score text
	m_ScoreLabel = new CLabel();
	m_ScoreLabel->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_ScoreLabel->m_Y = (float)IwGxGetScreenHeight() * 0.65f;
	m_ScoreLabel->SetFont(g_pResources->getFont());
	m_ScoreLabel->m_AnchorX = 0.5;
	m_ScoreLabel->m_AnchorY = 0.5;
	m_ScoreLabel->m_Color = CColor(0,0,0,255);
	AddChild(m_ScoreLabel);

	// Create the title text
	m_TapLabel = new CLabel();
	m_TapLabel->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_TapLabel->m_Y = (float)IwGxGetScreenHeight() * 0.8f;
	m_TapLabel->SetFont(g_pResources->getFont());
	m_TapLabel->m_AnchorX = 0.5;
	m_TapLabel->m_AnchorY = 0.5;
	m_TapLabel->m_Color = CColor(0,0,0,255);
	m_TapLabel->SetText("TAP TO CONTINUE");
	m_TapLabel->m_IsVisible = false;
	AddChild(m_TapLabel);
}

void ResultsScene::UpdateLabels()
{
	char scoreBuffer[20];
	sprintf(scoreBuffer, "%i", ((GameSceneManager*) m_Manager)->GetScore());
	m_ScoreLabel->SetText(scoreBuffer);
}