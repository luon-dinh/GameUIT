#pragma once
#include"Sprite.h"

class SpriteManager {
private:
	static SpriteManager* instance;
	std::unordered_map<Tag, std::vector<Sprite*>> sprites;
public:
	void LoadResources();
	static SpriteManager* getInstance();
	void addSprite(Sprite *);
	Sprite* getSprite(Tag tag, int index);
	std::vector<Sprite*> getSprites(Tag tag, int first, int last);
};