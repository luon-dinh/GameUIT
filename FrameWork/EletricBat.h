#include "EvilBat.h"

class EletricBat : public EvilBat {
protected:
	void LoadAllAnimations() override;
public:
	EletricBat(D3DXVECTOR2 pos);
	~EletricBat();
};