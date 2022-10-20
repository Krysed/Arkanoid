#pragma once
#include "Framework.h"
#include "Variables.h"

/**
 * @brief sets Shape for every sprite to use it for collision
*/
struct RectShape
{
	float XLocation, YLocation;
	int side, bottom, width, height;
public:
	RectShape() {
		//default values
		float XLocation = 0;
		float YLocation = 0;
		int side = 0;
		int bottom = 0;
		int width = 0;
		int height = 0;
	}
};

class SpritesLogic
{
	Sprite* spriteInstance;
protected:
	int Width = WIDTH;
	int Height = HEIGHT;
public:
	RectShape SpriteRect;

	//Show on screen
	void DrawInConsole();

	//Movement Logic
	void MoveSprite(float x, float y);

	//easy file path passing
	SpritesLogic(const char* path);

	//Setters
	void SetTexture(const char* path);
	void SetSize(int width, int hight);
	void SetPosition(int x, int y);


	//Constructor
	SpritesLogic();

	//Deconstructor
	~SpritesLogic();
};

