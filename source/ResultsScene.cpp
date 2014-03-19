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

	// Create the score text
	scoreText = new CLabel();
	scoreText->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	scoreText->m_Y = (float)IwGxGetScreenHeight() * 0.65f;
	scoreText->SetFont(g_pResources->getFont());
	scoreText->m_AnchorX = 0.5;
	scoreText->m_AnchorY = 0.5;
	scoreText->m_Color = CColor(0,0,0,255);
	AddChild(scoreText);

	// Create the title text
	tapToContinue = new CLabel();
	tapToContinue->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	tapToContinue->m_Y = (float)IwGxGetScreenHeight() * 0.8f;
	tapToContinue->SetFont(g_pResources->getFont());
	tapToContinue->m_AnchorX = 0.5;
	tapToContinue->m_AnchorY = 0.5;
	tapToContinue->m_Color = CColor(0,0,0,255);
	tapToContinue->SetText("TAP TO CONTINUE");
	tapToContinue->m_IsVisible = false;
	AddChild(tapToContinue);

	AddButtons();
}

void ResultsScene::Update(float deltaTime, float alphaMul)
{
	//if not current scene, don't bother updating.
	if(!(m_Manager->GetCurrent() == this))
	{
		return;
	}
	char scoreBuffer[20];
	sprintf(scoreBuffer, "%i", ((GameSceneManager*) m_Manager)->GetScore());
	scoreText->SetText(scoreBuffer);

	Scene::Update(deltaTime, alphaMul);
	
	if(delay <= 0)
	{
		tapToContinue->m_IsVisible = true;
		if(m_IsInputActive && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
		{
			g_pInput->Reset();
			TitleScene * titleScene = (TitleScene *) m_Manager->Find("TitleState");
			Audio::StopMusic();
			m_Manager->SwitchTo(titleScene);
			tapToContinue->m_IsVisible = false;
			
		}
	}
	else
	{
		g_pInput->Reset();
		delay -= deltaTime;
	}
	

	
}

void ResultsScene::Reset()
{
	delay = 2.0f;
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

void ResultsScene::Render()
{
	Scene::Render();
}

void ResultsScene::AddButtons()
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

