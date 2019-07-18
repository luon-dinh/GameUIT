#pragma once
#include "TileMap.h"

class MapPittsburgh : public TileMap
{
public:
	MapPittsburgh(const char * imgPath, const char * txtPath, Tag tag);
	~MapPittsburgh();
};