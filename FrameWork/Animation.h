#pragma once
#include"SpriteManager.h"
#include"Sprite.h"

class Animation {
private:
	int toframe;
	int  tiperframe;
	int ticurframe;
	std::vector<Sprite*>sprites;
public:
	~Animation();
	Animation() {};
	Animation(Tag tag, int idex);
	Animation(Tag tag, int first, int last, int tipeframe=TIME_PER_FRAME);
	Sprite* getSprite(int index);
	void Update(float dt);
	void Render(float x, float y);
	void Render(float x, float y, int first, int last);
	int curframeindex;
};

