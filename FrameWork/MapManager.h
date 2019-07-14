#pragma once
#include "Map.h"
#include<vector>
class MapManager
{
private:
	static MapManager* instance;
	std::vector<Map*> maps;
public:
	Map* getMap(int mapindex);
	void loadResource();
	static MapManager* getInstance();
};

