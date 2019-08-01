#pragma once
#include"BulletSolder.h"
#include"BulletRedRockerter.h"
#include"BulletWhiteRockerter.h"

class BulletManager {
private:
	static BulletManager* instance;
public:
	static BulletManager* getInstance()
	{
		if (!instance)
			instance = new BulletManager();
		return instance;
	}
	static Bullet* CreateBullet(Tag tag)
	{
		switch (tag)
		{
		case Tag::BLUESOLDERBULLET:
			//return new BulletSolder(); phải truyền vào hướng của nó
		case Tag::REDROCKERTERBULLET:
			return new BulletRedRockerter();
		case Tag::WHITEROCKERTERBULLET:
			return new BulletWhiteRockerter();
		}
	}
};