#pragma once
#include "PlayScene.h"

class PlayScene01 : public PlayScene
{
public:
	//Hàm này dùng để cập nhật Scene (VD Scene có các vật thể chuyển động theo thời gian,...).
	void Update(double dt) override;

	//Hàm này dùng để load toàn bộ nội dung của một Scene (bao gồm các đối tượng của Scene, Scene Map,...).
	void LoadContent() override;

	//Hàm này dùng để vẽ một Scene lên màn hình.
	void Draw() override;

	PlayScene01();
	~PlayScene01();

private:

	//Hằng số dùng để lưu địa chỉ đến các file.
	const char * world01tile = (char*)".\\..\\Resources\\Images\\Maps\\Charles\\charles_tile.png";
	const char * world01map = (char*)".\\..\\Resources\\Images\\Maps\\Charles\\charles_map.txt";
	const char * world01MapObject = (char*) ".\\..\\Resources\\Images\\Maps\\Charles\\charles_map_object.txt";

	void ProcessUpdates(double dt) override;
	void UpdateCameraWithPlayerPos(double dt) override;
	void CollisionProcess(double dt) override;
	void EnvironmentUpdate(double dt) override;
};