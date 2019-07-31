#pragma once
#include"BossWizardState.h"
#include"BossWizard.h"
class BossWizardFlyingState :public BossWizardState {
public:
	const float mapWidth = 250;
	const float mapHeight = 220;
	const float maxFly1 = 50;
	void Update(float dt) override;
	void Fly(int flyMode);
	void InputHandler() override;
	BossWizardFlyingState();
	~BossWizardFlyingState();
};