#include"BossWizardDeadState.h"
#include"SceneManager.h"

BossWizardDeadState::BossWizardDeadState()
{
	timeDead = 0;
}
BossWizardDeadState::~BossWizardDeadState()
{

}

void BossWizardDeadState::InputHandler()
{

}

void BossWizardDeadState::Update(float dt)
{
	auto wizard = BossWizard::getInstance();
	if (timeDead < maxTimeDead)
		timeDead += wizard->defaultDT;
	else
	{
		Player::getInstance()->ScoreUp(wizard->score);
		wizard->DeactivateObjectInGrid();
		SceneManager::getInstance()->GoToNextScene();
		//stop all sound in here
	}
}
