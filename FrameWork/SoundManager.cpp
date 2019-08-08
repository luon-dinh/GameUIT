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
	manager->Create(&sounds[action_theme], (char*)".\\..\\Resources\\Sounds\\action_theme.wav");
	manager->Create(&sounds[boss_gragas_theme], (char*)".\\..\\Resources\\Sounds\\boss_gragas_theme.wav");
	manager->Create(&sounds[boss_wizard_theme], (char*)".\\..\\Resources\\Sounds\\boss_wizard_theme.wav");
	manager->Create(&sounds[door_open], (char*)".\\..\\Resources\\Sounds\\door_open.wav");
	manager->Create(&sounds[item_exit_orb], (char*)".\\..\\Resources\\Sounds\\item_exit_orb.wav");
	manager->Create(&sounds[item_holder], (char*)".\\..\\Resources\\Sounds\\item_holder.wav");
	manager->Create(&sounds[item_hp], (char*)".\\..\\Resources\\Sounds\\item_hp.wav");
	manager->Create(&sounds[item_normal], (char*)".\\..\\Resources\\Sounds\\item_normal.wav");
	manager->Create(&sounds[main_theme], (char*)".\\..\\Resources\\Sounds\\main_theme.wav");
	manager->Create(&sounds[object_explode], (char*)".\\..\\Resources\\Sounds\\object_explode.wav");
	manager->Create(&sounds[player_dash], (char*)".\\..\\Resources\\Sounds\\player_dash.wav");
	manager->Create(&sounds[player_dead], (char*)".\\..\\Resources\\Sounds\\player_dead.wav");
	manager->Create(&sounds[player_diving], (char*)".\\..\\Resources\\Sounds\\player_diving.wav");
	manager->Create(&sounds[player_punch_kick], (char*)".\\..\\Resources\\Sounds\\player_punch_kick.wav");
	manager->Create(&sounds[player_rolling], (char*)".\\..\\Resources\\Sounds\\player_rolling.wav");
	manager->Create(&sounds[player_stand], (char*)".\\..\\Resources\\Sounds\\player_stand.wav");
	manager->Create(&sounds[shield_attack], (char*)".\\..\\Resources\\Sounds\\shield_attack.wav");
	manager->Create(&sounds[shield_collision], (char*)".\\..\\Resources\\Sounds\\shield_collision.wav");
	manager->Create(&sounds[wizard_fire], (char*)".\\..\\Resources\\Sounds\\wizard_fire.wav");
	manager->Create(&sounds[wizard_flying], (char*)".\\..\\Resources\\Sounds\\wizard_flying.wav");
	manager->Create(&sounds[wizard_lazer], (char*)".\\..\\Resources\\Sounds\\wizard_laze.wav");
	manager->Create(&sounds[enemy_attack], (char*)".\\..\\Resources\\Sounds\\enemy_attack.wav");
}

void SoundManager::play(SoundName soundName, bool loop)
{
	if (loop)
	{
		//sounds[soundName]->Play(0,0,0, DSBPLAY_LOOPING);
		sounds[soundName]->Play(0,DSBPLAY_LOOPING);
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
	std::unordered_map<SoundName, CSound *>::iterator it;
	for (it=sounds.begin();it!=sounds.end();++it)
	{
		if(it->second->IsSoundPlaying())
			it->second->Stop();
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

bool SoundManager::isPlaying(SoundName soundName)
{
	return sounds[soundName]->IsSoundPlaying();
}

std::vector<SoundManager::SoundName> SoundManager::getAllPlayingSound()
{
	std::vector<SoundManager::SoundName> listOfPlayingSound;
	for (auto it = sounds.begin(); it != sounds.end(); ++it)
	{
		if (isPlaying(it->first))
			listOfPlayingSound.push_back((it->first));
	}
	return listOfPlayingSound;
}

void SoundManager::playMultipleSound(std::vector<SoundName> soundNameList)
{
	for (auto soundName : soundNameList)
	{
		play(soundName);
	}
}

void SoundManager::pauseAllSound()
{
	stopAll();
	pausedSound.clear();
	pausedSound = getAllPlayingSound();
}

void SoundManager::resumeAllSound()
{
	playMultipleSound(pausedSound);
}