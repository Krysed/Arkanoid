#pragma once
#include "SpritesLogic.h"
#include "PlayerPlatform.h"
class PickupItem :
    public SpritesLogic
{
private:
protected:
    //Item Variables
    bool bIsPickupAlive = false;
    
    float yAxisMovement = 1;
    int itemWidth = 50;
    int itemHeight = 20;
public:
    //platform instance pointer for usage in functions
    PlayerPlatform* playerPlatform;

    virtual void GameSetup() = 0;

    //Pickup Logic
    virtual void DestroyOnContact(PlayerPlatform* playerPlatform)       = 0;
    virtual void ApplyEffect(PlayerPlatform* playerPlatform)            = 0;
    void Movement();

    //getters
    virtual int GetPickupXLocation()    = 0;
    virtual int GetPickupYLocation()    = 0;
    bool  IsPickupAlive();

    //Setter
    void SetIsPickupAlive(bool state);

    //Constructor
    PickupItem();

    //Deconstructor
    ~PickupItem();
};

