#pragma once
#include"Global.h"
#include"Collision.h"
#include"Object.h"
#include"SceneManager.h"
class BossWizardState {
public:
	State stateName;
	BossWizardState() {};
	virtual void InputHandler() {};
	virtual void Update(float dt) {};
};