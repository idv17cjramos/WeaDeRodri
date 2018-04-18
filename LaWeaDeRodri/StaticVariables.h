#pragma once
#include "RPGCharacter.h"

typedef struct Party
{
	RPGCharacter **frontLeft = nullptr, **frontCenter = nullptr, **frontRight = nullptr;
	RPGCharacter **backLeft = nullptr, **backRight = nullptr;
}Party;

class StaticVariables
{
public:
	StaticVariables();
	~StaticVariables();
	static Party playerParty, enemyParty;
	static void GenerateEnemyParty();
	static void ClearEnemyParty();
};

