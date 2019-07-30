#include"SoundManager.h"

SoundManager* SoundManager::instance = NULL;
CSoundManager* SoundManager::manager = new CSoundManager();

SoundManager* SoundManager::getinstance()
{
	if (!instance)
		instance = new SoundManager();
	return instance;
}

void SoundManager::Create(HWND hwnd)
{
	manager->Initialize(hwnd, DSSCL_PRIORITY);
}

void SoundManager::loadResources()
{
	manager->Create(&sounds[1], (char*)".\\..\\Resources\\Sounds\\pong_jump_a.wav");
	manager->Create(&sounds[2], (char*)".\\..\\Resources\\Sounds\\pong_jump_b.wav");
}

void SoundManager::play(int index)
{
	sounds[index]->Play();
}

