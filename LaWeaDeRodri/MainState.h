#pragma once
#include "State.h"
#include "Tile.h"
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
	TextWindow* mw;
	MenuWindow* menu;
	Map* map;
	Tile* player;
	int pX = 0, pY = 0, realPY, realPX;
	int screenW, screenH;
};