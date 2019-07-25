#include"Object.h"
#include"Collision.h"
class Item:public Object {
private:

public:
	int countFrame;
	int existTime;
	void Update(float dt);
	BoundingBox getBoundingBox()override;

	Animation* animation;
	void Render();
	//Hàm dùng để xác định xem liệu object có được render trong grid không ?
	//Mặc định là sẽ được Render. Những object cần render theo kiểu đặc biệt thì ta override lại và để trống.
	virtual void RenderInGrid() { Render(); };
	void OnCollision(Object* object, collisionOut* colOut)override;
	Item(Type type);
	Item() {};
	~Item();
};