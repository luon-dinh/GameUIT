#pragma once
#include "PlaySceneWithLight.h"

class PlayScenePittsburgh : PlaySceneWithLight
{
public:
	PlayScenePittsburgh();
	~PlayScenePittsburgh();
private:
	const char * world02LightTXT = (char*)".\\..\\Resources\\Images\\Maps\\CharlesBoss\\charles_boss_light.txt";
	const char * world02TileLightPNG = (char*)".\\..\\Resources\\Images\\Maps\\CharlesBoss\\charles_boss_light.png";
	const char * world02DarkTXT = (char*)".\\..\\Resources\\Images\\Maps\\CharlesBoss\\charles_boss_dark.txt";
	const char * world02TileDarkPNG = (char*)".\\..\\Resources\\Images\\Maps\\CharlesBoss\\charles_boss_dark.png";
	const char * world02MapObject = (char*)".\\..\\Resources\\Images\\Maps\\CharlesBoss\\charles_boss_map_object.txt";
};