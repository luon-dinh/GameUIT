#include "Delay.h"

Delay::Delay(float _delayInterval)
{
	delayInterval = _delayInterval;
	currentTick = 0;
}

bool Delay::GetDelayStatus(float dt)
{
	if (currentTick > delayInterval)
	{
		currentTick = 0;
		return true;
	}
	currentTick += dt;
	return false;
}