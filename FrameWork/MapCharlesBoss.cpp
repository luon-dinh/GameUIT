#include "MapCharlesBoss.h"

MapCharlesBoss::MapCharlesBoss(const char * imgPath, const char * txtPath, Tag tag) : TileMap(imgPath, txtPath, tag)
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