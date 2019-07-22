#pragma once
#include"Global.h"
#include"Sprite.h"
#include"Collision.h"
#include"Animation.h"

class Object {
public:
	Object() { vx = vy = 0; };
	virtual ~Object() {};

	D3DXVECTOR2 pos;
	float vx, vy;

	Tag tag;
	Type type;

	int width, height;

	BoundingBox getBoundingBox();
	int getWidth();
	int getHeight();
	
	BoundingBox getStaticObjectBoundingBox();

	virtual void Render();
	virtual void OnCollision(Object* object, collisionOut* colOut) {};
	virtual void Update(float dt);
	virtual void Respawn() {} ;
};
