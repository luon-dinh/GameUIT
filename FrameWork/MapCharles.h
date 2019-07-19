#pragma once
#include "TileMap.h"

class MapCharles : public TileMap
{
private:
	const int SEWER_ANIM_ID = 69;
	const int WATER_TOP_ANIM_ID = 72;
	const int WATER_BOTTOM_ANIM_ID = 75;
	const int EXIT_SIGN_BEGIN_ID = 73;
	const int EXIT_SIGN_END_ID = 74;
	Animation * waterTopAnim;
	Animation * waterBottomAnim;
	Animation * sewerAnim;
	Animation * exitSign;
	const int delayWaterFlow = 50; //Khoảng thời gian chuyển giữa các frame water flow.
	const int delaySewerFlow = 50; //Khoảng thời gian chuyển giữa các frame sewer.
	const int delayExitSignFlash = 150; //Khoảng thời gian chớp tắt exit sign.
public:
	MapCharles(const char * imgPath, const char * txtPath);
	~MapCharles();
	void Draw(Camera* camera) override;
	void Update(double dt) override;
};