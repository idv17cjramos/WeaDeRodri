#pragma once
class State
{
public:
	State();
	virtual ~State();//Allows function to be overwritten at some point in time
	virtual void Start();
	virtual void Update();
	virtual void End();
};

