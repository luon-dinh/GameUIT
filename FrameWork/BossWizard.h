#pragma once
#include"Enemy.h"
#include"BossWizardRunningState.h"
#include"BossWizardShootingState.h"
#include"BossWizardStandingState.h"
#include"BossWizardFlyingState.h"
#include"BossWizardPunchingState.h"
#include"BossWizardStandSmileState.h"
#include"BossWizardDeadState.h"
#include"BossWizardBeatenState.h"

#include"BulletWizardNormal.h"
#include"BulletWizardSpecial.h"
#include"Equation.h"

class BossWizard :public Enemy {
private:
	std::unordered_map<State, Animation *>animations; //cac animation cua boss
	std::unordered_map<State, BossWizardState*> wizardStates;
	static BossWizard* instance;

	void LoadAllStates();
	void LoadAllAnimations();
	void AddPosX();
	void AddPosY();
public:
	const float minMap = 0;
	const float maxMap = 256;
	const float flySpeedx1 = 1;
	const float flySpeedx2 = 3;
	const float flySpeedy = 2.5;
	const float maxFlyy1 = 30;
	const float maxXToFly1 = 80;
	const float maxTimeNotRender = 1000;
	const float maxHelth = 30;
	const float bulletSpeed = 2.7;
	const float defaultDT = 50;
	bool canShootOnAir;
	bool isCollide;
	int hitTime;
	float deltaY;
	float deltaX;
	int flyMode;
	int flyTimes;
	float timeNotRender;
	bool turnOffLight;
	int countBullet;
	bool canNewParapol = true;
	bool isMode1;

	State state;
	Type type;
	Animation * currentanimation;
	BossWizardState * wizardState;
	Equation* parapol;

	float getWidth();
	float getHeight();
	float getPosToBottom();
	float getPosToRight();
	static BossWizard* getInstance();
	void ChangeState(State stateName) override;
	void Update(float dt);
	BossWizard();
	~BossWizard();
	void Render();
	BoundingBox getBoundingBox()override;
	void OnCollision(Object* object, collisionOut* collision)override;
	void OnNotCollision(Object* object)override;
	bool OnRectCollided(Object* object, CollisionSide side)override;
};