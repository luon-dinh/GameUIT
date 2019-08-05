#pragma once
#include<dsound.h>
#include"dsutil.h"
#include<unordered_map>
#include"Global.h"


class SoundManager {
private:
	
	static SoundManager* instance;
	static CSoundManager* manager;
public:
	enum SoundName {
		action_theme,
		boss_gragas_theme,
		boss_wizard_theme,
		door_open,
		object_explode,
		item_exit_orb,
		item_holder,
		item_hp,
		item_normal,
		main_theme,
		player_dash,
		player_dead,
		player_diving,
		player_punch_kick,
		player_rolling,
		player_stand,//va cham
		shield_attack, 
		shield_collision,
		wizard_fire,// đạn thường
		wizard_flying,
		wizard_lazer// đạn special
	};
	std::unordered_map<SoundName, CSound *> sounds;

	static SoundManager* getinstance();
	void Create(HWND hwnd);
	void loadResources();
	void play(SoundName soundName, bool loop=false);
	void stop(SoundName soundName);
	bool isPlaying(SoundName soundName);
	void stopAll();
	void ReleaseAll();
};