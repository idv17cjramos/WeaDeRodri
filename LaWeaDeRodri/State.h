#pragma once
class State
{
public:
	State();
	virtual ~State();//Virtual?
	virtual void Start();
	virtual void Update();
	virtual void End();
};

