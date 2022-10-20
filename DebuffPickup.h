#pragma once
#include "PickupItem.h"
class DebuffPickup :
    public PickupItem
{
public:
    virtual void GameSetup() override;

    //Pickup Logic
    virtual void DestroyOnContact(PlayerPlatform* playerPlatform) override;
    virtual void ApplyEffect(PlayerPlatform* playerPlatform) override;

    //getters
    virtual int GetPickupXLocation() override;
    virtual int GetPickupYLocation() override;

    //Constructor
    DebuffPickup();

    //Deconstructor
    ~DebuffPickup();
};

