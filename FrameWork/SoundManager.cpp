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
	manager->Create(&sounds[SoundName::stage1], (char*)".\\..\\Resources\\Sounds\\Opening.wav");
	manager->Create(&sounds[SoundName::stage2], (char*)".\\..\\Resources\\Sounds\\Map_of_America.wav");
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
		sounds[soundName]->Play();
	}
}

