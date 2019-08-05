#pragma once
#include "PlaySceneWithLight.h"

class PlayScenePittsburgh : public PlaySceneWithLight
{
public:
	PlayScenePittsburgh();
	~PlayScenePittsburgh();
	void GoToNextScene() override;
	void Update(double dt) override; 
	void ResetPlayerPosition() override;
private:
	const char * world02LightTXT = (char*)".\\..\\Resources\\Images\\Maps\\Pittsburgh\\pittsburgh_light.txt";
	const char * world02TileLightPNG = (char*)".\\..\\Resources\\Images\\Maps\\Pittsburgh\\pittsburgh_light.png";
	const char * world02DarkTXT = (char*)".\\..\\Resources\\Images\\Maps\\Pittsburgh\\pittsburgh_dark.txt";
	const char * world02TileDarkPNG = (char*)".\\..\\Resources\\Images\\Maps\\Pittsburgh\\pittsburgh_dark.png";
	const char * world02MapObject = (char*)".\\..\\Resources\\Images\\Maps\\Pittsburgh\\pittsburgh_map_object.txt";
	const char * world02Spawn = (char*)".\\..\\Resources\\Images\\Maps\\Pittsburgh\\pittsburgh_map_spawn.txt";

	const int blueSoldierKillReq = 3;
	const int redRocketKillReq = 3;

	bool isCameraAlreadyLockedOnce = false;

	bool isAddSoldier = false;
};