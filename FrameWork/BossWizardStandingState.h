#pragma once
#include"BossWizardState.h"
#include"BossWizard.h"
class BossWizardStandingState :public BossWizardState {
public:
	void Update(float dt) override;
	void InputHandler() override;
	BossWizardStandingState();
	~BossWizardStandingState();
};