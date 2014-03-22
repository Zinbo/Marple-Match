#pragma once
#include "Iw2DSceneGraph.h"
#include "resources.h"
#include "audio.h"

using namespace Iw2DSceneGraph;

class SettingsMenu : public CSprite
{
public:
	SettingsMenu(float xGraphicsScale, float yGraphicsScale);
	~SettingsMenu(void);
	void ToggleMusic();
	void ToggleSound();
	CSprite* GetPlayButton();
	CSprite* GetMusicButton();
	CSprite* GetMuteMusicButton();
	CSprite* GetSoundButton();
	CSprite* GetMuteSoundButton();
	CSprite* GetExitButton();

private:
	CSprite* m_ExitButton;
	CSprite* m_PlayButton;
	CSprite* m_MusicButton;
	CSprite* m_MuteMusicButton;
	CSprite* m_SoundButton;
	CSprite* m_MuteSoundButton;

	float m_XGraphicsScale;
	float m_YGraphicsScale;

	void InitButtons();
};

