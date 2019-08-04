#pragma once
#include"BossWizardState.h"
#include"BossWizard.h"
class BossWizardPunchingState :public BossWizardState {
public:
	float timePunch;
	const float maxTimeToPunch = 1000;
	void Update(float dt) override;
	void InputHandler() override;
	BossWizardPunchingState();
	~BossWizardPunchingState();
};