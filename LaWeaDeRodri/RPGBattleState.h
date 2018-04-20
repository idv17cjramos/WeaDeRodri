#pragma once
#include "State.h"
#include "RPGCharacter.h"
#include "StateManager.h"
#include "StaticVariables.h"
#include "Engine.h"
#include "MenuWindow.h"
#include "TextWindow.h"
#include <string>
#include <queue>
#include <algorithm>

typedef std::string(RPGCharacter::*SkillUsageFunc)(RPGCharacter& other, size_t skillNum);

typedef struct SkillUsage
{
	SkillUsageFunc f;
	RPGCharacter* target, * caller;
	size_t skillNum,
		   dex;
}SkillUsage;

inline bool compareSkillUsage(const SkillUsage& a, const SkillUsage& b)
{
	return a.dex < b.dex;
}

class RPGBattleState :
	public State
{
public:
	RPGBattleState();
	~RPGBattleState();
	void Start() override;
	void Update() override;
	void End() override;
	void StartBattle();
	void MidBattle();
	void EndBattle();
	void DisplaySkills(RPGCharacter* chr);
	void DisplayItems(RPGCharacter* chr);
	void SelectTarget();
	void DisplayOptions();
private:
	std::queue<SkillUsage> turnQueue;
	bool enemiesDone = false, playerDone = false,
		battleStarted = false, battleEnded = false,
		menuSetup = false, displayingSkills = false,
		displayingItems = false, selectTarget = false,
		playerWon = false;
	MenuWindow * mw = nullptr;
	TextWindow * partyDisplay = nullptr, *tw = nullptr;
	SkillUsage currSkill;
	int currentSelection = 0;
};

