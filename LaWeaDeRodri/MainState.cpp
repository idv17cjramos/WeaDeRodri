#include "MainState.h"
#include "Engine.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
MainState::MainState()
{
}


MainState::~MainState()
{
}


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
	std::fstream file("WeaChidolira.dat");
	if (file.good())
	{
		file.close();
		map = new Map("WeaChidolira.dat");
	}
	else
	{
		map = new Map(300, 300, .4500f, .4500f,7);
		map->SaveMapToFile("WeaChidolira.dat");
	}
	player = new Tile(TileType::Player);
	screenW = Engine::getInstance()->getWidth() / 2;
	screenH = Engine::getInstance()->getHeight() / 2;
	player->setXY(screenW, screenH);
	realPX = screenW;
	realPY = screenH;
}

void MainState::Update()
{
	//if(InputManager::GetKeyDown(Key::A))
	//	std::cout << " A" << std::endl;
	//if(InputManager::GetKeyUp(Key::C))
	//	std::cout << " C" << std::endl;
	//if(InputManager::GetKey(Key::U))
	//	std::cout << " U" << std::endl;
	TileType t;
	Tile tile = map->getTileAt(realPX, realPY);
	if (InputManager::GetKey(Key::up))
	{
		t =	tile.up->GetType();
		if (t == TileType::Forest ||
			t == TileType::Path ||
			t == TileType::Lava)
		{
			--realPY;
			++pY;
		}

	}
	if (InputManager::GetKey(Key::down))
	{
		t = tile.down->GetType();
		if (t == TileType::Forest ||
			t == TileType::Path ||
			t == TileType::Lava)
		{
			++realPY;
			--pY;
		}
	}
	if (InputManager::GetKey(Key::left))
	{
		t = tile.left->GetType();
		if (t == TileType::Forest ||
			t == TileType::Path ||
			t == TileType::Lava)
		{
			--realPX;
			++pX;
		}
	}
	if (InputManager::GetKey(Key::right))
	{
		t = tile.right->GetType();
		if (t == TileType::Forest ||
			t == TileType::Path ||
			t == TileType::Lava)
		{
			++realPX;
			--pX;
		}
	}
	map->setPlayerPositon(pX, pY);
	map->drawMap();
	player->draw();
}

void MainState::End()
{
}
