#include "MapCharlesBoss.h"

MapCharlesBoss::MapCharlesBoss(const char * imgPath, const char * txtPath) : TileMap(imgPath, txtPath, Tag::MAPCHARLESBOSS)
{

}

MapCharlesBoss::~MapCharlesBoss()
{

}

void MapCharlesBoss::Draw(Camera* camera)
{
	TileMap::Draw(camera);
}

void MapCharlesBoss::Update(double dt)
{
	TileMap::Update(dt);
}