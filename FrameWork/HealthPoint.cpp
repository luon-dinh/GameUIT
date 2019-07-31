#include "HealthPoint.h"

HealthPoint* HealthPoint::instance = NULL;

HealthPoint::HealthPoint() {
	this->numberOfHP = 0;
	this->renderFlip = false;
	this->currentFlipFrame = 0;
	this->animation = new Animation(Tag::HP_RENDER, 0);
}

HealthPoint* HealthPoint::getInstance() {
	if (instance == NULL) {
		instance = new HealthPoint();
	}
	return instance;
}

void HealthPoint::releaseInstance() {
	delete instance;
}

HealthPoint::~HealthPoint() {

}

void HealthPoint::Update(int hp) {
	this->numberOfHP = hp;
	if (this->numberOfHP == MIN_FLIP_HP) {
		this->renderFlip = true;
	}

}

void HealthPoint::Render() {
	if (!this->renderFlip) {
		this->InnerRender();
		this->currentFlipFrame = 0;
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

void HealthPoint::InnerRender() {
	int curX = 28, curY = 20;
	for (int i = 1;i <= numberOfHP;i++) {
		animation->Render(curX, curY);
		curY += 8;
	}
}