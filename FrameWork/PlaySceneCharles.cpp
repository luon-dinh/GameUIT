#include "PlaySceneCharles.h"
#include "BulletWhiteFlyingRocketer.h"
#include "WhiteFlyingRobot.h"
#include "BulletRedRocket.h"
#include "RedRocketRobotOneSided.h"
#include "RedRocketRobotTwoSided.h"
#include "RedRocketRobotTwoSidedNonLinear.h"
#include "RedRocketRobotNonShooting.h"
#include "Camera.h"	
#include "Solder.h"

PlaySceneCharles::PlaySceneCharles()
{
	//Các singleton đã được tự động load khi gọi hàm khởi tạo tại class cha.
	//Vì vậy chúng ta không cần thực hiện lại việc load singleton.

	world = new GameMap(world01tile, world01map, world01MapObject, MapName::CHARLES);
	world->SetCamera(camera);
	camera->SetMapProperties(world->getMapHeight(), world->getMapWidth());
	//mapStaticObject = world->getStaticObject(); //Lấy entity của tất cả các object có trong map.

	//Xét tạo Grid.
	grid = new Grid(world->getMapWidth(), world->getMapHeight(), world01SpawnLocation, world01MapObject);
	//grid->Add(new BulletWhiteFlyingRocketer(Object::MoveDirection::LeftToRight, 1500, SCREEN_HEIGHT));
	//grid->Add(new WhiteFlyingRobot(200, 180));
	//Solder* soldier = new Solder(RunType::NOTRUN);
	//soldier->pos.x = 1500;
	//soldier->pos.y = 180;
	//grid->Add(soldier);
	////grid->Add(new BulletRedRocket(Object::MoveDirection::LeftToRight, 1550, 51, 1));
	//grid->Add(new RedRocketRobotOneSided(1400, 51));
	//grid->Add(new RedRocketRobotTwoSided(1600, 51));
	//grid->Add(new RedRocketRobotTwoSidedNonLinear(1500,90));
	//grid->Add(new RedRocketRobotNonShooting(1800, 51));
}

PlaySceneCharles::~PlaySceneCharles()
{

}

void PlaySceneCharles::ResetPlayerPosition()
{
	//Reset lại player luôn.
	Player * player = Player::getInstance();
	player->pos.x = 0;
	player->pos.y = SCREEN_HEIGHT + 20;
	player->ChangeState(State::JUMPING);
	player->SetOnAirState(Player::OnAir::Falling);

	//Update lại camera sau khi set.
	UpdateCameraWithPlayerPos();
}

void PlaySceneCharles::Update(double dt)
{
	PlayScene::Update(dt);

	//Nếu chưa từng khoá camera thì tới đúng thời điểm ta sẽ khoá.
	if (!isCameraAlreadyLockedOnce)
	{
		//Xét nếu player nằm trong vùng lock thì lock camera lại.
		auto inRange = [](int inputValue, int valueToCompare, int range = 10) {return ( (valueToCompare - range) < inputValue) && (inputValue < (valueToCompare + range)); };
		if (inRange(player->pos.x, 415) && inRange(player->pos.y, 50, 100))
		{
			camera->LockCamera();
			isCameraAlreadyLockedOnce = true;
			isCameraLocking = true;
			this->KillAllEnemyInActiveCells();
		}
	}

	//Xét nếu đang bị khoá camera thì ta sẽ spawn liên tục cho đến khi giết đủ số lượng enemy.
	if (isCameraLocking)
	{
		//Thêm vào con robot đỏ bên phải.
		if (!isAddSoldier)
		{
			Object* redRobot = new RedRocketRobotNonShooting(500, 90);
			if (!this->AddObjectToPlayScene(redRobot))
				delete redRobot;
			isAddSoldier = true;
		}
		else
		{
			Object* blueSoldier = new Solder(RunType::CANRUN, 250, 85);
			if (!this->AddObjectToPlayScene(blueSoldier))
				delete blueSoldier;
			isAddSoldier = false;
		}
	}

	//Xét thêm điều kiện hoàn thành là khi player đi đến tận cùng phải của map.
	if (player->pos.x >= world->getMapWidth() - 100)
	{
		if (player->CanGoNextScene())
		{
			Done = true;
			ReplaceToThisMap = MapName::CHARLESBOSSLIGHT;
		}
	}
}