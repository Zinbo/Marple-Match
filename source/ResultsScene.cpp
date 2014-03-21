/*
 * (C) 2014 Search for a Star
 * 
 */

#include "ResultsScene.h"
#include "IwGx.h"
#include "resources.h"
#include "TitleScene.h"

#define BUTTON_SPACING 25.0f
#define BUTTON_X_OFFSET 30.0f
#define BUTTON_STARTING_X 1.0f
#define BUTTON_STARTING_Y 1.0f

using namespace SFAS2014;

//
//
// ResultsScene class
//
//
ResultsScene::ResultsScene()
{

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

	//If a touch has been detected then if it's on the music button, toggle the audio and the button, if it's the sound button, toggle the sound and the button, else change to the game scene and clean up.
	if(m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		g_pInput->Reset();
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
			if(m_TapLabel->m_IsVisible)
			{
				ChangeSceneAndCleanUp();
			}
		}
	}

	m_Delay -= deltaTime;

	UpdateLabels();
}

void ResultsScene::ToggleMusic()
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

void ResultsScene::ToggleSound()
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
void ResultsScene::ChangeSceneAndCleanUp()
{
	TitleScene * titleScene = (TitleScene *) m_Manager->Find("TitleState");
	Audio::StopMusic();
	m_Manager->SwitchTo(titleScene);
	m_TapLabel->m_IsVisible = false;
}

void ResultsScene::Reset()
{
	m_Delay = 2.0f;
	Audio::PlayMusic(g_pResources->GetMenuMusicFilename(), true);
	//If the sound and music has been turned off in another scene then set the buttons on this scene to reflect this.
	SetSoundAndMusicButtons();
}

void ResultsScene::SetSoundAndMusicButtons()
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

void ResultsScene::Render()
{
	Scene::Render();
}

void ResultsScene::InitButtons()
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
	m_SoundButton->m_X = m_MusicButton->m_X - (BUTTON_X_OFFSET*m_XGraphicsScale);
	m_SoundButton->m_Y = m_MusicButton->m_Y;
	m_SoundButton->SetImage(g_pResources->GetSoundButton());
	m_SoundButton->m_H = m_SoundButton->GetImage()->GetHeight();
	m_SoundButton->m_W = m_SoundButton->GetImage()->GetWidth();
	m_SoundButton->m_ScaleX = buttonXScale;
	m_SoundButton->m_ScaleY = buttonYScale;
	AddChild(m_SoundButton);

	m_MuteSoundButton = new CSprite();
	m_MuteSoundButton->m_X = m_SoundButton->m_X;
	m_MuteSoundButton->m_Y = m_MusicButton->m_Y;
	m_MuteSoundButton->SetImage(g_pResources->GetMuteSoundButton());
	m_MuteSoundButton->m_H = m_MuteSoundButton->GetImage()->GetHeight();
	m_MuteSoundButton->m_W = m_MuteSoundButton->GetImage()->GetWidth();
	m_MuteSoundButton->m_ScaleX = buttonXScale;
	m_MuteSoundButton->m_ScaleY = buttonYScale;
	m_MuteSoundButton->m_IsVisible = false;
	AddChild(m_MuteSoundButton);
	
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