#include "InstructionsScene.h"

using namespace SFAS2014;

const float InstructionsScene::kMainMenuButtonX = 124.0f;
const float InstructionsScene::kMainMenuButtonY = 418.0f;
const float InstructionsScene::kMainMenuButtonYScale = 60.0f;

InstructionsScene::InstructionsScene(float xGraphicsScale, float yGraphicsScale)
{
	m_XGraphicsScale = xGraphicsScale;
	m_YGraphicsScale = yGraphicsScale;
}


InstructionsScene::~InstructionsScene(void)
{
}

void InstructionsScene::Init()
{
	Scene::Init();
	
	InitUI();
	InitButtons();
}

void InstructionsScene::Update(float deltaTime, float alphaMul)
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
		if(m_MainMenuButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			TitleScene * titleScene = (TitleScene *) m_Manager->Find("TitleState");
			SwitchScene(titleScene);
		}
		g_pInput->Reset();
	}


	
}

void InstructionsScene::Reset()
{
	Audio::PlayMusic(g_pResources->GetMenuMusicFilename(), true);
}

void InstructionsScene::Render()
{
	Scene::Render();
}

void InstructionsScene::InitUI()
{
	m_Background = new CSprite();
	m_Background->SetImage(g_pResources->GetInstructionsBackground());
	m_Background->m_W = m_Background->GetImage()->GetWidth();
	m_Background->m_H = m_Background->GetImage()->GetHeight();
	//Fit background to screen size
	m_Background->m_ScaleX = (float)IwGxGetScreenWidth() / m_Background->m_W;
	m_Background->m_ScaleY = (float)IwGxGetScreenHeight() / m_Background->m_H;
	AddChild(m_Background);
}

void InstructionsScene::InitButtons()
{
	m_MainMenuButton = new CSprite();
	m_MainMenuButton->m_X = kMainMenuButtonX * m_XGraphicsScale;
	m_MainMenuButton->m_Y = kMainMenuButtonY * m_YGraphicsScale;
	m_MainMenuButton->SetImage(g_pResources->GetMainMenuButton());
	m_MainMenuButton->m_H = m_MainMenuButton->GetImage()->GetHeight();
	m_MainMenuButton->m_W = m_MainMenuButton->GetImage()->GetWidth();
	float buttonScale = kMainMenuButtonYScale / m_MainMenuButton->m_H; 
	m_MainMenuButton->m_ScaleX = buttonScale*m_XGraphicsScale;
	m_MainMenuButton->m_ScaleY = buttonScale*m_YGraphicsScale;
	AddChild(m_MainMenuButton);
}

void InstructionsScene::CleanUp()
{
	Audio::StopMusic();
}

void InstructionsScene::SwitchScene(Scene * scene)
{
	CleanUp();
	m_Manager->SwitchTo(scene);
}

