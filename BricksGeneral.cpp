#include "BricksGeneral.h"
#include "Variables.h"

//constructor
BricksGeneral::BricksGeneral() {}
//deconstructor
BricksGeneral::~BricksGeneral() {}

/**
 * @brief sets default values for every block
 * Width, height and status
*/
void BricksGeneral::GameSetup(int BlockWidth,int BlockHeight)
{
	bIsBrickDead = false;
	SetSize(BlockWidth, BlockHeight);
}