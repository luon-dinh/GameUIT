#include "ExitSignal.h"

ExitSignal* ExitSignal::instance = NULL;

ExitSignal::ExitSignal() {
	this->isActive = false;
	this->currentFlipFrame = 0;
	this->animation = new Animation(Tag::EXITSIGN, 0);
}

ExitSignal* ExitSignal::getInstance() {
	if (instance == NULL) {
		instance = new ExitSignal();
	}
	return instance;
}

void ExitSignal::releaseInstance() {
	delete instance;
}

ExitSignal::~ExitSignal() {
	//delete animation;
}

void ExitSignal::Render() {
	if (!this->GetActive()) {
		return;
	}

	this->currentFlipFrame++;

	if (this->currentFlipFrame < FLIP_FRAME / 2) {
		return;
	}
	else {
		this->InnerRender();
		if (this->currentFlipFrame == FLIP_FRAME) {
			this->currentFlipFrame = 0;
		}
	}
}

void ExitSignal::InnerRender() {
	animation->Render(60, 23);
}