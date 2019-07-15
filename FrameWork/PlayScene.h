#pragma once
#include "Scene.h"
#include "GameMap.h"
#include "KeyboardManager.h"
#include "Object.h"
#include "Player.h"

class PlayScene : public Scene
{
public:
	void Update(double dt);
	void LoadContent();
	void Draw();
	std::vector<Object*> mapStaticObject;
	PlayScene();
	~PlayScene();

private:
	void ProcessKeyBoardInput(double dt);
	void UpdateCameraWithPlayerPos(double dt);
	void CollisionProcess(double dt);
	void EnvironmentUpdate(double dt);
	const char * world11tile = (char*)".\\..\\\\Resources\\Images\\Maps\\Charles\\charles_map.png";
	const char * world11map = (char*)".\\..\\Resources\\Images\\Maps\\Charles\\charles_map.txt";
	const char * world11MapObject = (char*) ".\\MapResources\\cap_charile_map_object.txt";
	GameMap* world11;	
	Player* player;
	Camera * camera;
};