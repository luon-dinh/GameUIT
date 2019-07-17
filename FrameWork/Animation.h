#pragma once
#include"SpriteManager.h"
#include"Sprite.h"

typedef Sprite::TransformationMode TransformationMode;

class Animation {
private:
	int toframe;
	int  tiperframe;
	int ticurframe;
	std::vector<Sprite*>sprites;
	Tag tag;
public:
	~Animation();
	Animation() {};
	Animation(Tag tag, int idex);
	Animation(Tag tag, int first, int last, int tipeframe=TIME_PER_FRAME);
	Sprite* getSprite(int index);
	void Update(float dt);
	void Render(D3DXVECTOR2 pos);
	void Render(float x, float y);
	void Render(D3DXVECTOR3 pos);
	void Render(float x, float y, int first, int last);
	void Render(D3DXVECTOR2 pos, TransformationMode transMode, float scaleRatio = 1.0f);
	void ReplaceSprite(int index, Sprite* sprite);//thay đổi sprite bất kì trong sprites của naimation
	int curframeindex;
	int getWidth();
	int getHeight();
};

