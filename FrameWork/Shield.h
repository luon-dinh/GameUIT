#pragma once
#include "Object.h"
#include"TextureManager.h"
#include"SpriteManager.h"
#include"Player.h"
class Shield :
	public Object
{
private:
	static Shield* instance;
	//std::vector<Sprite*>sprites;//chứa danh sách các sprite của shield
	Animation * animation;
public:
	int currentSpriteIndex;
	Player::MoveDirection direction;

	static Shield* getInstance();
	void Update(float dt);
	void Render();
	void InputHandler(float dt);
	void OnCollision(Object* object, collisionOut out);
	Shield();
	~Shield();
};

