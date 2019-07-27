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
	addItem(new Item(ItemType::UP));
	addItem(new Item(ItemType::HP));
	addItem(new Item(ItemType::STAR));
	addItem(new Item(ItemType::GEM));
	addItem(new Item(ItemType::SMALLGEM));
	addItem(new Item(ItemType::EXIT));
	addItem(new Item(ItemType::HEART));
	addItem(new Item(ItemType::HALFHEART));
}

Item* ItemManager::getItem(int index)
{
	return items[index];
}