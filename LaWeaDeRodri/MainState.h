#pragma once
#include <string>
#include "State.h"
#include "Map.h"
#include "MenuWindow.h"
#include "TextWindow.h"
#include "InputManager.h"
class MainState :
	public State//Main state can use all methods of State
{
public:
	MainState();
	~MainState();
	void Start() override;//Allows to override virtual function
	void Update() override;
	void End() override;
private:
	TextWindow * tw = nullptr;
	MenuWindow * mw = nullptr;
	bool startPressed = false, nameEntered = false,
		newGame = false, ngChosen = false, selMenuSetup = false;
	std::string name, msg;
	RPGClass cls;
};