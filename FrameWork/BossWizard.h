#pragma once
#include"Enemy.h"
#include"BossWizardRunningState.h"
#include"BossWizardShootingState.h"
#include"BossWizardStandingState.h"
#include"BossWizardFlyingState.h"
#include"BossWizardPunchingState.h"
#include"BossWizardStandSmileState.h"
#include"BulletWizardNormal.h"

class BossWizard :public Enemy {
private:
	std::unordered_map<State, Animation *>animations; //cac animation cua player
	std::unordered_map<State, BossWizardState*> wizardStates;
	static BossWizard* instance;

	void LoadAllStates();
	void LoadAllAnimations();
	void AddPosX();
	void AddPosY();
public:
	float deltaY = 0;
	float deltaX = 0;
	float getWidth();
	float getHeight();
	float getPosToBottom();
	float getPosToRight();
	int flyMode;
	BossWizardState * wizardState;
	static BossWizard* getInstance();
	void ChangeState(State stateName) override;
	void Update(float dt);
	BossWizard();
	~BossWizard();
	void Render();
	BoundingBox getBoundingBox()override;
	State state;
	Type type;
	Animation * curanimation;
	void OnCollision(Object* object, collisionOut* collision)override;
	void OnNotCollision(Object* object)override;
};