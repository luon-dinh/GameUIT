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
		Map,
		Boss1,
		Boss2
	};
	std::unordered_map<SoundName, CSound *> sounds;
	static SoundManager* getinstance();
	void Create(HWND hwnd);
	void loadResources();
	void play(SoundName soundName, bool loop);
	void stop(SoundName soundName);
	void stopAll();
	void ReleaseAll();
};