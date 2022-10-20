#pragma once
#include "SpritesLogic.h"
#include "Ball.h"
#include "DebuffPickup.h"
#include "BuffPickup.h"

class BricksGeneral :
    public SpritesLogic
{
private:
protected:
    bool bIsBrickDead = true;
public:
    BuffPickup* buffPickup;
    DebuffPickup* debuffPickup;

    int BlockWidthVar=0;
    int BlockHeightVar=0;

    //pure virtual functions for every brick
    virtual void GameSetup(int BlockWidth, int BlockHeight) = 0;

    //Brick Logic
    virtual void TakenDamage() = 0;
    virtual void OverlapWithBall(Ball* ballInstance, int& score, int& combo, int& killedBricks, int ScreenWidth, PickupItem* pickupItem) = 0;

    //getters
    virtual int GetHealth() = 0;
    virtual int GetXLocation() = 0;
    virtual int GetYLocation() = 0;

    virtual bool isBrickDead() = 0;

    //Constructor
    BricksGeneral();

    //Deconstructor
    ~BricksGeneral();
};

