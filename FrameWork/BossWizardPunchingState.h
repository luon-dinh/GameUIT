#pragma once
#include"BossWizardState.h"
#include"BossWizard.h"
class BossWizardPunchingState :public BossWizardState {
public:
	void Update(float dt) override;
	void InputHandler() override;
	BossWizardPunchingState();
	~BossWizardPunchingState();
};