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

	// Create background sprite
	
	mpBackground = new CSprite();
	mpBackground->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	mpBackground->m_Y = (float)IwGxGetScreenHeight() * 0.5f;
	mpBackground->SetImage(g_pResources->getTitleBackground());
	mpBackground->m_W = mpBackground->GetImage()->GetWidth();
	
	mpBackground->m_H = mpBackground->GetImage()->GetHeight();
	
	mpBackground->m_AnchorX = 0.5;
	mpBackground->m_AnchorY = 0.5;
 
	float backgroundXScale = (float)IwGxGetScreenWidth() / mpBackground->m_W;
	float backgroundYScale = (float)IwGxGetScreenHeight() / mpBackground->m_H;
	// Fit background to screen size
	mpBackground->m_ScaleX = backgroundXScale;
	mpBackground->m_ScaleY = backgroundYScale;
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

	AddButtons();
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
		if(m_MusicButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			if(m_MusicButton->m_IsVisible)
			{
				m_MusicButton->m_IsVisible = false;
				m_MuteMusicButton->m_IsVisible = true;
				Audio::PauseMusic();
			}
			else
			{
				m_MusicButton->m_IsVisible = true;
				m_MuteMusicButton->m_IsVisible = false;
				Audio::ResumeMusic();
			}
		}
		else if(m_SoundButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
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
		else
		{	
			GameScene * gameScene = (GameScene *) m_Manager->Find("GameState");
			Audio::StopMusic();
			m_Manager->SwitchTo(gameScene);
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

void TitleScene::AddButtons()
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
	m_MuteMusicButton->m_X = ((float) IwGxGetScreenWidth() - (BUTTON_STARTING_X*m_XGraphicsScale) - (BUTTON_SPACING*m_XGraphicsScale));
	m_MuteMusicButton->m_Y = BUTTON_STARTING_Y*m_YGraphicsScale;
	m_MuteMusicButton->SetImage(g_pResources->GetMuteMusicButton());
	m_MuteMusicButton->m_H = m_MuteMusicButton->GetImage()->GetHeight();
	m_MuteMusicButton->m_W = m_MuteMusicButton->GetImage()->GetWidth();
	m_MuteMusicButton->m_ScaleX = buttonXScale;
	m_MuteMusicButton->m_ScaleY = buttonYScale;
	m_MuteMusicButton->m_IsVisible = false;
	AddChild(m_MuteMusicButton);

	m_SoundButton = new CSprite();
	m_SoundButton->m_X = ((float) IwGxGetScreenWidth() - (BUTTON_STARTING_X*m_XGraphicsScale) - (BUTTON_X_OFFSET*m_XGraphicsScale) - (BUTTON_SPACING*m_XGraphicsScale));
	m_SoundButton->m_Y = BUTTON_STARTING_Y*m_YGraphicsScale;
	m_SoundButton->SetImage(g_pResources->GetSoundButton());
	m_SoundButton->m_H = m_SoundButton->GetImage()->GetHeight();
	m_SoundButton->m_W = m_SoundButton->GetImage()->GetWidth();
	m_SoundButton->m_ScaleX = buttonXScale;
	m_SoundButton->m_ScaleY = buttonYScale;
	AddChild(m_SoundButton);

	m_MuteSoundButton = new CSprite();
	m_MuteSoundButton->m_X = ((float) IwGxGetScreenWidth() - (BUTTON_STARTING_X*m_XGraphicsScale) - (BUTTON_X_OFFSET*m_XGraphicsScale) - (BUTTON_SPACING*m_XGraphicsScale));
	m_MuteSoundButton->m_Y = BUTTON_STARTING_Y*m_YGraphicsScale;
	m_MuteSoundButton->SetImage(g_pResources->GetMuteSoundButton());
	m_MuteSoundButton->m_H = m_MuteSoundButton->GetImage()->GetHeight();
	m_MuteSoundButton->m_W = m_MuteSoundButton->GetImage()->GetWidth();
	m_MuteSoundButton->m_ScaleX = buttonXScale;
	m_MuteSoundButton->m_ScaleY = buttonYScale;
	m_MuteSoundButton->m_IsVisible = false;
	AddChild(m_MuteSoundButton);
	
}