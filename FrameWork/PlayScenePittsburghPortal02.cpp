#include "PlayScenePittsburghPortal02.h"

PlayScenePittsburghPortal02::PlayScenePittsburghPortal02()
{
	//Khởi tạo các world.
	world = new GameMap(pbPortal02LightPNG, pbPortal02LightTXT, pbPortal02MapObject, MapName::PITTSBURGHPORTAL2LIGHT);
	worldDark = new GameMap(pbPortal02DarkPNG, pbPortal02DarkTXT, pbPortal02MapObject, MapName::PITTSBURGHPORTAL2DARK);

	world->SetCamera(camera);
	worldDark->SetCamera(camera);

	//mapStaticObject = world->getStaticObject();
	currentWorld = worldDark;
	//Xét tạo Grid.
	grid = new Grid(world->getMapWidth(), world->getMapHeight(), pbPortal02Spawn, pbPortal02MapObject);
	//Thêm player và shield vào Grid.
}

PlayScenePittsburghPortal02::~PlayScenePittsburghPortal02()
{
	if (worldDark != nullptr)
		delete worldDark;
}

void PlayScenePittsburghPortal02::Update(double dt)
{
	PlaySceneWithLight::Update(dt);
	//Test phím bật/tắt đèn.
	if (KeyboardManager::getInstance()->getKeyPressedOnce(DIK_L))
		TurnOnOffLight();

	//Test phím chuyển màn.
	if (KeyboardManager::getInstance()->getKeyPressedOnce(DIK_K) && isLightOn)
		ReplaceToThisMap = MapName::PITTSBURGHLIGHT;
	else if (KeyboardManager::getInstance()->getKeyPressedOnce(DIK_K) && !isLightOn)
		ReplaceToThisMap = MapName::PITTSBURGHDARK;
}

void PlayScenePittsburghPortal02::ResetPlayerPosition()
{
	//Reset lại player khi vừa bắt đầu màn chơi.
	Player * player = Player::getInstance();
	player->pos.x = 64; //Ngay cánh cửa.
	player->pos.y = player->height + 10;
	player->ChangeState(State::JUMPING);
	player->SetOnAirState(Player::OnAir::Falling);

	//Update lại camera sau khi set.
	UpdateCameraWithPlayerPos();
}

void PlayScenePittsburghPortal02::GoToNextScene()
{
	//Xét tình trạng đèn hiện tại để chuyển cho phù hợp.
	if (isLightOn)
		ReplaceToThisMap = MapName::PITTSBURGHLIGHT;
	else if (!isLightOn)
		ReplaceToThisMap = MapName::PITTSBURGHDARK;
}