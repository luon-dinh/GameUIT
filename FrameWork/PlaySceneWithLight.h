#pragma once
#include "PlayScene.h"

class PlaySceneWithLight : public PlayScene
{
public:
	//Hàm này dùng để cập nhật Scene (VD Scene có các vật thể chuyển động theo thời gian,...).
	virtual void Update(double dt) override;

	//Hàm này dùng để vẽ một Scene lên màn hình.
	virtual void Draw() override;
	bool getLightStatus() { return isLightOn; }
	void setLightStatus(bool _status)
	{
		if (_status != isLightOn) //Nếu trạng thái hiện tại cần sự chuyển đổi thì ta chuyển đổi.
			TurnOnOffLight();
	}
	PlaySceneWithLight();
	~PlaySceneWithLight();
protected:
	bool isLightOn;
	GameMap* worldDark;
	GameMap* currentWorld;
	void TurnOnOffLight();
	virtual void ProcessUpdates(double dt) override;
	virtual void UpdateCameraWithPlayerPos(double dt) override;
	virtual void CollisionProcess(double dt) override;
	virtual void EnvironmentUpdate(double dt) override;
};