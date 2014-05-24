#if !defined(__MASTERSCENE_H__)
#define __MASTERSCENE_H__

#include "scene.h"
class MasterScene : public Scene
{
public:
	MasterScene(float xGraphicsScale, float yGraphicsScale, SettingsMenu * SettingsMenu);
	~MasterScene(void);
protected:
	//Sprites for background
	CSprite* m_Background;
	CSprite* m_SettingsButton;

	//Init methods
	void Init();
	virtual void InitUI() = 0;
	virtual void InitButtons() = 0;

	//Methods for toggling
	void ToggleButtons();
	void ToggleSettingsMenu();
	bool SettingsMenuHitTest();
	
	//Methods for cleaning up
	void Reset();
	void CleanUp();
	void SwitchScene(Scene *scene);
	virtual void ExitScene() = 0;
	
	//Methods for game control
	virtual void ResumeGame() = 0;
	virtual void PauseGame() = 0;
};

#endif  // __MASTERSCENE_H__