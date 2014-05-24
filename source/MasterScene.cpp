#include "MasterScene.h"
#include "input.h"

MasterScene::MasterScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * settingsMenu)
{
	m_XGraphicsScale = xGraphicsScale;
	m_YGraphicsScale = yGraphicsScale;
	m_SettingsMenu = settingsMenu;
}


MasterScene::~MasterScene(void)
{
}

void MasterScene::ToggleButtons()
{
	if(m_SettingsMenu->GetPlayButton()->HitTest(g_pInput->m_X, g_pInput->m_Y))
	{
		g_pInput->Reset();
		ToggleSettingsMenu();
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
		g_pInput->Reset();
		ToggleSettingsMenu();
		ExitScene();
	}
}

void MasterScene::ToggleSettingsMenu()
{
	if(m_SettingsMenu->m_IsVisible)
	{
		m_SettingsMenu->m_IsVisible = false;
		ResumeGame();
	}
	else
	{
		m_SettingsMenu->m_IsVisible = true;
		PauseGame();
	}
}

void MasterScene::Reset()
{
	Scene::Reset();
	Audio::PlayMusic(g_pResources->GetMenuMusicFilename(), true);
	AddChild(m_SettingsMenu);
}

bool MasterScene::SettingsMenuHitTest()
{
	//If settings menu is open and it has been clicked, then check to see if one of the buttons have been hit.
	if(m_SettingsMenu->m_IsVisible && m_SettingsMenu->HitTest(g_pInput->m_X, g_pInput->m_Y))
	{
		ToggleButtons();
		return true;
	}
	//Else if the menu is open and the button has been clicked OR the settings menu is open and elsewhere on the screen has been clicked then toggle the menu
	else if(m_SettingsButton->HitTest(g_pInput->m_X, g_pInput->m_Y) || m_SettingsMenu->m_IsVisible)
	{
		ToggleSettingsMenu();
		return true;
	}
	return false;
}

void MasterScene::CleanUp()
{
	Audio::StopMusic();
}

void MasterScene::SwitchScene(Scene* scene)
{
	CleanUp();
	m_Manager->SwitchTo(scene);
}

void MasterScene::Init()
{
	Scene::Init();
	
	//Initialise background
	InitUI();

	//Initialise buttons for controlling sound and music
	InitButtons();
}