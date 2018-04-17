#include "MainState.h"
#include <iostream>
#include "Engine.h"
#include "MenuWindow.h"
#include "InputManager.h"
#include "Map.h"
#include <cstdlib>
#include <ctime>
MainState::MainState()
{
}


MainState::~MainState()
{
}

TextWindow* mw;
MenuWindow* menu;
Map* map;
int pX = 0, pY = 0;
void MainState::Start()
{
	srand(time(NULL));
	//mw = new TextWindow();
	//mw->SetPosition(10, 10);
	//mw->SetDimentions(15, 2);
	//mw->SetBackgroundColor(BackgroundColor::BDARKYELLOW);
	//mw->SetLetterColor(LetterColor::CYAN);
	//mw->SetTextSpeed(2);
	//Engine::getInstance()->setTextWindow(mw);
	//Engine::getInstance()->setTextWindowActive(true);
	//mw->SetText("texterino maxerino alderino");
	//mw->SetCloseKey(Key::space);
	//mw->SetUpScrollKey(Key::up);
	//mw->SetDownScrollKey(Key::down);
	//mw->CloseOnScrollEnd(true);
	//mw->SetAutoScroll(false);
	//menu = new MenuWindow();
	//menu->SetPosition(20, 20);
	//menu->SetDimentions(20, 20);
	//menu->SetBackgroundColor(BackgroundColor::BCYAN);
	//menu->SetLetterColor(LetterColor::GRAY);
	//menu->SetActive(true);
	//menu->AddMenuItem("Test 1");
	//menu->AddMenuItem("Test 2");
	//menu->AddMenuItem("Test 3");
	//menu->AddMenuItem("Test 4");
	//menu->SetCursorDownKey(Key::S);
	//menu->SetCursorUpKey(Key::W);
	//menu->SetCursorType(MenuWindow::CursorType::arrow);
	//menu->SetCursorSelection(Key::space);
	//Engine::getInstance()->setMenuWindow(menu);
	map = new Map(300, 300, .4500f, .4500f,7);
}

void MainState::Update()
{
	//if(InputManager::GetKeyDown(Key::A))
	//	std::cout << " A" << std::endl;
	//if(InputManager::GetKeyUp(Key::C))
	//	std::cout << " C" << std::endl;
	//if(InputManager::GetKey(Key::U))
	//	std::cout << " U" << std::endl;
	if (InputManager::GetKey(Key::up))
		++pY;
	if (InputManager::GetKey(Key::down))
		--pY;
	if (InputManager::GetKey(Key::left))
		++pX;
	if (InputManager::GetKey(Key::right))
		--pX;
	map->setPlayerPositon(pX, pY);
	map->drawMap();
}

void MainState::End()
{
}
