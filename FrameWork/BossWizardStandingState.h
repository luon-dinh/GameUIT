#pragma once
#include"BossWizardState.h"
#include"BossWizard.h"
class BossWizardStandingState :public BossWizardState {
public:
	float timeStand;
	const float maxTimeStand = 500;
	void Update(float dt) override;
	void InputHandler() override;
	BossWizardStandingState();
	~BossWizardStandingState();
};