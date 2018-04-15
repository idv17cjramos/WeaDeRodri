#pragma once//Why do we need a state manager? Basically so we can pause the game
#include <stack>
#include "State.h"
class StateManager
{
public:
	StateManager();
	~StateManager();
	static void ChangeState(State* const& state);//pointer
	static void EndState();
	static void Update();
private:
	
	static std::stack<State*> _stateStack;//Variable
};

