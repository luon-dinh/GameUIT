#pragma once
#include"Global.h"
class PlayerState {
public:
	State state;
	PlayerState() {};
	virtual void InputHandler() {};
	virtual void Update(float dt) {};
};
