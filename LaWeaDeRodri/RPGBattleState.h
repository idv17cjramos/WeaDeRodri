#pragma once
#include "State.h"
class RPGBattleState :
	public State
{
public:
	RPGBattleState();
	~RPGBattleState();
	void Start() override;
	void Update() override;
	void End() override;
};

