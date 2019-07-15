﻿#pragma once
#include "Camera.h"
#include "MapCharles.h"
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
	void LoadContent();
	std::vector<Object*> &getStaticObject();
	GameMap(const char * imgPath, const char * txtPath, const char * mapObjectPath);
	~GameMap();
private:
	long mapHeight;
	long mapWidth;
	const char * imgPath;
	const char * txtPath;
	const char * mapObjectPath;
	std::vector<Object*> staticObject;
	Camera * camera;
	TileMap *tMap;
};