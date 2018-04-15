#pragma once
#include "State.h"
class MainState :
	public State//Main state can use all methods of State
{
public:
	MainState();
	~MainState();
	void Start() override;//Allows to override virtual function
	void Update() override;
	void End() override;
};