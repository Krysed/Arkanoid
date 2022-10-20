#include "OneHitBrick.h"
#include <iostream>

//Constructor
OneHitBrick::OneHitBrick(int BlockWidth, int BlockHeight)
{
	GameSetup(BlockWidth, BlockHeight);
}
//Deconstructor
OneHitBrick::~OneHitBrick() {}

/**
 * @brief Setting Default values for Blue Brick
 * Health, Texture, and inherited ones
*/
void OneHitBrick::GameSetup(int BlockWidth, int BlockHeight)
{
	BlockWidthVar = BlockWidth;
	BlockHeightVar = BlockHeight;
	health = maxHealth;
	SetTexture("data/01-Breakout-Tiles.png");
	BricksGeneral::GameSetup(BlockWidth,BlockHeight);
}

/**
 * @brief Handling Damage events
*/
void OneHitBrick::TakenDamage()
{
	health-=1;
	if (health >= 0) bIsBrickDead = true;
}


/**
 * @brief Handling Collision with ball
 * @param ballInstance	-takes ball instance for collision
 * @param score			-increase score if brick is dead
 * @param combo			-counts combo per hit
 * @param killedBricks	-increase value if brick is destroyed
 * @param pickupItem	-when brick is destroyed making it movable
*/
void OneHitBrick::OverlapWithBall(Ball* ballInstance, int& score, int& combo, int& killedBricks, int ScreenWidth, PickupItem* pickupItem)
{
	if ((GetXLocation() + BlockWidthVar >= ballInstance->GetBallXLocation() + BallSize-5 &&
		GetYLocation() + BlockHeightVar >= ballInstance->GetBallYLocation()) &&
		GetXLocation() <= ballInstance->GetBallXLocation() + BallSize / 2 &&
		GetYLocation() <= ballInstance->GetBallYLocation() &&
		isBrickDead() == false
		)
	{
		if (combo > 3)
		{
			combo++;
			score += 30;
			std::cout << "COMBO! Score: " << score << '\n';
			std::cout << "Current Combo: " << combo << '\n';
			killedBricks++;
		}
		else 
		{
			combo++;
			score += 10;
			std::cout << "Score: " << score << '\n';
			killedBricks++;
		}
		ballInstance->YAxisMovementSpeed *= -1;
		TakenDamage();
		pickupItem->SetPosition(((rand() + GetXLocation()) % ScreenWidth), 0);
		pickupItem->SetIsPickupAlive(true);
	}
	if ((this->GetYLocation() + BlockHeightVar >= ballInstance->GetBallYLocation() + BallSize / 2 &&
		this->GetXLocation() <= ballInstance->GetBallXLocation() + BallSize) &&
		this->GetYLocation() <= ballInstance->GetBallYLocation() + BallSize / 2 &&
		this->GetXLocation() + BlockWidthVar >= ballInstance->GetBallXLocation() &&
		isBrickDead() == false
		)
	{
		if (combo > 3)
		{
			combo++;
			score += 30;
			std::cout << "COMBO "<< combo << "x! Score: " << score << '\n';
			killedBricks++;
		}
		else
		{
			combo++;
			score += 10;
			std::cout << "Score: " << score << '\n';
			killedBricks++;
		}
		ballInstance->XAxisMovementSpeed *= -1;
		TakenDamage();
		pickupItem->SetPosition(((rand() + GetXLocation()) % WIDTH), 0);
		pickupItem->SetIsPickupAlive(true);
	}
}

//getters
int OneHitBrick::GetHealth()
{
	return health;
}
bool OneHitBrick::isBrickDead()
{
	return bIsBrickDead;
}
int OneHitBrick::GetXLocation()
{
	return SpriteRect.XLocation;
}
int OneHitBrick::GetYLocation()
{
	return SpriteRect.YLocation;
}