#include"BossWizardFlyingState.h"
#include"SceneManager.h"
BossWizardFlyingState::BossWizardFlyingState()
{

}
BossWizardFlyingState::~BossWizardFlyingState()
{

}

void BossWizardFlyingState::InputHandler()
{

}

void BossWizardFlyingState::Fly(float dt)
{
	auto wizard = BossWizard::getInstance();
	auto player = Player::getInstance();

	//cập nhật đội dời khi bay
	wizard->deltaY += abs(wizard->vy);
	wizard->deltaX += abs(wizard->vx);

	//nếu fly mode1  thì cập nhật vx theo hướng


	
	if(wizard->flyMode!=1)
	{
		wizard->hitTime = 0;
	}
	//cập nhật theo từng trạng thái khi bay
	switch (wizard->GetOnAirState())
	{
	case BossWizard::OnAir::Falling:
		wizard->currentanimation->curframeindex = 1;
		wizard->vy = -wizard->flySpeedy;
		if (wizard->flyMode != 1)
			wizard->vx = 0;
		break;
	case BossWizard::OnAir::Jumping:
		if(wizard->flyMode!=1)
			wizard->vx = 0;
		wizard->vy = wizard->flySpeedy;
		wizard->currentanimation->curframeindex = 0;
		if (wizard->flyMode == 1&& wizard->deltaY >= maxFly1)
		{
			wizard->deltaY = 0;
			wizard->vy = 0;
			wizard->SetOnAirState(BossWizard::OnAir::Falling);
			return;
		}
		else if (wizard->pos.y >mapHeight-wizard->height)
		{
			wizard->vy = 0;
			wizard->SetOnAirState(BossWizard::OnAir::None);
		}
		break;
	case BossWizard::OnAir::None:
		wizard->currentanimation->curframeindex = 2;
		if (wizard->flyMode == 2&&wizard->deltaX>maxFlyx2)
		{
			wizard->SetOnAirState(BossWizard::OnAir::Falling);
			return;
		}
		// nếu nó có thể tắt đèn thì rớt xuống tắt đèn
		if (wizard->turnOffLight)
		{
			if (abs(wizard->pos.x - 70) < 5 && SceneManager::getInstance()->IsLightOn())
			{
				wizard->SetOnAirState(BossWizard::OnAir::Falling);
				return;
			}

		}
		if (abs(player->pos.x-wizard->pos.x)<5 && wizard->canShootOnAir)
		{
			//bắn xuống rồi return
			auto scene = SceneManager::getInstance();
			auto bullet = new BulletWizardSpecial();
			bullet->vx = 0;
			bullet->vy = -wizard->bulletSpeed;
			bullet->animation = bullet->animation3;
			if (wizard->direction == BossWizard::MoveDirection::LeftToRight)
				bullet->pos.x = wizard->pos.x + wizard->width / 2;
			else
			{
				bullet->pos.x = wizard->pos.x - wizard->width / 2;
			}
			bullet->pos.y = wizard->pos.y - wizard->height / 2;
			scene->AddObjectToCurrentScene(bullet);
			wizard->canShootOnAir = false;
			return;
		}
		//cập nhật speed của boss theo direction
		if (wizard->direction == BossWizard::MoveDirection::LeftToRight)
		{
			wizard->vx = wizard->flySpeedx2;
			if ((wizard->pos.x + wizard->width/2 - player->pos.x) < 1.5)
			{
				wizard->canShootOnAir = true;
			}
		}
		else
		{
			wizard->vx = -wizard->flySpeedx2;
			if (abs(wizard->pos.x - wizard->width / 2 - player->pos.x) < 1.5)
			{
				wizard->canShootOnAir = true;
			}
		}
		break;
	default:
		break;
	}
}

void BossWizardFlyingState::Update(float dt)
{
	auto wizard = BossWizard::getInstance();
	// nếu xuống min hoặc max map thì rớt
	if ((wizard->pos.x < wizard->minMap+wizard->getWidth()/2 || wizard->pos.x>wizard->maxMap-wizard->getWidth()/2)&&wizard->deltaX>2)
	{
		if (wizard->flyMode == 1)
		{
			wizard->flyMode == 3;
		}
		wizard->SetOnAirState(BossWizard::OnAir::Falling);
	}
	Fly(dt);
}
