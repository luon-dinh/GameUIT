#pragma once
#include "MapStaticObject.h"
#include "PlatformFire.h"

class MovingPlatform : public Object
{
	//Kích thước của platform.
	const int platformWidth = 32;
	const int platformHeight = 16;
	
	PlatformFire* fireDownLeft;
	PlatformFire* fireDownRight;
	PlatformFire* fireLeft;
	PlatformFire* fireRight;

	Animation* platformAnim;

	bool isMoving = false;

	void UpdatePlatformFirePosition();
public:
	MovingPlatform(int posX, int posY);
	~MovingPlatform();
	virtual void Update(float dt) override;
	virtual void Render() override;
	//Chỗ nào cần cách move khác chỉ cần override lại là xong.
	virtual void MovePlatform() {};
	//Cấm không cho Grid xoá platform.
	void DeactivateObjectInGrid() override {};
	BoundingBox getBoundingBox() override;
};