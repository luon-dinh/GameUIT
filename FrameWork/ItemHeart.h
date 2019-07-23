#include"Item.h"
class ItemHeart :public Item {
public:
	ItemHeart()
	{
		sprite = animation->getSprite(6);
	}
};