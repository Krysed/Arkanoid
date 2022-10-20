#include "PickupItem.h"
#include <ctime>
#include <cstdlib>
PickupItem::PickupItem() 
{
}
PickupItem::~PickupItem() {}

void PickupItem::Movement()
{
	if (bIsPickupAlive)
	{
		MoveSprite(0, yAxisMovement);
	}
}
bool PickupItem::IsPickupAlive()
{
	return bIsPickupAlive;
}
void PickupItem::SetIsPickupAlive(bool state)
{
	bIsPickupAlive = state;
}