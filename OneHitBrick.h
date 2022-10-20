#pragma once
#include "BricksGeneral.h"
class OneHitBrick :
    public BricksGeneral
{
private:
	//Brick health Variables
	int health;
	const int maxHealth = 1;

public:

	virtual void GameSetup(int BlockWidth, int BlockHeight) override;

	//Brick logic
	virtual void TakenDamage() override;
	virtual void OverlapWithBall(Ball* ballInstance, int& score, int& combo, int& killedBricks, int ScreenWidth,PickupItem* pickupItem) override;


	//getters
	virtual int GetHealth() override;
	virtual int GetXLocation() override;
	virtual int GetYLocation() override;

	virtual bool isBrickDead() override;
	
	//constructor
	OneHitBrick(int BlockWidth, int BlockHeight);

	//deconstructor
	~OneHitBrick();
};

