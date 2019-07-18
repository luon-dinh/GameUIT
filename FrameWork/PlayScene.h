#pragma once
#include "Scene.h"
#include "GameMap.h"
#include "KeyboardManager.h"
#include "Object.h"
#include "Player.h"
#include "Global.h"

//Các PlayScene khác nhau sẽ có nhiều đoạn code có thể dùng chung được.
//Ý tưởng ở đây của việc kế thừa là những đoạn code dùng chung sẽ được gom lại ở lớp cha PlayScene này.
//Lớp con sẽ override lại tất cả phương thức virtual của lớp cha.
//Những chỗ nào code không đổi thì các lớp con sẽ gọi phương thức của lớp cha.
//Những chỗ nào có đổi thì lớp con sẽ tự implement lại phương thức đó.

class PlayScene : public Scene
{
public:
	virtual void Update(double dt);
	virtual void LoadContent();
	virtual void Draw();
	bool isDone() { return Done; }
	virtual void ResetCamera(); //Hàm dùng để reset camera lại (cập nhật lại vị trí, thông tin của map để camera biết).
	PlayScene(); //Khởi tạo player và camera.
	~PlayScene();
protected:
	std::vector<Object*> mapStaticObject;
	bool Done = false; //Biến dùng để xét xem cảnh hiện tại đã hoàn thành chưa.
	virtual void ProcessUpdates(double dt);
	virtual void UpdateCameraWithPlayerPos(double dt);
	virtual void CollisionProcess(double dt);
	virtual void EnvironmentUpdate(double dt);
	GameMap* world;
	Player* player;
	Camera * camera;
};