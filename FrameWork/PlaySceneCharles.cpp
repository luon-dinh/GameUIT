#include "PlaySceneCharles.h"

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
}

PlaySceneCharles::~PlaySceneCharles()
{

}

void PlaySceneCharles::ResetPlayerPosition()
{
	//Reset lại player luôn.
	Player * player = Player::getInstance();
	player->pos.x = 1500;
	player->pos.y = SCREEN_HEIGHT + 20;
	player->ChangeState(State::JUMPING);
	player->SetAirState(Player::OnAir::Falling);
	player->SetGroundCollision(new GroundCollision());

	//Update lại camera sau khi set.
	UpdateCameraWithPlayerPos();
}

void PlaySceneCharles::Update(double dt)
{
	PlayScene::Update(dt);
	//Xét thêm điều kiện hoàn thành là khi player đi đến tận cùng phải của map.
	if (player->pos.x >= world->getMapWidth() - 100)
	{
		Done = true;
		ReplaceToThisMap = MapName::CHARLESBOSSLIGHT;
	}
		
}