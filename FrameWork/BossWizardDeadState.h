#pragma once
#include"BossWizardState.h"
#include"BossWizard.h"
class BossWizardDeadState :public BossWizardState {
public:
	void Update(float dt) override;
	void InputHandler() override;
	BossWizardDeadState();
	~BossWizardDeadState();
};