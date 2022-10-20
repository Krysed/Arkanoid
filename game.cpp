#include "BricksGeneral.h"
#include "SpritesLogic.h"

#include "PickupItem.h"
#include "BuffPickup.h"
#include "DebuffPickup.h"

#include "OneHitBrick.h"
#include "TwoHitBrick.h"
#include "IndestructibleBrick.h"

#include "PlayerPlatform.h"
#include "Ball.h"

#include "Framework.h"

#include<iostream>
#include<vector>
#include<string>
int ScreenWidth;
int ScreenHeight;

/* Test Framework realization */
class MyFramework : public Framework {

private:
	//setting up game components
	int killedBricks = 0;
	int goldBricksCount ,killableBricks;
	int comboPoints = 0;
	int timeElapsed;
	int counter = 0;
	float xStartDirection, yStartDirection;

	int score = NULL;

	bool bIsGameRunning = false;
	bool bIsGameFinished = false;

	//Background
	SpritesLogic* backgroundGraphic;
	
	//Player Platform
	PlayerPlatform* playerPlatform;
	
	//Pickup items
	PickupItem* pickupItem[30];
	BuffPickup* buffPickup;
	DebuffPickup* debuffPickup;

	//Movement component
	PlayerMovementStruct movement;

	//bricks
	BricksGeneral* bricks[30];
	OneHitBrick* oneHitBrick;
	TwoHitBrick* twoHitBrick;
	IndestructibleBrick* indestructibleBrick;
	
	//ball
	Ball* ball;

public:
	/**
	 * @brief initialization for framework window
	 * @param width X axis resolution
	 * @param height Y axis resolution
	 * @param fullscreen is fullscreen mode enabled
	*/
	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = ScreenWidth;
		height = ScreenHeight;
		fullscreen = false;
	}
	/**
	 * @brief initialization of elements in game
	 * @return true when finished
	*/
	virtual bool Init() {
		//for random generation of buff/debuff
		srand(time(nullptr));

		
		//bIsGameRunning = true;
		backgroundGraphic = new SpritesLogic("data/background.png");
		playerPlatform = new PlayerPlatform();
		ball = new Ball(playerPlatform,ScreenWidth);
		//Setup Bricks

		for (int i = 0; i < NUMBER_OF_BRICKS; i++)
		{
			if ((i < 10) && (i >= 0))
			{

				indestructibleBrick = new IndestructibleBrick(ScreenWidth * 0.1, ScreenHeight * 0.05);
				bricks[i] = indestructibleBrick;
				bricks[i]->SetPosition((ScreenWidth * 0.1) * i,ScreenHeight* 0.1);
				goldBricksCount++;
					
			}
			else if ((i < 20) && (i >= 10))
			{
				if ( i == 14 || i == 15 || i == 10|| i ==19)
				{
					twoHitBrick = new TwoHitBrick(ScreenWidth * 0.1,ScreenHeight*0.05);
					bricks[i] = twoHitBrick;
					bricks[i]->SetPosition((ScreenWidth * 0.1) * (i - 10), ScreenHeight* 0.15);
				}
				else
				{
					oneHitBrick = new OneHitBrick(ScreenWidth * 0.1, ScreenHeight * 0.05);
					bricks[i] = oneHitBrick;
					bricks[i]->SetPosition((ScreenWidth * 0.1) * (i - 10), ScreenHeight * 0.15);
				}
			}
			else if ((i < NUMBER_OF_BRICKS) && (i >= 20 && i < 30))
			{
				oneHitBrick = new OneHitBrick(ScreenWidth * 0.1, ScreenHeight * 0.05);
				bricks[i] = oneHitBrick;
				bricks[i]->SetPosition((ScreenWidth * 0.1) * (i - 20), ScreenHeight * 0.2);
			}
		}

		//setup bonus
		for (int i = 0; i < NUMBER_OF_ITEMS; i++)
		{
			int number = (rand()+i)% 10;

			if (number >= 4)
			{
				pickupItem[i] = new DebuffPickup; 
			}
			else
			{
				pickupItem[i] = new BuffPickup;
			}
		}

		StartGameState();
		killableBricks = NUMBER_OF_BRICKS - goldBricksCount;
		return true;
	}
	/**
	 * @brief handles values when starting/restarting game 
	*/
	void StartGameState()
	{
		//clear screen
		system("cls");
		if (score == NULL)
		{
			//Shows controlls at launch of the game
			Controls();
		}
		//View final Score from Previous Round
		if(score != NULL)
		std::cout << "Final Score: " << score << std::endl;
		if (bIsGameFinished && killedBricks == killableBricks)
		{
			system("cls");
			std::cout << "Victory! \t Your Score: " << score << '\n';
		}

		//reset bool values
		bIsGameRunning = false;
		bIsGameFinished = false;

		//set values to zero
		score = 0;
		killedBricks = 0;
		comboPoints = COMBO_RESET;

		//Reset Platform Position,size and ball starting position
		playerPlatform->DefaultSize();
		playerPlatform->GameSetup(ScreenWidth,ScreenHeight);
		playerPlatform->SetbBuffActive();
		ball->GameSetup(ScreenWidth);

		//finish
		for (int i = 0; i < NUMBER_OF_BRICKS; i++)bricks[i]->GameSetup(ScreenWidth * 0.1, ScreenHeight * 0.05);
	}
	virtual void Close() {
		
	}
	/**
	 * @brief resets ComboPoints that player have obtained
	*/
	void ComboResetFunc()
	{
		comboPoints = COMBO_RESET;
	}
	/**
	 * @brief called every frame
	 * @return 
	*/
	virtual bool Tick() 
	{
		srand(time(NULL));
		int number = (rand() + counter) % 40 + counter;
		drawOnTick();

		timeElapsed = getTickCount();
		//std::cout << xStartDirection << " " << yStartDirection << '\n';
		//ball->StartGame(xStartDirection, yStartDirection);
		//std::cout << ball->GetXAxisMovementSpeed() << ball->GetYAxisMovementSpeed() << '\n';
		if (bIsGameRunning) 
		{
			if (counter > NUMBER_OF_ITEMS)
			{
				//std::cout << timeElapsed / 1000 << "\n";
				if (GetTimeInSeconds() >= number)
				{
					timeElapsed = getTickCount();
				}
			}
		}

		//overlap with platform
		if ((playerPlatform->GetPlatformXLocation() + playerPlatform->GetPlatformSize() >= ball->GetBallXLocation() &&
			ball->GetBallYLocation() == playerPlatform->GetPlatformYLocation()&& 
			playerPlatform->GetPlatformXLocation()	<= ball->GetBallXLocation()))
		{
			ball->YAxisMovementSpeed *= -1;
			ComboResetFunc();
		}
		if (ball->GetBallYLocation() > HEIGHT)
		{
			bIsGameFinished = true;
			bIsGameRunning = false;
			StartGameState();
		}

		//platform overlap with pickup items
		for (int i = 0; i < NUMBER_OF_BRICKS;i++)
		{
			if ((playerPlatform->GetPlatformXLocation() + playerPlatform->GetPlatformSize() >= pickupItem[i]->GetPickupXLocation() && 
				pickupItem[i]->GetPickupYLocation()+10 == playerPlatform->GetPlatformYLocation()) &&
				(playerPlatform->GetPlatformXLocation()	<= pickupItem[i]->GetPickupXLocation()))
			{
				pickupItem[i]->DestroyOnContact(playerPlatform);
			}
		}

		//Handling Overlap with Bricks, Calculating Score, Combo, killedBricks variable and changing items state
		for (int i = 0; i < NUMBER_OF_BRICKS; i++)
		{
			bricks[i]->OverlapWithBall(ball, score, comboPoints, killedBricks,ScreenWidth, pickupItem[i]);
		}

		//Handling Game victory State
		if (killedBricks == killableBricks)
		{
			bIsGameFinished = true;
			bIsGameRunning = false;
			StartGameState();
		}

		return false;
	}

	/**
	 * @brief Getting mouse position
	*/
	virtual void onMouseMove(int XPosition, int YPosition, int xrelative, int yrelative) {
		this->xStartDirection = XPosition;
		this->yStartDirection = YPosition;
	}

	/**
	 * @brief handling mouse input
	 * @param button 
	 * @param isReleased when button is released
	*/
	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		switch (button)
		{
		case FRMouseButton::LEFT:
			if (bIsGameRunning == false) {
				bIsGameRunning = true;
				system("cls");
				ball->StartGame(xStartDirection, yStartDirection);
				timeElapsed = getTickCount();
				//basic movement system
				//ball->ChooseDirection(xStartDirection, yStartDirection);
			}
			break;
		}
	}

	/**
	 * @brief handling keyboard input when pressed
	 * @param k - pressed hey
	*/
	virtual void onKeyPressed(FRKey k) {
		switch (k)
		{
		case FRKey::LEFT:
			movement.bIsMovingLeft = true;
			break;
		case FRKey::RIGHT:
			movement.bIsMovingRight = true;
			break;
		}
	}

	/**
	 * @brief handling keyboard input when key is relesed
	 * @param k - pressed hey
	*/
	virtual void onKeyReleased(FRKey k) {
		switch (k)
		{
		case FRKey::DOWN:
			//debug
			ball->XAxisMovementSpeed = 0;
			ball->YAxisMovementSpeed = 0;
			break;
		case FRKey::LEFT:
			movement.bIsMovingLeft = false;
			break;
		case FRKey::RIGHT:
			movement.bIsMovingRight = false;
			break;
		case FRKey::UP:
			if (bIsGameRunning == false) {
				bIsGameRunning = true;
				system("cls");
				ball->StartGame(xStartDirection, yStartDirection);
			}
			break;
		}
	}

	/**
	 * @brief update every frame/ draws on screen every frame
	*/
	void drawOnTick()
	{
		renderGraphics();
		ball->Update(ScreenWidth,ScreenHeight);
		playerPlatform->Update(movement, ScreenWidth);
		for (int i = 0; i < NUMBER_OF_ITEMS; i++)
		{
			if (pickupItem[i] != NULL)
			{
				pickupItem[i]->Movement();
			}
		}
	}

	/**
	 * @brief draws every sprite on screen
	*/
	void renderGraphics()
	{
		//drawTestBackground();
		backgroundGraphic->DrawInConsole();
		playerPlatform->DrawInConsole();
		ball->DrawInConsole();

		for (int i = 0; i < NUMBER_OF_BRICKS; i++)
		{
			if (!(bricks[i]->isBrickDead()))bricks[i]->DrawInConsole();
		}
		for (int i = 0; i < NUMBER_OF_ITEMS;i++)
		{
			if(pickupItem[i] != NULL)
			if (pickupItem[i]->IsPickupAlive())
			{
				pickupItem[i]->DrawInConsole();
			}
		}
	}

	/**
	 * @brief Shows title in top left corner of window
	 * @return - shown title
	*/
	virtual const char* GetTitle() override
	{
		return "ArcanoidV2";
	}

	/**
	 * @brief Shows Game Controlls
	*/
	void Controls()
	{
		std::cout << "Aim with mouse\n\n";
		std::cout << "Left mouse button       - Start game\n";
		std::cout << "UP    arrow on Keyboard - Start Game\n\n";
		std::cout << "RIGHT arrow on Keyboard - Move right\n";
		std::cout << "LEFT  arrow on Keyboard - Move left \n";
		std::cout << "DOWN  arrow on Keyboard - Stop ball movement (For debug)\n";
	}
	/**
	 * @brief returns current time
	*/
	int GetTimeInSeconds()
	{
		return (getTickCount() - timeElapsed / 1000);
	}
};

/**
 * @brief main function
 * @return runs framework
*/
int main(int argc, char *argv[])
{
	if (!strcmp(argv[1], "-window"))
	{
		//string for conversion
		std::string value= argv[2];

		for (int i = 0; i < strlen(argv[2]); i++)
			if (argv[2][i] == 'x')
			{
				//converting string to int
				ScreenWidth = std::stoi(value.substr(0, i));
				ScreenHeight = std::stoi(value.substr(i + 1, value.size()));
				break;
			}
	}
	else
	{
		//if numbers are invalid
		ScreenHeight = HEIGHT;
		ScreenWidth = WIDTH;
	}

	return run(new MyFramework);
}