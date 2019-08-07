#include "PlaySceneCharlesBoss.h"
#include "Door.h"


PlaySceneCharlesBoss::PlaySceneCharlesBoss()
{
	//Các singleton đã được tự động load khi gọi hàm khởi tạo tại class cha.
	//Vì vậy chúng ta không cần thực hiện lại việc load singleton.

	//Chúng ta tạo ra 2 GameMap : Một sáng một tối dùng để chuyển khi bật đèn sáng/tối.
	world = new GameMap(world01BossTileLight, world01BossMapLight, world01BossMapObject, MapName::CHARLESBOSSLIGHT);
	worldDark = new GameMap(world01BossTileDark, world01BossMapDark, world01BossMapObject, MapName::CHARLESBOSSDARK);

	world->SetCamera(camera);
	worldDark->SetCamera(camera);

	//mapStaticObject = world->getStaticObject(); //Lấy entity của tất cả các object có trong map.

	currentWorld = world;
	isLightOn = true;

	//Xét tạo Grid.
	grid = new Grid(world->getMapWidth(), world->getMapHeight(), world01BossSpawn, world01BossMapObject);
	//Thêm player và shield vào Grid.
	/*grid->Add(BossWizard::getInstance());*/
	bulletAppearDelay = new Delay(3000);
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
	player->pos.x = 10;
	player->pos.y = SCREEN_HEIGHT - 10;
	player->ChangeState(State::JUMPING);
	player->SetOnAirState(Player::OnAir::Falling);
	player->ResetGameProperty();
	//Update lại camera sau khi set.
	UpdateCameraWithPlayerPos();
}

void PlaySceneCharlesBoss::Update(double dt)
{
	PlaySceneWithLight::Update(dt);

	//Test phím bật/tắt đèn.
	if (KeyboardManager::getInstance()->getKeyPressedOnce(DIK_L))
		TurnOnOffLight();

	//Test phím qua màn.
	if (KeyboardManager::getInstance()->getKeyPressedOnce(DIK_Q))
	{
		GoToNextScene();
	}
	//Kiểm tra xem player đã đi đến đích chưa.
	/*if (player->pos.x > SCREEN_WIDTH - 50)
	{
		GoToNextScene();
	}*/
	if (noOfSpawnedObject < 4 && bulletAppearDelay->GetDelayStatus(dt))
	{
		if (noOfSpawnedObject < 3)
		{
			BulletWizardNormal* bullet;
			int bulletX;
			int bulletY;
			float bulletSpeed = BossWizard::getInstance()->bulletSpeed;
			float bulletVX;
			float bulletVY;
			int bulletXToPlayerX;
			int bulletYToPlayerY;
			double degree;

			//Đạn được sinh ra ở phía bên phải.
			if (isRightBullet)
			{
				bulletX = 256 - 10;
				bulletY = 64;
				isRightBullet = false;
				bulletXToPlayerX = player->pos.x - bulletX;
				bulletYToPlayerY = player->pos.y - bulletY;
				degree = atan2(bulletYToPlayerY, bulletXToPlayerX);
				if (degree < 0)
					degree = PI;
				else if (degree < 3 * PI / 4)
					degree = 3 * PI / 4;
				else if (degree < 8 * PI / 9)
				{
					double toUpperDegree = degree - 3 * PI / 4;
					double toLowerDegree = 8 * PI / 9 - degree;
					if (toUpperDegree > toLowerDegree)
						degree = 8 * PI / 9;
					else
						degree = 3 * PI / 4;
				}
				else if (degree < PI)
				{
					double toUpperDegree = degree - 8 * PI / 9;
					double toLowerDegree = PI - degree;
					if (toUpperDegree > toLowerDegree)
						degree = PI;
					else
						degree = 8 * PI / 9;
				}
			}
			//Đạn được sinh ra ở phía bên trái.
			else
			{
				bulletX = 10;
				bulletY = 64;
				isRightBullet = true;
				bulletXToPlayerX = player->pos.x - bulletX;
				bulletYToPlayerY = player->pos.y - bulletY;
				degree = atan2(bulletYToPlayerY, bulletXToPlayerX);
				if (degree < 0)
					degree = 0;
				else if (degree > PI / 4)
					degree = PI / 4;
				else if (degree > PI / 9)
				{
					double toUpperDegree = PI / 4 - degree;
					double toLowerDegree = degree - PI / 9;
					if (toUpperDegree > toLowerDegree)
						degree = PI / 9;
					else
						degree = PI / 4;
				}
				else if (degree > 0)
				{
					double toUpperDegree = PI / 9 - degree;
					double toLowerDegree = degree;
					if (toUpperDegree < toLowerDegree)
						degree = PI / 9;
				}
			}

			bulletVX = cos(degree) * bulletSpeed;
			bulletVY = sin(degree) * bulletSpeed;
			bullet = new BulletWizardNormal();
			bullet->pos.x = bulletX;
			bullet->pos.y = bulletY;
			bullet->SetVx(bulletVX);
			bullet->SetVy(bulletVY);
			double absDegree = atan2(abs(bulletYToPlayerY), abs(bulletXToPlayerX));
			if (absDegree < (double)PI / 20)
				bullet->animation = bullet->animation3;
			else if (absDegree < (double)PI / 4)
				bullet->animation = bullet->animation2;
			else
				bullet->animation = bullet->animation1;
			grid->Add(bullet);
			++noOfSpawnedObject;
		}
		else
		{
			Object* newObject = BossWizard::getInstance();
			grid->Add(newObject);
			++noOfSpawnedObject;
		}
	}
}

void PlaySceneCharlesBoss::GoToNextScene()
{
	Done = true;
	ReplaceToThisMap = MapName::PITTSBURGHDARK;
}