#pragma once
#include"BossWizardState.h"
#include"BossWizard.h"
class BossWizardBeatenState :public BossWizardState {
public:
	void Update(float dt) override;
	void InputHandler() override;
	BossWizardBeatenState();
	~BossWizardBeatenState();
};