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
	int currentFrameIndex = wizard->curanimation->curframeindex;
	int maxFrameIndex = wizard->curanimation->toframe;
	if (currentFrameIndex == maxFrameIndex - 2)
	{
		auto scene = SceneManager::getInstance();
		auto bullet = new BulletWizardNormal();
		auto box = wizard->getBoundingBox();
		bullet->direction = wizard->direction;
		bullet->pos.y = box.top - 6;
		bullet->vy = 0;
		switch (bullet->direction)
		{
		case BossWizard::MoveDirection::LeftToRight:
			bullet->vx = 1.5;
			bullet->pos.x = box.right;
			break;
		case BossWizard::MoveDirection::RightToLeft:
			bullet->vx = -1.5;
			bullet->pos.x = box.right;
			break;
		default:
			break;
		}
		scene->AddObjectToCurrentScene(bullet);
	}
	else
	{
		if (currentFrameIndex == maxFrameIndex - 1)
		{
			auto player = Player::getInstance();
			float deltaPlayer = abs(player->pos.x - wizard->pos.x);
			if (deltaPlayer >= 100)
			{
				if (deltaPlayer > 130)
				{
					wizard->flyMode = 2;
					wizard->ChangeState(State::FLYING);
					return;
				}
				wizard->ChangeState(State::RUNNING);
			}
			else
			{
				if (deltaPlayer < 30)
				{
					if (wizard->pos.x < 15 || wizard->pos.x>230)
					{
						wizard->flyMode = 3;
						wizard->ChangeState(State::FLYING);
					}
					wizard->ChangeState(State::STAND_PUNCH);
				}
				else
				{
					if(wizard->pos.x < 25 || wizard->pos.x>210)
						wizard->flyMode = 3;
					else
					{
						wizard->flyMode = 1;
					}
					wizard->ChangeState(State::FLYING);
				}
			}
		}
	}

}
