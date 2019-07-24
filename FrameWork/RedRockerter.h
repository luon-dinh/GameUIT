#include"Enemy.h"
#include"BulletManager.h"
#include"Shield.h"
class RedRockerter :public Enemy
{
public:
	RedRockerter();
	~RedRockerter();
	State stateName;
	Bullet* bullet,*bullet2;//cần 2 viên đạn cho bắn đứng và bắn ngồi
	bool canRun;
	float timeCurrentState;
	std::unordered_map<State, Animation*> animations;

	void LoadAllAnimation();
	void ChangeState(State state)override;
	void Shoot(int a) ;
	void OnCollision(Object* object, collisionOut* colOut) override;
	void Update(float dt) override;
	void Respawn()override {};
	void Render();
	BoundingBox getBoundingBox();// boundingbox của ngồi khác nên cần override lại
};