#include"BossWizardShootingState.h"
#include"SceneManager.h"
BossWizardShootingState::BossWizardShootingState()
{
	timeShoot = 0;
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
	if (timeShoot < maxTimeShoot)
	{
		timeShoot += wizard->defaultDT;
	}
	else
	{
		timeShoot = 0;
		if (wizard->countBullet == 2&& (wizard->hitTime!=0||wizard->flyTimes>0))
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
			wizard->countBullet++;
			wizard->ChangeState(State::STANDING);
			return;
		}
		else if (wizard->countBullet == 3)
		{
			wizard->countBullet = 0;
			if (wizard->flyTimes > 0)
			{
				wizard->flyTimes--;
				wizard->flyMode = rand() % 3 + 2;
				wizard->ChangeState(State::FLYING);
				wizard->hitTime = 0;
				return;
			}
			auto player = Player::getInstance();
			float deltaPlayer = abs(player->pos.x - wizard->pos.x);
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
				wizard->flyMode = 1;
				wizard->ChangeState(State::FLYING);
			}
			else
			{
				wizard->ChangeState(State::RUNNING);
			}
			return;
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
			wizard->countBullet++;
			wizard->ChangeState(State::STANDING);
			scene->AddObjectToCurrentScene(bullet);
		}
	}
}
