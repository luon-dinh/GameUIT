#pragma once
#include "GameMap.h"

class MapCharles : public GameMap
{
private:
	Animation * water;
	Animation * sewer;
public:
	MapCharles(const char * imgPath, const char * txtPath, const char * mapObjectPath, const char * waterTopPath, const char * waterBottomPath, const char * sewerPath);
	~MapCharles();
};