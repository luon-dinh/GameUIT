#pragma once
#include "PlaySceneWithLight.h"
#include "GameMap.h"
#include "Camera.h"
#include "Player.h"

class PlaySceneCharlesBoss : public PlaySceneWithLight
{
public:
	PlaySceneCharlesBoss();
	~PlaySceneCharlesBoss();
	void Update(double dt);
	void ResetPlayerPosition() override;
private:
	const char * world01BossMapLight = (char*)".\\..\\Resources\\Images\\Maps\\CharlesBoss\\charles_boss_light.txt";
	const char * world01BossTileLight = (char*)".\\..\\Resources\\Images\\Maps\\CharlesBoss\\charles_boss_light.png";
	const char * world01BossMapDark = (char*)".\\..\\Resources\\Images\\Maps\\CharlesBoss\\charles_boss_dark.txt";
	const char * world01BossTileDark = (char*)".\\..\\Resources\\Images\\Maps\\CharlesBoss\\charles_boss_dark.png";
	const char * world01BossMapObject = (char*)".\\..\\Resources\\Images\\Maps\\CharlesBoss\\charles_boss_map_object.txt";
};