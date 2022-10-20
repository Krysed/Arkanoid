#include "Ball.h"
#include <cmath>
#include <iostream>

//Constructor
Ball::Ball(PlayerPlatform* platform,int Width) 
	: SpritesLogic("data/64-Breakout-Tiles.png")
{
	this->plat = platform;
	GameSetup(Width);
}

//Deconstructor
Ball::~Ball()
{
	delete plat;
}

/**
 * @brief starting game by moving the ball
*/
void Ball::StartGame(float XAxisSpeed,float YAxisSpeed)
{
	bIsBallMoving = true;

	StartMovementDirection(XAxisSpeed, YAxisSpeed,
		XAxisMovementSpeed,YAxisMovementSpeed
	);
}

/**
 * @brief Sets default Values for Ball
 * Default Position(where does it sits before game starts)
 * Size and reseting bool values
*/
void Ball::GameSetup(int Width)
{
	ballSize = Width * 0.03;
	SetSize(ballSize, ballSize);
	SetPosition(plat->GetPlatformXLocation() + plat->SpriteRect.width / 2,
				plat->GetPlatformYLocation() - 16
			);
	bIsBallMoving = false;
	bIsOutOfMap = false;
}

/**
 * @brief checks movement and is ball is out of map
*/
void Ball::Update(int Width, int Height)
{
	Movement(Height);
	MapBounds(Width, Height);
}

/**
 * @brief Handling movement, and start position for ball
*/
void Ball::Movement(int Height)
{
	if (bIsBallMoving == false)
	{
		SetPosition(plat->SpriteRect.XLocation - 10 + plat->SpriteRect.width / 2, Height - 40
		);
	}
	else
	{
		MoveSprite(XAxisMovementSpeed	, YAxisMovementSpeed);
	}
}

/**
 * @brief sets boundaries for ball to move inside
*/
void Ball::MapBounds(int Width,int Height)
{
	//X axis
	if		(this->SpriteRect.XLocation < 0)			XAxisMovementSpeed = XAxisMovementSpeed * (-1);
	else if (this->SpriteRect.XLocation > Width -20)	XAxisMovementSpeed = XAxisMovementSpeed * (-1);

	//Y axis
	if		(this->SpriteRect.YLocation < 0)		YAxisMovementSpeed *= -1;
	else if (this->SpriteRect.YLocation >= Height)	bIsOutOfMap = true;
}

/**
 * @brief More advanced movement system
 * @param mouseXAxisLocation - Mouse X axis location on screen
 * @param mouseYAxisLocation - Mouse Y axis location on screen
 * @param SpeedX			 - Calculated X axis speed that ball will move with
 * @param SpeedY			 - Calculated X axis speed that ball will move with
*/
void Ball::StartMovementDirection(float mouseXAxisLocation, float mouseYAxisLocation, float& SpeedX, float& SpeedY)
{
	float xAxisDirection = mouseXAxisLocation - GetBallXLocation() - SpriteRect.width / 2;
	float yAxisDirection = mouseYAxisLocation - GetBallYLocation() - SpriteRect.height / 2;
	float length = sqrt((xAxisDirection* xAxisDirection) + (yAxisDirection* yAxisDirection));
	float invLength = 1 / length;

	SpeedX = invLength * xAxisDirection;
	SpeedY = invLength * yAxisDirection;

	//debug line
	//std::cout << SpeedX << " " << xAxisDirection / length << " | " << SpeedY << " " << invLength * yAxisDirection << " | " << invLength <<  '\n';
}

/**
 * @brief choose general direction for ball to go at begining of the game
 * @param mouseXLocation - Mouse X axis location on screen
 * @param mouseYLocation - Mouse Y axis location on screen
*/
void Ball::ChooseDirection(float mouseXLocation, float mouseYLocation)
{
	bIsBallMoving = true;
	if (mouseXLocation < plat->GetPlatformXLocation() + plat->GetPlatformSize() / 2)
	{
		XAxisMovementSpeed=-1; 
		YAxisMovementSpeed=1;
	}
	else if (mouseXLocation > plat->GetPlatformXLocation() + plat->GetPlatformSize() / 2)
	{
		XAxisMovementSpeed=1;
		YAxisMovementSpeed=1;
	}
	else {}
}

//getters
int Ball::GetBallXLocation()
{
	return SpriteRect.XLocation;
}

int Ball::GetBallYLocation()
{
	return SpriteRect.YLocation;
}
float Ball::GetXAxisMovementSpeed()
{
	return XAxisMovementSpeed;
}
float Ball::GetYAxisMovementSpeed()
{
	return YAxisMovementSpeed;
}

//setters
void Ball::SetXAxisMovementSpeed()
{
	XAxisMovementSpeed *= 1.5;
}
void Ball::SetYAxisMovementSpeed()
{
	YAxisMovementSpeed *= 1.5;
}