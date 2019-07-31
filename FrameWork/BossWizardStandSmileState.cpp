#include"BossWizardStandSmileState.h"

BossWizardStandSmileState::BossWizardStandSmileState()
{

}
BossWizardStandSmileState::~BossWizardStandSmileState()
{

}

void BossWizardStandSmileState::InputHandler()
{

}

void BossWizardStandSmileState::Update(float dt)
{
	auto player = Player::getInstance();
	auto wizard = BossWizard::getInstance();
	if (player->GetOnAirState() != BossWizard::OnAir::None)
		wizard->ChangeState(State::ATTACK);
}
