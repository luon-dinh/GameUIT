#pragma once
#include "PlayScene.h"

class PauseScene : public PlayScene
{
public:
	void Update(double dt) override;
	void Draw() override;

	void ResetCamera() override {};
	void ResetPlayerPosition() {};
	void AddPlayerElementsToGrid() override {}; //Thêm vào grid các thành phần của player
	void UpdateCameraWithPlayerPos(double dt = 0) override {};

	PauseScene();
	~PauseScene();
protected:
	const char * pathToPauseBackground = (char*)".\\..\\Resources\\Images\\Maps\\PauseScene\\PauseScene.png";
	void ProcessUpdates(double dt) override {};
	Player* player;
	Sprite* backgroundImage;
	void CollisionProcess(double dt) override {};
	void EnvironmentUpdate(double dt) override {};
	void DrawDebugBoxForPlayer() override {};
	void DrawDebugBoxForStaticObjects() override {};

};