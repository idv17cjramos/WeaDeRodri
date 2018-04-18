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
	//TODO: hacer esto.
}

void StaticVariables::ClearEnemyParty()
{
	if (enemyParty.backLeft)
		delete (*enemyParty.backLeft);
	if (enemyParty.backRight)
		delete (*enemyParty.backRight);
	if (enemyParty.frontRight)
		delete (*enemyParty.frontRight);
	if (enemyParty.frontLeft)
		delete (*enemyParty.frontLeft);
	if (enemyParty.frontCenter)
		delete (*enemyParty.frontCenter);
	enemyParty.backLeft = enemyParty.backRight = 
		enemyParty.frontCenter = enemyParty.frontLeft = 
		enemyParty.frontRight = nullptr;
}
