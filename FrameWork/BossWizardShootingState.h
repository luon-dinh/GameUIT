#pragma once
#include"BossWizardState.h"
#include"BossWizard.h"
class BossWizardShootingState :public BossWizardState {
public:
	const float maxTimeShoot=500;
	const float shoot1 = 30;// deltay so với player để set hướng đạn bay
	const float shoot2 = 80;
	float timeShoot;
	void Update(float dt) override;
	void InputHandler() override;
	BossWizardShootingState();
	~BossWizardShootingState();
};