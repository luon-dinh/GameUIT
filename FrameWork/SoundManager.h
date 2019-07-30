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
		stage1,
		stage2,
		stage3,
		stage4,
		playerattack,
		playerdie,
		itemfall,
		enemydie,
	};
	std::unordered_map<SoundName, CSound *> sounds;
	static SoundManager* getinstance();
	void Create(HWND hwnd);
	void loadResources();
	void play(SoundName soundName, bool loop);
};