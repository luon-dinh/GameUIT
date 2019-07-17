#pragma once
#include "PlayScene.h"
#include "GameMap.h"
#include "Camera.h"
#include "Player.h"

class PlayScene01Boss : public PlayScene
{
public:
	//Hàm này dùng để cập nhật Scene (VD Scene có các vật thể chuyển động theo thời gian,...).
	void Update(double dt) override;

	//Hàm này dùng để load toàn bộ nội dung của một Scene (bao gồm các đối tượng của Scene, Scene Map,...).
	void LoadContent() override;

	//Hàm này dùng để vẽ một Scene lên màn hình.
	void Draw() override;

	PlayScene01Boss();
	~PlayScene01Boss();

private:
	
	const char * world01BossMap = "";
	const char * world01BossTile = "";
	const char * world01BossMapObject = "";

	void ProcessUpdates(double dt) override;
	void UpdateCameraWithPlayerPos(double dt) override;
	void CollisionProcess(double dt) override;
	void EnvironmentUpdate(double dt) override;
};