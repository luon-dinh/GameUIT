#include"Item.h"

class ItemManager {
private:
	static ItemManager* instance;
public:
	std::vector<Item*>items;
	static ItemManager* getInstance();
	void LoadAllItem();
	ItemManager();
	~ItemManager();
	void addItem(Item *item);
	Item* getItem(int index);
};