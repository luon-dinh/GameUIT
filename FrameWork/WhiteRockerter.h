#include"Enemy.h"
#include"BulletManager.h"
#include"Shield.h"
class WhiteRockerter :public Enemy
{
public:
	WhiteRockerter();
	~WhiteRockerter();
	State stateName;
	bool canRun;
	float timeCurrentState;
	std::unordered_map<State, Animation*> animations;
	std::list<Object*> additionalObjects;
	std::list<Object*>* getAdditionalObjects()override
	{
		return &additionalObjects;
	}

	void LoadAllAnimation();
	void ChangeState(State state)override;
	void OnCollision(Object* object, collisionOut* colOut) override;
	void Update(float dt) override;
	void Render();
	BoundingBox getBoundingBox();// boundingbox của ngồi khác nên cần override lại
};