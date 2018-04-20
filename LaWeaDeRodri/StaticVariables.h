#pragma once
#include "RPGCharacter.h"

typedef struct Party
{
	RPGCharacter *frontLeft = nullptr, // 1
		*frontCenter = nullptr, // 0
		*frontRight = nullptr; // 2
	RPGCharacter *backLeft = nullptr, // 3
		*backRight = nullptr; // 4
}Party;

class StaticVariables
{
public:
	StaticVariables();
	~StaticVariables();
	static Party playerParty, enemyParty;
	static void GenerateEnemyParty();
	static void ClearEnemyParty();
	static void ClearPlayerParty();
};

