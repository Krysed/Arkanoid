#pragma once
#include "SpritesLogic.h"

/**
 * @brief handling platform movement
*/
struct PlayerMovementStruct
{
	bool bIsMovingRight = false;
	bool bIsMovingLeft = false;
};

class PlayerPlatform :
    public SpritesLogic
{
private:
	//Platform Variables
	const float baseSpeed = 2;
	float movementSpeed = baseSpeed;
	double baseSize ;
	
	double Size;
	double baseHeight;

	int MAX_SIZE;
	int MIN_SIZE;

	int timeElapsed;
	int placeHolder;
	int timeHolder;
	int buffStacks = 0;
	bool bBuffActive = false;


public:
	void GameSetup(int Width, int Height);

	//buffs and debuff effects
	void IncreaseSize();
	void DecreaseSize();
	void DefaultSize();

	//Platfrom logic
	void Update(PlayerMovementStruct& move, int Width);
	void PlayerMovement(PlayerMovementStruct& move);
	void MapBorders(int Width);
	
	//getters
	int GetPlatformXLocation();
	int GetPlatformYLocation();
	int GetPlatformSize();
	int GetTime();


	int SetBuffTime();

	//setters
	void SetTickTime(int Time);
	void SetbBuffActive();

	//Constructor
	PlayerPlatform();

	//Deconstructor
	~PlayerPlatform();
};

