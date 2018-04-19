#include "StaticVariables.h"

RPGCharacter* ptr = new RPGCharacter(RPGClassEnumEnd, 0, ""),
*ptr2 = new RPGCharacter(RPGClassEnumEnd, 0, ""),
*ptr3 = new RPGCharacter(RPGClassEnumEnd, 0, ""),
*ptr4 = new RPGCharacter(RPGClassEnumEnd, 0, ""),
*ptr5 = new RPGCharacter(RPGClassEnumEnd, 0, "");
Party StaticVariables::playerParty, StaticVariables::enemyParty;
StaticVariables::StaticVariables()
{
}

StaticVariables::~StaticVariables()
{
}

void StaticVariables::GenerateEnemyParty()
{
	//TODO: hacer esto.
}

void StaticVariables::ClearEnemyParty()
{
	if (enemyParty.backLeft && enemyParty.backLeft != ptr4)
		delete (enemyParty.backLeft);
	if (enemyParty.backRight && enemyParty.backRight != ptr5)
		delete (enemyParty.backRight);
	if (enemyParty.frontRight && enemyParty.frontRight != ptr3)
		delete (enemyParty.frontRight);
	if (enemyParty.frontLeft && enemyParty.frontLeft != ptr2)
		delete (enemyParty.frontLeft);
	if (enemyParty.frontCenter && enemyParty.frontCenter != ptr)
		delete (enemyParty.frontCenter);
	enemyParty.backLeft = enemyParty.backRight = 
		enemyParty.frontCenter = enemyParty.frontLeft = 
		enemyParty.frontRight = nullptr;
}

void StaticVariables::ClearPlayerParty()
{
	if (playerParty.backLeft && playerParty.backLeft != ptr4)
		delete (playerParty.backLeft);
	if (playerParty.backRight && playerParty.backRight != ptr5)
		delete (playerParty.backRight);
	if (playerParty.frontRight && playerParty.frontRight != ptr3)
		delete (playerParty.frontRight);
	if (playerParty.frontLeft && playerParty.frontLeft != ptr2)
		delete (playerParty.frontLeft);
	if (playerParty.frontCenter && playerParty.frontCenter != ptr)
		delete (playerParty.frontCenter);
	playerParty.frontCenter = playerParty.backLeft =
		playerParty.backRight = playerParty.frontLeft =
		playerParty.frontRight = nullptr;
}


Party::Party() :frontCenter(ptr), frontLeft(ptr2), frontRight(ptr3), backLeft(ptr4), backRight(ptr5)
{


}
