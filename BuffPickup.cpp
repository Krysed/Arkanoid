#include "BuffPickup.h"

//constructor
BuffPickup::BuffPickup()
{
	GameSetup();
}
//deconstructor
BuffPickup::~BuffPickup() {}

/**
 * @brief sets default values for item
 * Width, Height and Texture
*/
void BuffPickup::GameSetup()
{
	SetTexture("data/47-Breakout-Tiles.png");
	SetSize(itemWidth, itemHeight);
}

/**
 * @brief changing status of item
 * @param playerPlatform - what does it touches
*/
void BuffPickup::DestroyOnContact(PlayerPlatform* playerPlatform)
{
	if(bIsPickupAlive)
	ApplyEffect(playerPlatform);
	bIsPickupAlive = false;
}

/**
 * @brief applies effect of the buff
 * @param playerPlatform -platform that it applies to
*/
void BuffPickup::ApplyEffect(PlayerPlatform* playerPlatform)
{
	playerPlatform->IncreaseSize();
}

//getters
int BuffPickup::GetPickupXLocation()
{
	return SpriteRect.XLocation;
}
int BuffPickup::GetPickupYLocation()
{
	return SpriteRect.YLocation;
}