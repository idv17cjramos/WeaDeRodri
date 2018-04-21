#include "StaticVariables.h"
#include "HelperFunctions.h"

Party StaticVariables::playerParty, StaticVariables::enemyParty;
static std::string StaticVariables::*names = new std::string[]
{
	"Vladimir",
	"Kim yong bebe",
	"Lord Peña",
	"Meme guy",
	"bunshy",
	"Chinto rey",
	"SFPK Recruit",

};

StaticVariables::StaticVariables()
{
}

StaticVariables::~StaticVariables()
{
}

int StaticVariables::enemies()
{
	int ret = 0;
	if (enemyParty.backLeft)
		++ret;
	if (enemyParty.backRight)
		++ret;
	if (enemyParty.frontCenter)
		++ret;
	if (enemyParty.frontLeft)
		++ret;
	if (enemyParty.frontRight)
		++ret;
	return ret;
}

int StaticVariables::players()
{
	int ret = 0;
	if (playerParty.backLeft)
		++ret;
	if (playerParty.backRight)
		++ret;
	if (playerParty.frontCenter)
		++ret;
	if (playerParty.frontLeft)
		++ret;
	if (playerParty.frontRight)
		++ret;
	return ret;
}

void StaticVariables::GenerateEnemyParty()
{
	int rand = randomRange(0,5);
	switch (rand)
	{
	case 4:
		enemyParty.frontRight = new RPGCharacter((RPGClass)randomRange(0,RPGClassEnumEnd), playerParty.frontCenter->getLevel() + (randomRange(0, 6) - 3), names[(randomRange(0,names[size()))]);
	case 3:
		enemyParty.backLeft = new RPGCharacter(RPGClass::Barbarian, 1, "TUGFA");
	case 2:
		enemyParty.frontRight = new RPGCharacter(RPGClass::Barbarian, 1, "TUGFA");
	case 1:
		enemyParty.frontLeft = new RPGCharacter(RPGClass::Barbarian, 1, "TUGFA");
	case 0:
		enemyParty.frontCenter = new RPGCharacter(RPGClass::Barbarian, 1, "TUGFA");
		break;
	}
	enemyParty.backLeft;
	enemyParty.backRight;
	enemyParty.frontLeft;
	enemyParty.frontRight;
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
