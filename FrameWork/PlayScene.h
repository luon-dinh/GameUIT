#pragma once
#include "Scene.h"
#include "Grid.h"
#include "GameMap.h"
#include "KeyboardManager.h"
#include "Object.h"
#include "Player.h"
#include "Shield.h"
#include "BulletWhiteFlyingRocketer.h"
#include "Global.h"
#include "DrawDebug.h"

//Các PlayScene khác nhau sẽ có nhiều đoạn code có thể dùng chung được.
//Ý tưởng ở đây của việc kế thừa là những đoạn code dùng chung sẽ được gom lại ở lớp cha PlayScene này.
//Lớp con sẽ override lại tất cả phương thức virtual của lớp cha.
//Những chỗ nào code không đổi thì các lớp con sẽ gọi phương thức của lớp cha.
//Những chỗ nào có đổi thì lớp con sẽ tự implement lại phương thức đó.

class PlayScene : public Scene
{
public:
	virtual void Update(double dt);
	virtual void Draw();
	bool isDone() { return Done; }
	MapName GetAndResetDestinationMap();
	virtual void ResetCamera(); //Hàm dùng để reset camera lại (cập nhật lại vị trí, thông tin của map để camera biết).
	virtual void ResetPlayerPosition() {}; //Nhớ override hàm setPlayer lại cho từng PlayScene khác nhau.
	void AddPlayerElementsToGrid(); //Thêm vào grid các thành phần của player
	PlayScene(); //Khởi tạo player và camera.
	~PlayScene();
protected:
	//std::vector<Object*> mapStaticObject;
	bool Done = false; //Biến dùng để xét xem cảnh hiện tại đã hoàn thành chưa (phục vụ cho mục đích xoá khỏi bộ nhớ).
	MapName ReplaceToThisMap = MapName::NOMAP; //Biến dùng để báo cho Scene Manager chuyển cảnh sang map mới.
	virtual void ProcessUpdates(double dt);
	virtual void UpdateCameraWithPlayerPos(double dt = 0);
	virtual void CollisionProcess(double dt);
	virtual void EnvironmentUpdate(double dt);
	virtual void DrawDebugBoxForPlayer();
	virtual void DrawDebugBoxForStaticObjects();
	GameMap* world;
	Grid* grid;
	Camera * camera;
	//Để đó nhưng chủ yếu là ta thao tác trong Grid.
	//Dưới đây là những biến chỉ giữ lại để xét điều kiện thôi.
	//Update, draw ta gọi Grid để nó quản lý.
	Player* player;
	Shield* shield;
};