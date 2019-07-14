#pragma once
#include "Scene.h"
#include "Player.h"
#include<map>
#include"MapManager.h"
#include "SceneManager.h"

class PlayScene : public Scene
{
private:
	Player* p;
	Map* map;
	int level;
	Rect endRect;

public:
	PlayScene(int level);
	~PlayScene();

	void Update(float dt);
	void Render();									
	void OnKeyDown();						
	void OnKeyUp();							
};