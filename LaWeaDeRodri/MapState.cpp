#include "MapState.h"
#include "Engine.h"
#include "RPGCharacter.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>

MapState::MapState()
{

}

MapState::~MapState()
{
}

void MapState::Start()
{
	srand(time(NULL));
	std::fstream file("WeaChidolira.dat");
	if (file.good())
	{
		file.close();
		map = new Map("WeaChidolira.dat");
	}
	else
	{
		map = new Map(300, 300, .4500f, .4500f, 7);
		map->SaveMapToFile("WeaChidolira.dat");
	}
	file.close();
	file.open("Save/Limon.dat");
	RPGCharacter *chr;
	if (file.good())
		chr = new RPGCharacter("Limon");
	else
	{
		chr = new RPGCharacter(RPGClass::Mage, 1, "Limon");
		chr->SaveToFile();
	}
	file.close();
	player = new Tile(TileType::Player);
	screenW = Engine::getInstance()->getWidth() / 2;
	screenH = Engine::getInstance()->getHeight() / 2;
	player->setXY(screenW, screenH);
	realPX = screenW;
	realPY = screenH;
}

void MapState::Update()
{
	TileType t;
	Tile tile = map->getTileAt(realPX, realPY);
	if (InputManager::GetKey(Key::up))
	{
		t = tile.up->GetType();
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

void MapState::End()
{
}
