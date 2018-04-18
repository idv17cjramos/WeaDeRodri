#include "StateManager.h"

std::stack<State*> StateManager::_stateStack;

StateManager::StateManager()
{
}


StateManager::~StateManager()
{
}

void StateManager::ChangeState(State * const & state)
{
	_stateStack.push(state);
	_stateStack.top()->Start();
}

void StateManager::EndState()
{
	if (!_stateStack.empty())
	{
		_stateStack.top()->End();
		delete _stateStack.top();
		_stateStack.pop();
	}
}

void StateManager::Update()
{
	if (!_stateStack.empty())
		_stateStack.top()->Update();
}
