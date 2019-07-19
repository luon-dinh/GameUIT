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

};