#include "DebuffPickup.h"
//constructor
DebuffPickup::DebuffPickup()
{
	GameSetup();
}
//deconstructor
DebuffPickup::~DebuffPickup() {}

/**
 * @brief sets default values for item
 * Width, Height and Texture
*/
void DebuffPickup::GameSetup()
{
	SetTexture("data/46-Breakout-Tiles.png");
	SetSize(itemWidth, itemHeight);
}
/**
 * @brief changing status of pickup item
 * @param playerPlatform -platform that it aplies to 
*/
void DebuffPickup::DestroyOnContact(PlayerPlatform* playerPlatform)
{
	if(bIsPickupAlive)
	ApplyEffect(playerPlatform);
	bIsPickupAlive = false;
}
/**
 * @brief applies effect of Debuff
 * @param playerPlatform -platform that it aplies to
*/
void DebuffPickup::ApplyEffect(PlayerPlatform* playerPlatform)
{
	playerPlatform->DecreaseSize();
}
//getters
int DebuffPickup::GetPickupXLocation()
{
	return SpriteRect.XLocation;
}
int DebuffPickup::GetPickupYLocation()
{
	return SpriteRect.YLocation;
}