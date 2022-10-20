#include "IndestructibleBrick.h"
#include <iostream>

//Constructor
IndestructibleBrick::IndestructibleBrick(int BlockWidth, int BlockHeight)
{
	GameSetup(BlockWidth, BlockHeight);
}
//Deconstructor
IndestructibleBrick::~IndestructibleBrick() {}

/**
 * @brief setting default values for Golden brick
*/
void IndestructibleBrick::GameSetup(int BlockWidth, int BlockHeight)
{
	BlockWidthVar = BlockWidth;
	BlockHeightVar = 30;
	SetTexture("data/13-Breakout-Tiles.png");
	BricksGeneral::GameSetup(BlockWidth,BlockHeight);
}

/**
 * @brief Handling taking damage (since it's indestructible ,definition is empty)
*/
void IndestructibleBrick::TakenDamage() {}

/**
 * @brief Handling Collision with ball
 * @param ballInstance	-takes ball instance for collision
 * @param score			-increase score if brick is dead
 * @param combo			-counts combo per hit
 * @param killedBricks	-increase value if brick is destroyed
 * @param pickupItem	-when brick is destroyed making it movable 
*/
void IndestructibleBrick::OverlapWithBall(Ball* ballInstance, int& score, int& combo, int& killedBricks, int ScreenWidth, PickupItem* pickupItem)
{
	if ((GetXLocation() + BlockWidthVar >= ballInstance->GetBallXLocation() + BallSize - 5 &&
		GetYLocation() + BlockHeightVar >= ballInstance->GetBallYLocation()) && 
		GetXLocation() <= ballInstance->GetBallXLocation()		+ BallSize	&&
		GetYLocation() <= ballInstance->GetBallYLocation()						&&
		isBrickDead() == false
		)
	{
		combo++;
		ballInstance->YAxisMovementSpeed *= -1;
	}
	else if ((this->GetYLocation() + BlockHeightVar >= ballInstance->GetBallYLocation() + BallSize / 2 &&
		this->GetXLocation() <= ballInstance->GetBallXLocation() + BallSize) &&
		this->GetYLocation() <= ballInstance->GetBallYLocation() + BallSize / 2 &&
		this->GetXLocation() + BlockWidthVar >= ballInstance->GetBallXLocation() && 
		isBrickDead() == false
		)
	{
		combo++;
		ballInstance->XAxisMovementSpeed *= -1;
	}
}

//getters
bool IndestructibleBrick::isBrickDead()
{
	return bIsBrickDead;
}
int IndestructibleBrick::GetXLocation()
{
	return SpriteRect.XLocation;
}
int IndestructibleBrick::GetYLocation()
{
	return SpriteRect.YLocation;
}
int IndestructibleBrick::GetHealth()
{
	return health;
}