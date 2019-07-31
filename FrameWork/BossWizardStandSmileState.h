#pragma once
#include"BossWizardState.h"
#include"BossWizard.h"
class BossWizardStandSmileState :public BossWizardState {
public:
	void Update(float dt) override;
	void InputHandler() override;
	BossWizardStandSmileState();
	~BossWizardStandSmileState();
};