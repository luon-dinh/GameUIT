#include"Enemy.h"
#include"BulletManager.h"
#include"Shield.h"
class RedRockerter :public Enemy
{
public:
	RedRockerter();
	~RedRockerter();
	State stateName;
	bool canRun;
	const int score = 300;
	float timeCurrentState;
	std::unordered_map<State, Animation*> animations;

	void LoadAllAnimation();
	void ChangeState(State state)override;
	void OnCollision(Object* object, collisionOut* colOut) override;
	bool OnRectCollided(Object* object, CollisionSide side)override { return false; };
	void OnNotCollision(Object* object)override {};
	void Update(float dt) override;
	void Render();
	BoundingBox getBoundingBox();// boundingbox của ngồi khác nên cần override lại
};