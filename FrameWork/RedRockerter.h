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
	float timeCurrentState;
	std::unordered_map<State, Animation*> animations;
	std::list<Object*>* additionalObjects;
	std::list<Object*>* getAdditionalObjects()override
	{
		return additionalObjects;
	}

	void LoadAllAnimation();
	void ChangeState(State state)override;
	void Shoot() ;
	void OnCollision(Object* object, collisionOut* colOut) override;
	void Update(float dt) override;
	void Respawn()override {};
	void Render();
	BoundingBox getBoundingBox();// boundingbox của ngồi khác nên cần override lại
};