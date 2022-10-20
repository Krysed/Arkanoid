#include "PlayerPlatform.h"
#include <iostream>

//constructor
PlayerPlatform::PlayerPlatform() 
	:SpritesLogic("data/55-Breakout-Tiles.png") {}

//deconstructor
PlayerPlatform::~PlayerPlatform() {}

/**
 * @brief seting default values for platform
 * Default Width,Height, position, and time which is used to calculate how long does buffs/debuffs last
*/
void PlayerPlatform::GameSetup(int Width, int Height)
{
	baseSize = Width* 0.2;
	baseHeight = Height * 0.05;
	Size = baseSize;
	MAX_SIZE = baseSize * 2;
	MIN_SIZE = baseSize * 0.5;

	SetSize(baseSize, baseHeight);
	//Set platform position directly in the middle of X axis
	SetPosition((Width / 2)-SpriteRect.width / 2, Height - SpriteRect.height);
	timeElapsed = getTickCount();
}

/**
 * @brief increase size by 40%
 * MAX_SIZE == 200% of original size
*/
void PlayerPlatform::IncreaseSize()
{
	if (Size)	{ SetSize(Size += Size * 0.4, baseHeight); }	
	if (Size > MAX_SIZE)	{ Size = MAX_SIZE; SetSize(Size, baseHeight); }
	bBuffActive = true;
	buffStacks++;
	//debug line
	//std::cout << "IncRease Size: " << Size << "\n";
}

/**
 * @brief decrease size by 40%
 * MIN_SIZE == 50% of original size
*/
void PlayerPlatform::DecreaseSize()
{
	if (Size > MIN_SIZE)		{ SetSize(Size -= Size * 0.4, 30); }
	else if (Size <= MIN_SIZE)	{ Size = MIN_SIZE; SetSize(Size, 30); }
	if(Size <= MIN_SIZE)		{ Size = MIN_SIZE; SetSize(Size, 30); }
	bBuffActive = true;
	buffStacks++;
	//debug line
	//std::cout << "DecreaseSize: " << Size << "\n";
}

/**
 * @brief sets size to default value
*/
void PlayerPlatform::DefaultSize()
{
	Size = baseSize;
	buffStacks = 0;
	bBuffActive = false;
	SetSize(Size, 30);
}

/**
 * @brief checks if player is out of map
 * handles movement
 * and handles time (how much time does function last)
 * @param movementInput handles player input
*/
void PlayerPlatform::Update(PlayerMovementStruct& movementInput, int Width)
{
	PlayerMovement(movementInput);
	MapBorders(Width);

	if (buffStacks == 0) 
	{
		timeElapsed = getTickCount();
	}
	else if(buffStacks == 1 && bBuffActive)
	{
		if (GetTime() >= 20)
		{
			DefaultSize();
			timeElapsed = getTickCount();
		}
	}
	else if (buffStacks > 1)
	{
		if (buffStacks != placeHolder) 
		{
			placeHolder = buffStacks;
			timeHolder = GetTime();
			timeElapsed = getTickCount();
		}
		if (timeHolder > 20) 
		{
			if (GetTime() >= 40)
			{
				std::cout << timeHolder << '\n';
				DefaultSize();
				timeElapsed = getTickCount();
			}
		}
		else if (GetTime() >= 40-timeHolder)
		{
			DefaultSize();
			timeElapsed = getTickCount();
		}
	}
}

/**
 * @brief handling player movement input
 * @param move - is player pressing key if yes move platform
*/
void PlayerPlatform::PlayerMovement(PlayerMovementStruct& move)
{
	if		(move.bIsMovingRight)	MoveSprite(movementSpeed, 0);
	else if (move.bIsMovingLeft)	MoveSprite(-movementSpeed, 0);
}

/**
 * @brief borders for player platform
*/
void PlayerPlatform::MapBorders(int Width)
{
	if		(SpriteRect.XLocation < 0)			SetPosition(0, SpriteRect.YLocation);
	else if (SpriteRect.XLocation > Width-Size)	SetPosition(Width - Size, SpriteRect.YLocation);
}

//getters
int PlayerPlatform::GetPlatformSize()
{
	return Size;
}
int PlayerPlatform::GetPlatformXLocation()
{
	return SpriteRect.XLocation;
}
int PlayerPlatform::GetPlatformYLocation()
{
	return SpriteRect.YLocation;
}

/**
 * @brief time in seconds
 * @return 
*/
int PlayerPlatform::GetTime()
{
	return (getTickCount() - timeElapsed)/1000;
}

//setters
void PlayerPlatform::SetTickTime(int Time)
{
	this->timeElapsed = Time;
}
void PlayerPlatform::SetbBuffActive()
{
	bBuffActive = false;
}
