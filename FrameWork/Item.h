#include"Object.h"
class Item:public Object {
private:

public:
	BOOL isActive;
	void Update(float dt);
	virtual BoundingBox getBoundingBox();
	Animation* animation = new Animation(Tag::ITEM, 0, 8);
	Sprite* sprite;
	virtual void Render();
	//Hàm dùng để xác định xem liệu object có được render trong grid không ?
	//Mặc định là sẽ được Render. Những object cần render theo kiểu đặc biệt thì ta override lại và để trống.
	virtual void RenderInGrid() { Render(); };
	virtual void OnCollision(Object* object, collisionOut* colOut);
	virtual void Update(float dt);
	Item(int frameindex,D3DXVECTOR2 pos);
	Item() {};
	~Item();
};