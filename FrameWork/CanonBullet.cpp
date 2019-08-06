#include "CanonBullet.h"


CanonBullet::CanonBullet(MoveDirection direction) : BulletSolder(direction){
	this->animation = new Animation(Tag::GREENCANNONBULLET, 0);
	this->tag = Tag::GREENCANNONBULLET;
	this->type = Type::BULLETTYPE;
}
