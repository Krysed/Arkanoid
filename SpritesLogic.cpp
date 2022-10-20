#include "SpritesLogic.h"

//Constructor
SpritesLogic::SpritesLogic(const char* path)
{
	SetTexture(path);
	getScreenSize(Width, Height);
}

//Constructor
SpritesLogic::SpritesLogic()
{
	getScreenSize(Width, Height);
}

//Deconstructor
SpritesLogic::~SpritesLogic()
{
	delete spriteInstance;
}

/**
 * @brief Draw image on Screen
*/
void SpritesLogic::DrawInConsole()
{
	drawSprite(spriteInstance, //Sprite variable
		SpriteRect.XLocation,  //X axis Location
		SpriteRect.YLocation   //Y axis Location
	);
}

/**
 * @brief Movement Function for sprites
 * @param xAxisLocation - setting X axis point for top left corner of sprite
 * @param yAxisLocation - setting X axis point for top left corner of sprite
*/
void SpritesLogic::MoveSprite(float xAxisLocation, float yAxisLocation)
{
	SpriteRect.XLocation	= SpriteRect.XLocation	+ xAxisLocation;
	SpriteRect.YLocation	= SpriteRect.YLocation	+ yAxisLocation;
	SpriteRect.side			= SpriteRect.side		+ xAxisLocation;
	SpriteRect.bottom		= SpriteRect.bottom		+ yAxisLocation;
}

//Setters
/**
 * @brief setting texture
 * @param path - takes file path as a variable
*/
void SpritesLogic::SetTexture(const char* path)
{
	spriteInstance = createSprite(path);
}

/**
 * @brief Setting Sprite Size
 * @param width		- Sprite width
 * @param height	- Sprite height
*/
void SpritesLogic::SetSize(int width, int height)
{
	SpriteRect.side		= SpriteRect.XLocation + width;
	SpriteRect.bottom	= SpriteRect.YLocation + height;
	SpriteRect.width	= width;
	SpriteRect.height	= height;
	setSpriteSize(spriteInstance, width, height);
}

/**
 * @brief Setting Position of Sprite in the Window
 * @param xAxisLocation - setting X axis point for top left corner of sprite
 * @param yAxisLocation - setting Y axis point for top left corner of sprite
*/
void SpritesLogic::SetPosition(int xAxisLocation, int yAxisLocation)
{
	SpriteRect.XLocation = xAxisLocation;
	SpriteRect.YLocation = yAxisLocation;
	SpriteRect.height	 = xAxisLocation + SpriteRect.width;
	SpriteRect.bottom	 = yAxisLocation + SpriteRect.height;
}
