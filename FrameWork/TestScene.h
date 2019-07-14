#pragma once
#include "Scene.h"
#include "GameMap.h"
#include "InputManager.h"

class TestScene : public Scene
{
public:
	void Update(double dt);
	void LoadContent();
	void Draw();
	TestScene();
	~TestScene();
private:
	const char * world11tile = ".\\..\\MapResources\\cap_charile_16_16.png";
	const char * world11map = ".\\..\\MapResources\\cap_charile_16_16.txt";
	GameMap* world11;
	Camera * camera;
};