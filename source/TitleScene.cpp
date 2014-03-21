/*
 * (C) 2014 Search for a Star
 * 
 */

#include "TitleScene.h"
#include "IwGx.h"
#include "resources.h"
#include "audio.h"
#define BUTTON_SPACING 25.0f
#define BUTTON_X_OFFSET 30.0f
#define BUTTON_STARTING_X 1.0f
#define BUTTON_STARTING_Y 1.0f

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
	
	//If a touch has been detected then if it's on the music button, toggle the audio and the button, if it's the sound button, toggle the sound and the button, else change to the game scene and clean up.
	if(m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		if(m_MusicButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			ToggleMusic();
		}
		else if(m_SoundButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			ToggleSound();
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
	Audio::PlayMusic(g_pResources->GetMenuMusicFilename(), true);
	//If the sound and music has been turned off in another scene then set the buttons on this scene to reflect this.
	SetSoundAndMusicButtons();
}

void TitleScene::InitButtons()
{
	m_MusicButton = new CSprite();
	m_MusicButton->m_X = ((float) IwGxGetScreenWidth() - (BUTTON_STARTING_X*m_XGraphicsScale) - (BUTTON_SPACING*m_XGraphicsScale));
	m_MusicButton->m_Y = BUTTON_STARTING_Y*m_YGraphicsScale;
	m_MusicButton->SetImage(g_pResources->GetMusicButton());
	m_MusicButton->m_H = m_MusicButton->GetImage()->GetHeight();
	m_MusicButton->m_W = m_MusicButton->GetImage()->GetWidth();
	float buttonScale = BUTTON_SPACING / m_MusicButton->m_H;
	float buttonXScale = m_XGraphicsScale * buttonScale;
	float buttonYScale = m_YGraphicsScale * buttonScale;
	m_MusicButton->m_ScaleX = buttonXScale;
	m_MusicButton->m_ScaleY = buttonYScale;
	AddChild(m_MusicButton);
	
	m_MuteMusicButton = new CSprite();
	m_MuteMusicButton->m_X = m_MusicButton->m_X;
	m_MuteMusicButton->m_Y = m_MusicButton->m_Y;
	m_MuteMusicButton->SetImage(g_pResources->GetMuteMusicButton());
	m_MuteMusicButton->m_H = m_MuteMusicButton->GetImage()->GetHeight();
	m_MuteMusicButton->m_W = m_MuteMusicButton->GetImage()->GetWidth();
	m_MuteMusicButton->m_ScaleX = buttonXScale;
	m_MuteMusicButton->m_ScaleY = buttonYScale;
	m_MuteMusicButton->m_IsVisible = false;
	AddChild(m_MuteMusicButton);

	m_SoundButton = new CSprite();
	m_SoundButton->m_X = (m_MusicButton->m_X - (BUTTON_X_OFFSET*m_XGraphicsScale));
	m_SoundButton->m_Y = m_MusicButton->m_Y;
	m_SoundButton->SetImage(g_pResources->GetSoundButton());
	m_SoundButton->m_H = m_SoundButton->GetImage()->GetHeight();
	m_SoundButton->m_W = m_SoundButton->GetImage()->GetWidth();
	m_SoundButton->m_ScaleX = buttonXScale;
	m_SoundButton->m_ScaleY = buttonYScale;
	AddChild(m_SoundButton);

	m_MuteSoundButton = new CSprite();
	m_MuteSoundButton->m_X =m_SoundButton->m_X;
	m_MuteSoundButton->m_Y = m_MusicButton->m_Y;
	m_MuteSoundButton->SetImage(g_pResources->GetMuteSoundButton());
	m_MuteSoundButton->m_H = m_MuteSoundButton->GetImage()->GetHeight();
	m_MuteSoundButton->m_W = m_MuteSoundButton->GetImage()->GetWidth();
	m_MuteSoundButton->m_ScaleX = buttonXScale;
	m_MuteSoundButton->m_ScaleY = buttonYScale;
	m_MuteSoundButton->m_IsVisible = false;
	AddChild(m_MuteSoundButton);	
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

void TitleScene::ToggleMusic()
{
	if(m_MusicButton->m_IsVisible)
	{
		m_MusicButton->m_IsVisible = false;
		m_MuteMusicButton->m_IsVisible = true;
		Audio::MuteMusic();
	}
	else
	{
		m_MusicButton->m_IsVisible = true;
		m_MuteMusicButton->m_IsVisible = false;
		Audio::UnmuteMusic();
	}
}

void TitleScene::ToggleSound()
{
	if(m_SoundButton->m_IsVisible)
	{
		g_pInput->Reset();
		m_SoundButton->m_IsVisible = false;
		m_MuteSoundButton->m_IsVisible = true;
		Audio::MuteSound();
	}
	else
	{
		m_SoundButton->m_IsVisible = true;
		m_MuteSoundButton->m_IsVisible = false;
		Audio::UnmuteSound();
	}
}
void TitleScene::ChangeSceneAndCleanUp()
{
	GameScene * gameScene = (GameScene *) m_Manager->Find("GameState");
	Audio::StopMusic();
	m_Manager->SwitchTo(gameScene);
}

void TitleScene::SetSoundAndMusicButtons()
{
	if(Audio::m_musicIsOn)
	{
		m_MusicButton->m_IsVisible = true;
		m_MuteMusicButton->m_IsVisible = false;
	}
	else
	{
		m_MusicButton->m_IsVisible = false;
		m_MuteMusicButton->m_IsVisible = true;
	}

	if(Audio::m_soundIsOn)
	{
		m_SoundButton->m_IsVisible = true;
		m_MuteSoundButton->m_IsVisible = false;
	}
	else
	{
		m_SoundButton->m_IsVisible = false;
		m_MuteSoundButton->m_IsVisible = true;
	}
}
