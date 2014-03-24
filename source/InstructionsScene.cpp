#include "InstructionsScene.h"

#define MAIN_MENU_BUTTON_X 124.0f
#define MAIN_MENU_BUTTON_Y 418.0f
#define MAIN_MENU_BUTTON_Y_SCALE 60.0f

using namespace SFAS2014;

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
	m_Background->SetImage(g_pResources->getInstructionsBackground());
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
	m_MainMenuButton->m_X = MAIN_MENU_BUTTON_X * m_XGraphicsScale;
	m_MainMenuButton->m_Y = MAIN_MENU_BUTTON_Y * m_YGraphicsScale;
	m_MainMenuButton->SetImage(g_pResources->GetMainMenuButton());
	m_MainMenuButton->m_H = m_MainMenuButton->GetImage()->GetHeight();
	m_MainMenuButton->m_W = m_MainMenuButton->GetImage()->GetWidth();
	float buttonScale = MAIN_MENU_BUTTON_Y_SCALE / m_MainMenuButton->m_H; 
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

