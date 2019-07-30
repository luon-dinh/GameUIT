#include"BossWizardShootingState.h"
#include"BulletWizardNormal.h"
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
	if (currentFrameIndex == maxFrameIndex - 1)
		wizard->ChangeState(State::STANDING);
	else
	{
		if (currentFrameIndex == 1)
		{
			auto scene = SceneManager::getInstance();
			auto bullet = new BulletWizardNormal();
			auto box = wizard->getBoundingBox();
			bullet->direction = wizard->direction;
			bullet->pos.y = box.top - 6;
			switch (bullet->direction)
			{
			case BossWizard::MoveDirection::LeftToRight:
				bullet->pos.x = box.right;
				break;
			case BossWizard::MoveDirection::RightToLeft:
				bullet->pos.x = box.right;
				break;
			default:
				break;
			}
			scene->AddObjectToCurrentScene(bullet);
		}
	}
}
