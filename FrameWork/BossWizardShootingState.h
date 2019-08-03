#pragma once
#include"BossWizardState.h"
#include"BossWizard.h"
class BossWizardShootingState :public BossWizardState {
public:
	const float maxTimeShoot=500;
	float timeShoot;
	void Update(float dt) override;
	void InputHandler() override;
	BossWizardShootingState();
	~BossWizardShootingState();
};