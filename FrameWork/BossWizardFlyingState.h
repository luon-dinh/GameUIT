#pragma once
#include"BossWizardState.h"
#include"BossWizard.h"
class BossWizardFlyingState :public BossWizardState {
public:
	const float mapWidth = 250;
	const float mapHeight = 230;
	const float maxFly1 = 40;
	const float maxFlyx2 = 120;
	void Update(float dt) override;
	void Fly(float dt);
	void InputHandler() override;
	BossWizardFlyingState();
	~BossWizardFlyingState();
};