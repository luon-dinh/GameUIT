#pragma once
#include "GameObjectProperty.h"
#include "Item.h"
#include "ExitSignal.h"

class GamePlayerProperty : public GameObjectProperty {
protected:
	int score;
	int gems;
	int nonAttackableFrameCount;
	int maxNonAttackableFrames;
	int power;
	
	int maxiableHeart;		// số lượng máu tối đa của player
	int damageAccelerator;	// lượng damage được cộng thêms

	bool isNonAttackable;
	bool isNearlyDead;
	bool isDead;
	bool canGoToNextScene;

	void IncreaseHealth(int value);
	void LoseHealth(int value);
	void UpdateNonAttackableState();
	
	void GemUp(int gems = 1);
	void SetHealth(int health) override;


	const int MAX_NON_ATTACKABLE_FRAME = 105;
	const int HEALTH_PER_HEART = 4;
	const int MAX_HEART_DEFAULT = 5;
	const int SCORE_PER_STAR = 3;
	const int GEM_PER_HEART = 2;
	const int MAX_POWER = 10;
	// lượng damage tăng thêm khi loot đủ gem
	const int DAMAGE_ACCELERATOR = 1;
	// lượng gem cân loot để power Up
	const int POWER_UP_LOOTED_GEM = 10;
public:
	GamePlayerProperty();
	~GamePlayerProperty();

	virtual bool IsNonAttackable();
	virtual bool IsImmortal();
	virtual void SetToImmortalState();				// Chuyển sang trạng thái bất tử
	virtual void SetToNonAttackableState(int frames = 105);
	virtual void SetToNormalState();				// Chuyển sang trạng thái bình thường

	void ScoreUp(int scores = 1);
	bool IsNearlyDead();
	bool CanGoNextScene();
	int GetHeart();									// Lấy trái tim để render
	int GetScore();
	void SetHeart(int heart);						// Set lại máu cho player
	int GetCurrentGem();							// Get số gem đã loot được hiện tại
	void ResetTransScene();
	void LootItem(Item* item);						//	 khi va chạm với item thì loot item đó
	void UpdateGameProperty()				 override;
	void ResetGameProperty()				 override;
	void BeingAttacked(int objectDamage)	 override;
	virtual int GetDamage() 				 override;
};