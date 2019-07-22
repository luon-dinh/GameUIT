#include"ItemManager.h"

ItemManager* ItemManager::instance = NULL;

ItemManager::ItemManager()
{
	LoadAllItem();
}

ItemManager::~ItemManager()
{
	for (auto it : items)
		it = nullptr;
	items.clear();
}

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
	addItem(new Item(Type::ITEM1));
	addItem(new Item(Type::ITEM2));
	addItem(new Item(Type::ITEM3));
	addItem(new Item(Type::ITEM4));
	addItem(new Item(Type::ITEM5));
	addItem(new Item(Type::ITEM6));
	addItem(new Item(Type::ITEM7));
	addItem(new Item(Type::ITEM8));
}

Item* ItemManager::getItem(int index)
{
	return items[index];
}