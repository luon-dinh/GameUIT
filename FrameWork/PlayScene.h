#pragma once
#include "Scene.h"
#include "Map1.h"
#include "KeyboardManager.h"
#include "Object.h"
#include "Player.h"
#include "Global.h"

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
	void ProcessUpdates(double dt);
	void UpdateCameraWithPlayerPos(double dt);
	void CollisionProcess(double dt);
	void EnvironmentUpdate(double dt);
	const char * world11tile = (char*)".\\..\\Resources\\Images\\Maps\\Charles\\charles_map.png";
	const char * world11map = (char*)".\\..\\Resources\\Images\\Maps\\Charles\\charles_map.txt";
	const char * world11MapObject = (char*) ".\\MapResources\\cap_charile_map_object.txt";
	const char * animWaterFlowTop = (char*)".\\..\\Resources\\Images\\Maps\\Charles\\water_1.png";
	const char * animWaterFlowBottom = (char*)".\\..\\Resources\\Images\\Maps\\Charles\\water_2.png";
	const char * animSewer = (char*)".\\..\\Resources\\Images\\Maps\\Charles\\sewer.png";
	
	Map1* world11;	
	Player* player;
	Camera * camera;
};