#pragma once
#include "MapStaticObject.h"

class ExitSignal : public MapStaticObject {
private:
	Animation* animation;
	int currentFlipFrame;

	void InnerRender();

	const int FLIP_FRAME = 50;

	ExitSignal();
	~ExitSignal();

	static ExitSignal* instance;
public:

	static ExitSignal* getInstance();
	static void releaseInstance();
	void Render() override;

};