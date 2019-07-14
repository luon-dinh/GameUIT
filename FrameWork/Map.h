#pragma once
#include"Global.h"
#include"SpriteManager.h"
#include "Camera.h"
#include <fstream>
#include<stdio.h>
#include<string>
#include<sstream>
#include"KeyboardManager.h"

class Map
{
private:
	int colBegin;
	int colEnd;
	int columns;
	int rows;
	int** mapTiles;
	Tag mapLevel;

public:
	Map(int level);
	void Update();
	void Render();

	int width;
	int height;
	Rect rect;
};