#include "SettingsMenu.h"

#define BUTTON_X_OFFSET 70.0f
#define BUTTON_Y_OFFSET 90.0f
#define BUTTON_SPACING 65.0f
#define BUTTON_SIZE 60.0f

SettingsMenu::SettingsMenu(float xGraphicsScale, float yGraphicsScale)
	:m_XGraphicsScale(xGraphicsScale), m_YGraphicsScale(yGraphicsScale)
{
	InitButtons();
}


SettingsMenu::~SettingsMenu(void)
{
}

void SettingsMenu::InitButtons()
{
	m_PlayButton = new CSprite();
	m_PlayButton->m_X = BUTTON_X_OFFSET;
	m_PlayButton->m_Y = BUTTON_Y_OFFSET;
	m_PlayButton->SetImage(g_pResources->GetPlayButton());
	m_PlayButton->m_H = m_PlayButton->GetImage()->GetHeight();
	m_PlayButton->m_W = m_PlayButton->GetImage()->GetWidth();
	//m_PlayButton->m_ScaleX = m_XGraphicsScale;
	//m_PlayButton->m_ScaleY = m_YGraphicsScale;
	AddChild(m_PlayButton);

	m_MusicButton = new CSprite();
	m_MusicButton->m_X = m_PlayButton->m_X;
	m_MusicButton->m_Y = m_PlayButton->m_Y + BUTTON_SPACING;
	m_MusicButton->SetImage(g_pResources->GetMusicButton());
	m_MusicButton->m_H = m_MusicButton->GetImage()->GetHeight();
	m_MusicButton->m_W = m_MusicButton->GetImage()->GetWidth();
	//m_MusicButton->m_ScaleX = m_XGraphicsScale;
	//m_MusicButton->m_ScaleY = m_YGraphicsScale;
	AddChild(m_MusicButton);

	m_MuteMusicButton = new CSprite();
	m_MuteMusicButton->m_X = m_MusicButton->m_X;
	m_MuteMusicButton->m_Y = m_MusicButton->m_Y;
	m_MuteMusicButton->SetImage(g_pResources->GetMuteMusicButton());
	m_MuteMusicButton->m_H = m_MuteMusicButton->GetImage()->GetHeight();
	m_MuteMusicButton->m_W = m_MuteMusicButton->GetImage()->GetWidth();
	//m_MuteMusicButton->m_ScaleX = m_XGraphicsScale;
	//m_MuteMusicButton->m_ScaleY = m_YGraphicsScale;
	m_MuteMusicButton->m_IsVisible = false;
	AddChild(m_MuteMusicButton);

	m_SoundButton = new CSprite();
	m_SoundButton->m_X = m_PlayButton->m_X;
	m_SoundButton->m_Y = m_MusicButton->m_Y + BUTTON_SPACING;
	m_SoundButton->SetImage(g_pResources->GetSoundButton());
	m_SoundButton->m_H = m_SoundButton->GetImage()->GetHeight();
	m_SoundButton->m_W = m_SoundButton->GetImage()->GetWidth();
	//m_SoundButton->m_ScaleX = m_XGraphicsScale;
	//m_SoundButton->m_ScaleY = m_YGraphicsScale;
	AddChild(m_SoundButton);

	m_MuteSoundButton = new CSprite();
	m_MuteSoundButton->m_X = m_SoundButton->m_X;
	m_MuteSoundButton->m_Y = m_SoundButton->m_Y;
	m_MuteSoundButton->SetImage(g_pResources->GetMuteSoundButton());
	m_MuteSoundButton->m_H = m_MuteSoundButton->GetImage()->GetHeight();
	m_MuteSoundButton->m_W = m_MuteSoundButton->GetImage()->GetWidth();
	//m_MuteSoundButton->m_ScaleX = m_XGraphicsScale;
	//m_MuteSoundButton->m_ScaleY = m_YGraphicsScale;
	m_MuteSoundButton->m_IsVisible = false;
	AddChild(m_MuteSoundButton);

	m_ExitButton = new CSprite();
	m_ExitButton->m_X = m_PlayButton->m_X;
	m_ExitButton->m_Y = m_SoundButton->m_Y + BUTTON_SPACING;
	m_ExitButton->SetImage(g_pResources->GetExitButton());
	m_ExitButton->m_H = m_ExitButton->GetImage()->GetHeight();
	m_ExitButton->m_W = m_ExitButton->GetImage()->GetWidth();
	//m_ExitButton->m_ScaleX = m_XGraphicsScale;
	//m_ExitButton->m_ScaleY = m_YGraphicsScale;
	AddChild(m_ExitButton);
}

CSprite* SettingsMenu::GetPlayButton()
{
	return m_PlayButton;
}
CSprite* SettingsMenu::GetMusicButton()
{
	return m_MusicButton;
}

CSprite* SettingsMenu::GetMuteMusicButton()
{
	return m_MuteMusicButton;
}

CSprite* SettingsMenu::GetSoundButton()
{
	return m_SoundButton;
}

CSprite* SettingsMenu::GetMuteSoundButton()
{
	return m_MuteSoundButton;
}

CSprite* SettingsMenu::GetExitButton()
{
	return m_ExitButton;
}

void SettingsMenu::ToggleMusic()
{
	if(m_MusicButton->m_IsVisible)
	{
		m_MusicButton->m_IsVisible = false;
		m_MuteMusicButton->m_IsVisible = true;
		Audio::MuteMusic();
	}
	//Else the mute music button is showing, so show the music button and turn on the music
	else
	{
		m_MusicButton->m_IsVisible = true;
		m_MuteMusicButton->m_IsVisible = false;
		Audio::UnmuteMusic();
	}
}

void SettingsMenu::ToggleSound()
{
	//If the sound button is showing, then show the mute sound button and turn off the sound 
	if(m_SoundButton->m_IsVisible)
	{
		m_SoundButton->m_IsVisible = false;
		m_MuteSoundButton->m_IsVisible = true;
		Audio::MuteSound();
	}
	//Else the mute sound button is showing, so show the sound button and turn on the sound
	else
	{
		m_SoundButton->m_IsVisible = true;
		m_MuteSoundButton->m_IsVisible = false;
		Audio::UnmuteSound();
	}
}