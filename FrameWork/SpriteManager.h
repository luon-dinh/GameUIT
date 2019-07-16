#pragma once
#include "Global.h"
#include"Sprite.h"

class SpriteManager {
private:
	static SpriteManager* instance;
	std::unordered_map<Tag, std::vector<Sprite*>> sprites;
public:
	void LoadResources();
	static SpriteManager* getInstance();
	void addSprite(Sprite *);
	void addSprite(Tag tag, int rowindex, int numberofsprites);
	Sprite* getSprite(Tag tag, int index=0);
	std::vector<Sprite*> getSprites(Tag tag, int first, int last);
};