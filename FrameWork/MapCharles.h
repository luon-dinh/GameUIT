#pragma once
#include "TileMap.h"

class MapCharles : public TileMap
{
private:
	const int SEWER_ANIM_ID = 69;
	const int WATER_TOP_ANIM_ID = 72;
	const int WATER_BOTTOM_ANIM_ID = 75;
	Animation * waterTopAnim;
	Animation * waterBottomAnim;
	Animation * sewerAnim;
	const int delayWaterFlow = 150; //Khoảng thời gian chuyển giữa các frame water flow.
	const int delaySewerFlow = 150; //Khoảng thời gian chuyển giữa các frame sewer.
public:
	MapCharles(const char * imgPath, const char * txtPath);
	~MapCharles();
	void Draw(Camera* camera) override;
	void Update(double dt) override;
};