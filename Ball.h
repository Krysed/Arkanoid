#pragma once
#include "SpritesLogic.h"
#include "PlayerPlatform.h"

class Ball :
    public SpritesLogic
{
	bool bIsBallMoving;
	bool bIsOutOfMap;

	PlayerPlatform* plat;

	int ballSize;

public:
	//movement options
	float XAxisMovementSpeed = 1.f;
	float YAxisMovementSpeed = 1.f;
	int timer = getTickCount();

	void Update(int Width, int Height);
	void Movement(int Height);

	void GameSetup(int Width);
	void MapBounds(int Width, int Height);

	//movement
	void StartGame(float XAxisSpeed, float YAxisSpeed);
	void StartMovementDirection(float mouseXAxisLocation,float mouseYAxisLocation, float& SpeedX, float& SpeedY);
	void ChooseDirection(float mouseXLocation, float mouseYLocation);

	//Getters
	int GetBallXLocation();
	int GetBallYLocation();

	float GetXAxisMovementSpeed();
	float GetYAxisMovementSpeed();

	void SetXAxisMovementSpeed();
	void SetYAxisMovementSpeed();

	//Constructor
	Ball(PlayerPlatform* plat,int Width);
	//Deconstructor
	~Ball();
};