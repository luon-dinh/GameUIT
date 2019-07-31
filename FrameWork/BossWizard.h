#pragma once
#include"Enemy.h"
#include"BossWizardRunningState.h"
#include"BossWizardShootingState.h"
#include"BossWizardStandingState.h"
#include"BossWizardFlyingState.h"
#include"BossWizardPunchingState.h"
#include"BossWizardStandSmileState.h"
#include"BulletWizardNormal.h"
#include"BulletWizardSpecial.h"

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
	const float minMap = 15;
	const float maxMap = 250;
	const float flySpeedx1 = 0.8;
	const float flySpeedx2 = 2.5;
	const float flySpeedy = 2;
	const float xRun = 100;
	const float xPunch = 30;
	bool isCollide;
	int hitTime;
	float deltaY;
	float deltaX;
	float getWidth();
	float getHeight();
	float getPosToBottom();
	float getPosToRight();
	int flyMode;
	int flyTimes;
	float timeNotRender ;
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