#pragma once
#include "BricksGeneral.h"
class IndestructibleBrick :
    public BricksGeneral
{
private:
	int health = 3;
public:

	virtual void GameSetup(int BlockWidth, int BlockHeight) override;

	//Brick Logic
	virtual void TakenDamage() override;
	virtual void OverlapWithBall(Ball* ballInstance, int& score, int& combo, int& killedBricks, int ScreenWidth,  PickupItem* pickupItem) override;


	//getters
	virtual int GetHealth() override;
	virtual int GetXLocation() override;
	virtual int GetYLocation() override;

	virtual bool isBrickDead() override;
	
	//constructor
	IndestructibleBrick(int BlockWidth, int BlockHeight);

	//deconstructor
	~IndestructibleBrick();
};

