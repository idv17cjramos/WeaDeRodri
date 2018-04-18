#pragma once
#include "State.h"
#include "Tile.h"
#include "Map.h"
#include "MenuWindow.h"
#include "TextWindow.h"
#include "InputManager.h"
class MapState :
	public State
{
public:
	MapState();
	~MapState();
	void Start() override;
	void Update() override;
	void End() override;
private:
	TextWindow * mw;
	MenuWindow* menu;
	Map* map;
	Tile* player;
	int pX = 0, pY = 0, realPY, realPX;
	int screenW, screenH;
	int stepsTaken = 0, stepsToNextFight;
};

