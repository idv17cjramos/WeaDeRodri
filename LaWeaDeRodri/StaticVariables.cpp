#include "StaticVariables.h"
#include "HelperFunctions.h"

Party StaticVariables::playerParty, StaticVariables::enemyParty;
std::vector<std::string> StaticVariables::names = 
{
	"Vladimir",
	"Kim yong bebe",
	"Lord Peña",
	"Meme guy",
	"bunshy",
	"Chinto rey",
	"SFPK Recruit",

};

std::vector<RPGItem> StaticVariables::items =
{
	RPGItem(RPGItemType::Consumable,RPGItemUsageType::HealHP,"Potion",40,"Heals 40 hp, nothing else."),
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
	int rand = randomRange(1,players());
	int randName;
	switch (rand)
	{
	case 4:
		randName = randomRange(0, names.size());
		enemyParty.backRight = new RPGCharacter((RPGClass)randomRange(0, RPGClassEnumEnd), playerParty.frontCenter->getLevel() + (randomRange(0, 6)), names[randName]);
	case 3:
		randName = randomRange(0, names.size());
		enemyParty.backLeft = new RPGCharacter((RPGClass)randomRange(0, RPGClassEnumEnd), playerParty.frontCenter->getLevel() + (randomRange(0, 6)), names[randName]);
	case 2:
		randName = randomRange(0, names.size());
		enemyParty.frontRight = new RPGCharacter((RPGClass)randomRange(0, RPGClassEnumEnd), playerParty.frontCenter->getLevel() + (randomRange(0, 6)), names[randName]);
	case 1:
		randName = randomRange(0, names.size());
		enemyParty.frontLeft = new RPGCharacter((RPGClass)randomRange(0, RPGClassEnumEnd), playerParty.frontCenter->getLevel() + (randomRange(0, 6)), names[randName]);
	case 0:
		randName = randomRange(0, names.size());
		enemyParty.frontCenter = new RPGCharacter((RPGClass)randomRange(0, RPGClassEnumEnd), playerParty.frontCenter->getLevel() + (randomRange(0, 6)), names[randName]);
		break;
	}
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
