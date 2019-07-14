#include "MapManager.h"

MapManager * MapManager::instance = NULL;



MapManager* MapManager::getInstance()
{
	if (!instance)
		instance = new MapManager();
	return instance;
}

void MapManager::loadResource()
{
	for (int i = 0; i < NUMBER_MAP; i++)
	{
		maps.push_back(new Map(i));
	}
}

Map* MapManager::getMap(int mapindex)
{
	return maps[mapindex-1];
}