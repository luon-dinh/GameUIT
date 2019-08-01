#pragma once
#include"BossWizardState.h"
#include"BossWizard.h"
class BossWizardShootingState :public BossWizardState {
public:
	void Update(float dt) override;
	void InputHandler() override;
	BossWizardShootingState();
	~BossWizardShootingState();
};