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
	manager->Create(&sounds[Map], (char*)".\\..\\Resources\\Sounds\\Map.wav");
	manager->Create(&sounds[Boss1], (char*)".\\..\\Resources\\Sounds\\Boss1.wav");
	manager->Create(&sounds[Boss2], (char*)".\\..\\Resources\\Sounds\\Boss2.wav");
}

void SoundManager::play(SoundName soundName, bool loop)
{
	if (loop)
	{
		sounds[soundName]->Play(0, 0, DSBPLAY_LOOPING);
	}
	else
	{
		sounds[soundName]->Stop();
		sounds[soundName]->Reset();
		sounds[soundName]->Play(0, 0, 0);
	}
}
void SoundManager::stop(SoundName soundName)
{
	sounds[soundName]->Stop();
}

void SoundManager::stopAll()
{
	for (auto sound : sounds)
	{
		sound.second->Stop();
	}
}

void SoundManager::ReleaseAll()
{
	for (auto sound : sounds)
	{
		sound.second->~CSound();
	}
	sounds.clear();
}

