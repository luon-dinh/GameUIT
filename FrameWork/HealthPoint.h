#include "MapStaticObject.h"
#include "Camera.h"

class HealthPoint : public MapStaticObject {
private:
	Animation* animation;
	int numberOfHP;
	int currentFlipFrame;
	bool renderFlip;

	void InnerRender();
	
	const int FLIP_FRAME = 20;
	const int MIN_FLIP_HP = 1;

	HealthPoint();
	~HealthPoint();

	static HealthPoint* instance;
public:

	static HealthPoint* getInstance();
	static void releaseInstance();

	void Update(int hp);
	void Render() override;

};