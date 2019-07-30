#pragma once
#include<dsound.h>
#include"dsutil.h"
#include<unordered_map>
#include"Global.h"


class SoundManager {
private:
	std::unordered_map<int, CSound *> sounds;
	static SoundManager* instance;
	static CSoundManager* manager;
public:
	static SoundManager* getinstance();
	void Create(HWND hwnd);
	void loadResources();
	void play(int index);
};