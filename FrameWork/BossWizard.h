#pragma once
#include"Enemy.h"
#include"BossWizardRunningState.h"
#include"BossWizardShootingState.h"
#include"BossWizardStandingState.h"
#include"BossWizardFlyingState.h"
#include"BossWizardPunchingState.h"
#include"BossWizardStandSmileState.h"
#include"BossWizardDeadState.h"
#include"BulletWizardNormal.h"
#include"BulletWizardSpecial.h"

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
	const float minMap = 20;
	const float maxMap = 235;
	const float flySpeedx1 = 1;
	const float flySpeedx2 = 2.5;
	const float flySpeedy = 2;
	const float xRun = 100;
	const float maxXToFly1 = 90;
	const float maxTimeNotRender = 1000;
	const float maxHelth = 20;
	const float bulletSpeed = 2;
	const float maxTimeToShoot = 1080;
	const float maxTimeToPunch = 500;
	const float defaultDT = 50;
	const float shoot1 = 30;
	const float shoot2 = 80;
	bool canShootOnAir;
	float timeDelayShootOnAir;
	float timeToShoot;
	float delayShoot;
	bool isCollide;
	int hitTime;
	float timePunch;
	float deltaY;
	float deltaX;
	float getWidth();
	float getHeight();
	float getPosToBottom();
	float getPosToRight();
	int flyMode;
	int flyTimes;
	float timeNotRender ;
	bool turnOffLight;
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
	Animation * currentanimation;
	void OnCollision(Object* object, collisionOut* collision)override;
	void OnNotCollision(Object* object)override;
	bool OnRectCollided(Object* object, CollisionSide side)override;
};