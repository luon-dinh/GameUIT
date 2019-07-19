#pragma once
#include"PlayerState.h"
#include"Player.h"

class PlayerStandingState: public PlayerState {
private:
	enum BeforeDash {
		DashLeft,
		DashRight,
		None
	};

	BeforeDash befDash;
	int frameFlip;		// frame
	BOOL flipStart;

	int MAX_FRAME_FLIP = 5;
public:

	PlayerStandingState();
	~PlayerStandingState() {};
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;
	void InputHandler() override;
	BOOL ChangeToDash(BeforeDash currentDash);
	void ResetFrameFlip();
	void StopFrameFlip();
	BoundingBox getBoundingBox();
	
};
