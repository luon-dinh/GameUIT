#pragma once
#include "Collision.h"
#include "Global.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "Camera.h"

class DrawDebug
{
public:
	//Vẽ debug dựa vào boundBox và màu cần vẽ.
	static void DrawBoundingBox(BoundingBox boundBox, Tag colorTag);
};