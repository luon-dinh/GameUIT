#pragma once
#include "PlaySceneWithLight.h"

class PlayScenePittsburghPortal02 : public PlaySceneWithLight
{
public:
	PlayScenePittsburghPortal02();
	~PlayScenePittsburghPortal02();
	void Update(double dt) override;
	void ResetPlayerPosition() override;
	void GoToNextScene() override;
private:
	const char * pbPortal02LightPNG = (char*)".\\..\\Resources\\Images\\Maps\\PittsburghPortal02\\pittsburgh_portal02_light.png";
	const char * pbPortal02LightTXT = (char*)".\\..\\Resources\\Images\\Maps\\PittsburghPortal02\\pittsburgh_portal02_light.txt";
	const char * pbPortal02DarkPNG = (char*)".\\..\\Resources\\Images\\Maps\\PittsburghPortal02\\pittsburgh_portal02_dark.png";
	const char * pbPortal02DarkTXT = (char*)".\\..\\Resources\\Images\\Maps\\PittsburghPortal02\\pittsburgh_portal02_dark.txt";
	const char * pbPortal02MapObject = (char*)".\\..\\Resources\\Images\\Maps\\PittsburghPortal02\\pittsburgh_portal02_map_object.txt";
	const char * pbPortal02Spawn = (char*)".\\..\\Resources\\Images\\Maps\\PittsburghPortal02\\pittsburgh_portal_02_spawn.txt";
};