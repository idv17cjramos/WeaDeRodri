#include "StaticVariables.h"

Party StaticVariables::playerParty, StaticVariables::enemyParty;
StaticVariables::StaticVariables()
{
}

StaticVariables::~StaticVariables()
{
}

void StaticVariables::GenerateEnemyParty()
{
	enemyParty.frontCenter = new RPGCharacter(RPGClass::Barbarian, 10, "TUGFA");
	//TODO: hacer esto.
}

void StaticVariables::ClearEnemyParty()
{
	if (enemyParty.backLeft)
		delete (enemyParty.backLeft);
	if (enemyParty.backRight)
		delete (enemyParty.backRight);
	if (enemyParty.frontRight)
		delete (enemyParty.frontRight);
	if (enemyParty.frontLeft)
		delete (enemyParty.frontLeft);
	if (enemyParty.frontCenter)
		delete (enemyParty.frontCenter);
	enemyParty.backLeft = enemyParty.backRight = 
		enemyParty.frontCenter = enemyParty.frontLeft = 
		enemyParty.frontRight = nullptr;
}

void StaticVariables::ClearPlayerParty()
{
	if (playerParty.backLeft)
		delete (playerParty.backLeft);
	if (playerParty.backRight)
		delete (playerParty.backRight);
	if (playerParty.frontRight)
		delete (playerParty.frontRight);
	if (playerParty.frontLeft)
		delete (playerParty.frontLeft);
	if (playerParty.frontCenter)
		delete (playerParty.frontCenter);
	playerParty.frontCenter = playerParty.backLeft =
		playerParty.backRight = playerParty.frontLeft =
		playerParty.frontRight = nullptr;
}
