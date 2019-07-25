#include"ItemManager.h"

ItemManager* ItemManager::instance = NULL;


ItemManager* ItemManager::getInstance()
{
	if (!instance)
		instance = new ItemManager();
	return instance;
}

void ItemManager::addItem(Item* item)
{
	items.push_back(item);
}

void ItemManager::LoadAllItem()
{
	addItem(new Item(Type::UP));
	addItem(new Item(Type::HP));
	addItem(new Item(Type::STAR));
	addItem(new Item(Type::GEM));
	addItem(new Item(Type::SMALLGEM));
	addItem(new Item(Type::EXIT));
	addItem(new Item(Type::HEART));
	addItem(new Item(Type::HALFHEART));
}

Item* ItemManager::getItem(int index)
{
	return items[index];
}