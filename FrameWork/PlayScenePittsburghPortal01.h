#pragma once
#include "PlaySceneWithLight.h"

class PlayScenePittsburghPortal01 : public PlaySceneWithLight
{
public:
	PlayScenePittsburghPortal01();
	~PlayScenePittsburghPortal01();
	void Update(double dt) override;
	void ResetPlayerPosition() override;
private:
	//Đường dẫn.
	const char * pbPortal01LightPNG = (char*)".\\..\\Resources\\Images\\Maps\\PittsburghPortal01\\pittsburgh_portal01_light.png";
	const char * pbPortal01LightTXT = (char*)".\\..\\Resources\\Images\\Maps\\PittsburghPortal01\\pittsburgh_portal01_light.txt";
	const char * pbPortal01DarkPNG = (char*)".\\..\\Resources\\Images\\Maps\\PittsburghPortal01\\pittsburgh_portal01_dark.png";
	const char * pbPortal01DarkTXT = (char*)".\\..\\Resources\\Images\\Maps\\PittsburghPortal01\\pittsburgh_portal01_dark.txt";
	const char * pbPortal01MapObject = (char*)".\\..\\Resources\\Images\\Maps\\PittsburghPortal01\\pittsburgh_portal01_map_object.txt";
};