#pragma once
#include "PickupItem.h"
class BuffPickup :
    public PickupItem
{
public:
    virtual void GameSetup() override;

    //Pickup Logic
    virtual void DestroyOnContact(PlayerPlatform* playerPlatform) override;
    virtual void ApplyEffect(PlayerPlatform* playerPlatform) override;

    //Getters
    virtual int GetPickupXLocation() override;
    virtual int GetPickupYLocation() override;
    
    //Constructor
    BuffPickup();

    //Deconstructor
    ~BuffPickup();
};

