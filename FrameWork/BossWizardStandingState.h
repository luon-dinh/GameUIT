#pragma once
#include"BossWizardState.h"
#include"BossWizard.h"
class BossWizardStandingState :public BossWizardState {
public:
	float timeStand;
	const float maxTimeStand = 300;
	void Update(float dt) override;
	void InputHandler() override;
	BossWizardStandingState();
	~BossWizardStandingState();
};