#pragma once
#include "RPGCharacter.h"

typedef struct Party
{
	Party();
	RPGCharacter *&frontLeft, // 1
		*&frontCenter, // 0
		*&frontRight ; // 2
	RPGCharacter *&backLeft, // 3
		*&backRight; // 4
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

