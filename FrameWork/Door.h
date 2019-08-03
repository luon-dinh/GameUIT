#pragma once
#include "Object.h"

class Door : public Object
{
	const int openDoorAnimDelay = 250;
	Animation * doorDarkAnim;
	Animation * doorLightAnim;
	Animation * currentAnim;
public:
	Door(int posX, int posY);
	~Door();
	void Update(float dt) override;
	void Render() override;
	void LoadAllAnim();
	BoundingBox getBoundingBox() override;
private:
	void SetAnimOnLightStatus();
};