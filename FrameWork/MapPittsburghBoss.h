#pragma once
#include "TileMap.h"

class MapPittsburghBoss : public TileMap
{
private:
	const int CARO_DOWN_ANIM = 0;
	const int CARO_UP_ANIM = 1;
	
	Animation * caroUpAnim;
	Animation * caroDownAnim;

	const int delayCaroAnimation = 15;
public:
	MapPittsburghBoss(const char * imgPath, const char * txtPath);
	~MapPittsburghBoss();
	void Draw(Camera* camera) override;
	void Update(double dt) override;
};