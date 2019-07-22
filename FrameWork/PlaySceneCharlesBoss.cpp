#include "PlaySceneCharlesBoss.h"


PlaySceneCharlesBoss::PlaySceneCharlesBoss()
{
	//Các singleton đã được tự động load khi gọi hàm khởi tạo tại class cha.
	//Vì vậy chúng ta không cần thực hiện lại việc load singleton.

	//Chúng ta tạo ra 2 GameMap : Một sáng một tối dùng để chuyển khi bật đèn sáng/tối.
	world = new GameMap(world01BossTileLight, world01BossMapLight, world01BossMapObject, MapName::CHARLESBOSSLIGHT);
	worldDark = new GameMap(world01BossTileDark, world01BossMapDark, world01BossMapObject, MapName::CHARLESBOSSDARK);

	world->SetCamera(camera);
	worldDark->SetCamera(camera);

	mapStaticObject = world->getStaticObject(); //Lấy entity của tất cả các object có trong map.

	currentWorld = world;
	isLightOn = true;

	//Xét tạo Grid.
	grid = new Grid(world->getMapWidth(), world->getMapHeight());
	//Thêm player và shield vào Grid.
	grid->Add(player);
	grid->Add(shield);
}

PlaySceneCharlesBoss::~PlaySceneCharlesBoss()
{
	if (worldDark != nullptr)
		delete worldDark;
}

void PlaySceneCharlesBoss::ResetPlayerPosition()
{
	//Reset lại player luôn.
	Player * player = Player::getInstance();
	player->pos.x = 0;
	player->pos.y = SCREEN_HEIGHT;
	player->ChangeState(State::JUMPING);
	player->SetAirState(Player::OnAir::Falling);
	player->SetGroundCollision(new GroundCollision());
	//Update lại camera sau khi set.
	UpdateCameraWithPlayerPos();
}

void PlaySceneCharlesBoss::Update(double dt)
{
	PlaySceneWithLight::Update(dt);

	//Test phím bật/tắt đèn.
	if (KeyboardManager::getInstance()->getKeyPressedOnce(DIK_L))
		TurnOnOffLight();

	//Kiểm tra xem player đã đi đến đích chưa.
	if (player->pos.x > SCREEN_WIDTH - 50)
	{
		Done = true;
		ReplaceToThisMap = MapName::PITTSBURGHDARK;
	}
}