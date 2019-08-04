#pragma once
#include "PlayScene.h"

class PlayScenePittsburghBoss : public PlayScene
{
public:
	PlayScenePittsburghBoss();
	~PlayScenePittsburghBoss();
	void GoToNextScene() override;
	void Update(double dt) override;
	void ResetPlayerPosition() override;
private:
	//Constant dùng để lưu địa chỉ đến các file.
	const char * pittsburghBossPNG = (char*)".\\..\\Resources\\Images\\Maps\\PittsburghBoss\\CaroDown.png";
	const char * pittsburghBossTXT = (char*)".\\..\\Resources\\Images\\Maps\\PittsburghBoss\\pittsburgh_boss_map.txt";
	const char * pittsburghBossSpawn = (char*)".\\..\\Resources\\Images\\Maps\\PittsburghBoss\\pittsburgh_boss_spawn.txt";
	const char * pittsburghBossMapObject = (char*)".\\..\\Resources\\Images\\Maps\\PittsburghBoss\\pittsburgh_boss_map_object.txt";
};