#pragma once
#include"BossWizardState.h"
#include"BossWizard.h"
class BossWizardRunningState :public BossWizardState {
public:
	const float runningSpeed = 2.5;
	const float maxX = 45;
	void Update(float dt) override;
	void InputHandler() override;
	BossWizardRunningState();
	~BossWizardRunningState();
};