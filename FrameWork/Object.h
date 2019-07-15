#pragma once
#include"Global.h"
#include"Sprite.h"
#include"Collision.h"
#include"Animation.h"
class Object {
public:
	Object() {};
	virtual ~Object() {};

	D3DXVECTOR2 pos;
	float vx, vy;

	Tag tag;
	Type type;

	int width, height;

	BoundingBox getBoundingBox();


	virtual void Render();

	virtual void Update(float dt);

};
