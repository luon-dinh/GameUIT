#include"BossWizardShootingState.h"
#include"SceneManager.h"
BossWizardShootingState::BossWizardShootingState()
{
	
}
BossWizardShootingState::~BossWizardShootingState()
{

}

void BossWizardShootingState::InputHandler()
{

}

void BossWizardShootingState::Update(float dt)
{
	auto wizard = BossWizard::getInstance();
	auto player = Player::getInstance();


	//thời gian shoot 3 viên
	if (wizard->timeToShoot>0)
	{
		if (wizard->delayShoot>=300)
		{
			//bắt đầu bắn
			//nếu là viên thứ 3 của trạng thái rơi từ trên cao xuống
			if (wizard->timeToShoot < 100&& wizard->flyMode != 1)
			{
				auto scene = SceneManager::getInstance();
				auto bullet = new BulletWizardSpecial ();
				auto box = wizard->getBoundingBox();
				bullet->animation = bullet->animation1;
				bullet->direction = wizard->direction;
				bullet->pos.y = wizard->pos.y + 10;
				bullet->vy = 0;
				switch (bullet->direction)
				{
				case BossWizard::MoveDirection::LeftToRight:
					bullet->vx = ENEMY_BULLET_SPEED * 3;
					bullet->pos.x = box.right;
					break;
				case BossWizard::MoveDirection::RightToLeft:
					bullet->vx = -ENEMY_BULLET_SPEED * 3;
					bullet->pos.x = box.left;
					break;
				default:
					break;
				}
				scene->AddObjectToCurrentScene(bullet);
				wizard->delayShoot = 0;
			}
			else
			{
				auto scene = SceneManager::getInstance();
				auto bullet = new BulletWizardNormal();
				auto box = wizard->getBoundingBox();
				bullet->animation = bullet->animation3;
				bullet->direction = wizard->direction;
				bullet->pos.y = wizard->pos.y + 10;
				
				switch (bullet->direction)
				{
				case BossWizard::MoveDirection::LeftToRight:
					bullet->vx = ENEMY_BULLET_SPEED * 2.5;
					bullet->pos.x = box.right;
					break;
				case BossWizard::MoveDirection::RightToLeft:
					bullet->vx = -ENEMY_BULLET_SPEED * 2.5;
					bullet->pos.x = box.left;
					break;
				default:
					break;
				}
				float delta = abs(wizard->pos.y - player->pos.y);
				if (delta < wizard->shoot1)
					bullet->vy = 0;
				else
				{
					if (delta < wizard->shoot2)
					{
						bullet->vy = abs(bullet->vx) * 1 / 3;
						bullet->animation = bullet->animation2;
					}
					else
					{
						bullet->vy = abs(bullet->vx) * 2 / 3;
						bullet->animation = bullet->animation1;
					}
				}
				scene->AddObjectToCurrentScene(bullet);
				wizard->delayShoot = 0;
			}
		}
		else
		{
			wizard->delayShoot += wizard->defaultDT;
		}
		wizard->timeToShoot -= wizard->defaultDT;
	}
	else
	{
		wizard->timeToShoot = wizard->maxTimeToShoot;
		if (wizard->flyTimes > 0)
		{
			wizard->flyMode = rand() % 3 + 2;
			wizard->ChangeState(State::FLYING);
			wizard->flyTimes--;
			wizard->hitTime = 0;
			wizard->timeToShoot = 1080;
			wizard->delayShoot = 0;
			return;
		}
		auto player = Player::getInstance();
		float deltaPlayer = abs(player->pos.x - wizard->pos.x);
		//nếu gần player, bắn rồi nhảy
		if (deltaPlayer < wizard->maxXToFly1)
		{
			auto scene = SceneManager::getInstance();
			auto bullet = new BulletWizardSpecial();
			auto box = wizard->getBoundingBox();
			bullet->animation = bullet->animation1;
			bullet->direction = wizard->direction;
			bullet->pos.y = wizard->pos.y + 10;
			bullet->vy = 0;
			switch (bullet->direction)
			{
			case BossWizard::MoveDirection::LeftToRight:
				bullet->vx = ENEMY_BULLET_SPEED * 3;
				bullet->pos.x = box.right;
				break;
			case BossWizard::MoveDirection::RightToLeft:
				bullet->vx = -ENEMY_BULLET_SPEED * 3;
				bullet->pos.x = box.left;
				break;
			default:
				break;
			}
			scene->AddObjectToCurrentScene(bullet);
			wizard->delayShoot = 0;
			wizard->flyMode = 1;
			wizard->ChangeState(State::FLYING);
		}
		else
		{
			wizard->ChangeState(State::RUNNING);
		}
	}
}
