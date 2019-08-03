#pragma once
#include"BossWizardState.h"
#include"BossWizard.h"
#include"Equation.h"
class BossWizardFlyingState :public BossWizardState {
public:
	Equation* parapol;
	const float mapWidth = 250;
	const float mapHeight = 230;
	const float maxFly1 = 40;
	void Update(float dt) override;
	void Fly(float dt);
	void InputHandler() override;
	BossWizardFlyingState();
	~BossWizardFlyingState();
};