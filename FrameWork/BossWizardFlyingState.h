#pragma once
#include"BossWizardState.h"
#include"BossWizard.h"
class BossWizardFlyingState :public BossWizardState {
public:
	float maxX=250;
	float maxY=100;
	void Update(float dt) override;
	void Fly(int flyMode);
	void InputHandler() override;
	BossWizardFlyingState();
	~BossWizardFlyingState();
};