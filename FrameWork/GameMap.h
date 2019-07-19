#pragma once
#include "Camera.h"
#include "MapCharles.h"
#include "MapCharlesBoss.h"
#include "MapPittsburgh.h"
#include "Sprite.h"
#include "KeyboardManager.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include "Debug.h"
#include "Object.h"
#include "TextureManager.h"

class GameMap
{
public:
	enum MapType
	{
		Map01,
		Map01Boss,
		Map02,
		Map02Boss
	};
	long getMapHeight() { return mapHeight; }
	long getMapWidth() { return mapWidth; }
	void Draw();
	void Update(double dt);
	void SetCamera(Camera*);
	std::vector<Object*> &getStaticObject();
	GameMap(const char * imgPath, const char * txtPath,  const char * mapObjectPath, MapName map);
	~GameMap();
private:
	long mapHeight;
	long mapWidth;
	const char * imgPath;
	const char * txtPath;
	const char * mapObjectPath;
	
	std::vector<Object*> staticObject;
	std::vector<D3DXVECTOR3> staticObjectDrawingPosition;
	const int debugTileSize = 8;
	Sprite* debugSprite;
	Camera * camera;
	TileMap *tMap;
	void CalculateAllDebugDrawingVectors();
	void DrawAllDebugVector();
	void LoadMapObject();
};