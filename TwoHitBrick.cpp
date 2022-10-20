#include "TwoHitBrick.h"
#include <iostream>

//Constructor
TwoHitBrick::TwoHitBrick(int BlockWidth, int BlockHeight)
{
	GameSetup(BlockWidth, BlockHeight);
}
//Deconstructor
TwoHitBrick::~TwoHitBrick() {}

/**
 * @brief Setting Default Values for Green Brick
*/
void TwoHitBrick::GameSetup(int BlockWidth, int BlockHeight)
{
	BlockWidthVar = BlockWidth;
	BlockHeightVar = BlockHeight;
	health = maxHealth;
	SetTexture("data/15-Breakout-Tiles.png");
	BricksGeneral::GameSetup(BlockWidth,BlockHeight);
}

/**
 * @brief Handling Damage Event
*/
void TwoHitBrick::TakenDamage()
{
	health = 1;
	if (maxHealth > health)
	{
		SetTexture("data/16-Breakout-Tiles.png");
		SetSize(SpriteRect.width, SpriteRect.height);
	}
}

/**
 * @brief Handling Collision with ball
 * @param ballInstance	-takes ball instance for collision
 * @param score			-increase score if brick is dead
 * @param combo			-counts combo per hit
 * @param killedBricks	-increase value if brick is destroyed
 * @param pickupItem	-when brick is destroyed making it movable
*/
void TwoHitBrick::OverlapWithBall(Ball*ballInstance , int &score, int& combo, int& killedBricks, int ScreenWidth,PickupItem* pickupItem)
{
	if ((GetXLocation() + BlockWidthVar >= ballInstance->GetBallXLocation() + BallSize - 5 &&
		GetYLocation() + BlockHeightVar >= ballInstance->GetBallYLocation()) &&
		GetXLocation()			<= ballInstance->GetBallXLocation() + BallSize / 2	&&
		GetYLocation()			<= ballInstance->GetBallYLocation()					&&
		isBrickDead() == false
		)
	{
		if (combo > 3)
		{
			combo++;
			score += 30;
			std::cout << "COMBO! Score: " << score << '\n';
		}
		else
		{
			combo++;
			score += 10;
			std::cout << "Score: " << score << '\n';
		}
		if (health == 2) {
			ballInstance->YAxisMovementSpeed *= -1;
			TakenDamage();

			pickupItem->SetPosition(((rand() + GetXLocation()) % ScreenWidth), 0);
			pickupItem->SetIsPickupAlive(true);
		}
		else
		{
			ballInstance->YAxisMovementSpeed *= -1;
			killedBricks++;
			SetDead();
			pickupItem->SetPosition(((rand() + GetXLocation()) % ScreenWidth), 0);
			pickupItem->SetIsPickupAlive(true);
		}
	}
	else if ((this->GetYLocation() + BlockHeightVar >= ballInstance->GetBallYLocation() +	BallSize / 2	&&
			this->GetXLocation()		<= ballInstance->GetBallXLocation() +	BallSize)		&&
			this->GetYLocation()		<= ballInstance->GetBallYLocation() +	BallSize / 2	&&
			this->GetXLocation() + BlockWidthVar >= ballInstance->GetBallXLocation()						&&
			isBrickDead() == false
		)
	{
		if (combo > 3)
		{
			combo++;
			score += 30;
			std::cout << "COMBO " << combo << "x! Score: " << score << '\n';
		}
		else
		{
			combo++;
			score += 10;
			std::cout << "Score: " << score << '\n';
		}
		if (health == 2)
		{
			ballInstance->YAxisMovementSpeed *= -1;
			TakenDamage();
		}
		else
		{
			ballInstance->XAxisMovementSpeed *= -1;
			SetDead();
			killedBricks++;
			pickupItem->SetPosition(((rand() + GetXLocation()) % ScreenWidth - 50), 0);
			pickupItem->SetIsPickupAlive(true);
		}
	}
}

//Getters
int TwoHitBrick::GetHealth()
{
	return health;
}
bool TwoHitBrick::isBrickDead()
{
	return bIsBrickDead;
}

int TwoHitBrick::GetXLocation()
{
	return SpriteRect.XLocation;
}
int TwoHitBrick::GetYLocation()
{
	return SpriteRect.YLocation;
}

//Setters
void TwoHitBrick::SetDead()
{
	bIsBrickDead = true;
}