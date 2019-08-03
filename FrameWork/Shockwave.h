#pragma once
#include "Object.h"
#include "Delay.h"

class Shockwave : public Object
{
	//Thời gian delay cho sprite chớp chớp của shockwave.
	const int shockWaveFlashingDelayTime = 30;
	//Thời gian bật điện.
	const int timeEnabled = 3000;
	//Thời gian tắt điện.
	const int timeDisabled = 1000;

	Animation* waveAnim;
	Delay* enableDelay;
	Delay* disableDelay;

	bool isShockwaveActivated = false;
public:
	Shockwave(int posX, int posY);
	~Shockwave();
	void Update(float dt) override;
	void Render() override;
};