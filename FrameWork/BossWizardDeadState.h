#pragma once
#include"BossWizardState.h"
#include"BossWizard.h"
class BossWizardDeadState :public BossWizardState {
public:
	float timeDead;
	const float maxTimeDead = 3000;
	void Update(float dt) override;
	void InputHandler() override;
	BossWizardDeadState();
	~BossWizardDeadState();
};