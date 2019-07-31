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
			bullet->vx = ENEMY_BULLET_SPEED*3;
			bullet->pos.x = box.right;
			break;
		case BossWizard::MoveDirection::RightToLeft:
			bullet->vx = -ENEMY_BULLET_SPEED*3;
			bullet->pos.x = box.left;
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
			if (deltaPlayer >= wizard->xRun)
			{
				wizard->ChangeState(State::RUNNING);
			}
			else
			{
				if (deltaPlayer < wizard->xPunch&&player->GetOnAirState()==BossWizard::OnAir::None)
				{
					wizard->ChangeState(State::STAND_PUNCH);
				}
				else
				{
					wizard->flyMode = 1;
					wizard->ChangeState(State::FLYING);
				}
			}
		}
	}

}
