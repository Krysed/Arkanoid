#pragma once
#include "BricksGeneral.h"
class TwoHitBrick :
    public BricksGeneral
{
	//Brick Health variables
	int health;
	const int maxHealth = 2;

public:

	virtual void GameSetup(int BlockWidth, int BlockHeight) override;

	//Brick logic
	virtual void TakenDamage() override;
	virtual void OverlapWithBall(Ball* ballInstance, int& score, int& combo, int& killedBricks, int ScreenWidth, PickupItem* pickupItem) override;
	void SetDead();

	//getters
	virtual int GetHealth() override;
	virtual int GetXLocation() override;
	virtual int GetYLocation() override;

	virtual bool isBrickDead() override;

	//constructor
	TwoHitBrick(int BlockWidth, int BlockHeight);

	//deconstructor
	~TwoHitBrick();

};

