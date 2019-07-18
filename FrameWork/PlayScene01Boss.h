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
	
	GameMap* worldDark;

	GameMap* currentWorld;

	const char * world01BossMapLight = (char*)".\\..\\Resources\\Images\\Maps\\CharlesBoss\\charles_boss_light.txt";
	const char * world01BossTileLight = (char*)".\\..\\Resources\\Images\\Maps\\CharlesBoss\\charles_boss_light.png";
	const char * world01BossMapDark = (char*)".\\..\\Resources\\Images\\Maps\\CharlesBoss\\charles_boss_dark.txt";
	const char * world01BossTileDark = (char*)".\\..\\Resources\\Images\\Maps\\CharlesBoss\\charles_boss_dark.png";
	const char * world01BossMapObject = (char*)".\\..\\Resources\\Images\\Maps\\CharlesBoss\\charles_boss_map_object.txt";

	bool isLightOn = true;

	void TurnOnOffLight();
	void ProcessUpdates(double dt) override;
	void UpdateCameraWithPlayerPos(double dt) override;
	void CollisionProcess(double dt) override;
	void EnvironmentUpdate(double dt) override;
};