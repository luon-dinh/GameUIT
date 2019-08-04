#include "EvilBat.h"

class EletricBat : public EvilBat {
protected:
	void LoadAllAnimations() override;

	const int WAKEN_UP_DISTANCE = 100;

	bool IsFlyAgain() override;
	void StopMoving() override;
public:
	EletricBat(D3DXVECTOR2 pos);
	~EletricBat();

	bool IsInImmortalState();

	bool IsWakenUpBy(Object* object) override;
	bool OnRectCollided(Object* object, CollisionSide side) override;
};