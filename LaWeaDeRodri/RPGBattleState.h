#pragma once
#include "State.h"
#include "RPGCharacter.h"
#include "StateManager.h"
#include "Engine.h"
#include "MenuWindow.h"
#include "TextWindow.h"
#include <string>
#include <queue>
#include <algorithm>

typedef std::string(*SkillUsageFunc)(RPGCharacter& other, size_t skillNum);

typedef struct SkillUsage
{
	SkillUsageFunc f;
	RPGCharacter** target;
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
private:
	std::queue<SkillUsage> turnQueue;
	bool enemiesDone = false, playerDone = false;
	MenuWindow * mw;
	TextWindow * tw, *tw2;
	int currentSelection = 0;
};

