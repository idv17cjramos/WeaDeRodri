#include "MapState.h"
#include "Engine.h"
#include "RPGCharacter.h"
#include "HelperFunctions.h"
#include "StaticVariables.h"
#include "StateManager.h"
#include "RPGBattleState.h"
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
	stepsToNextFight = randomRange(0, 30);
	tomando.SetStart(Point(screenW, screenH));
	while (end.x == 0 && end.y == 0)
	{
		Tile t = map->getTileAt(randomRange(0, 300), randomRange(0, 300));
		if (t.GetType() == TileType::Forest || t.GetType() == TileType::Path)
			end = Point(t.getX(), t.getY());
	}
	tomando.SetEnd(end);
	tomando.SetMap(map);
	tomando.CalculateRoute();
}

void MapState::Update()
{
	TileType t;
	Tile tile = map->getTileAt(realPX, realPY);
	//if (InputManager::GetKey(Key::up))
	//{
	//	t = tile.up->GetType();
	//	if (t == TileType::Forest ||
	//		t == TileType::Path ||
	//		t == TileType::Lava)
	//	{
	//		--realPY;
	//		++pY;
	//		++stepsTaken;
	//	}
	//	else if (t == TileType::Treasure)
	//	{
	//		if (StaticVariables::playerParty.frontCenter->getClass() == RPGClass::Thief)
	//		{
	//			StaticVariables::playerParty.frontCenter->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			for (int i = 0; i < 4; ++i);
	//			{
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.frontCenter->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//		}
	//		else
	//		{
	//			for (int i = 0; i < 3; ++i);
	//			{
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.frontCenter->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//		}
	//		if (StaticVariables::playerParty.backRight)
	//		{
	//			if (StaticVariables::playerParty.backRight->getClass() == RPGClass::Thief)
	//			{
	//				StaticVariables::playerParty.backRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				for (int i = 0; i < 4; ++i);
	//				{
	//					int randomChance = randomRange(0, 100);
	//					if (randomChance < 33)
	//						StaticVariables::playerParty.backRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				}
	//			}
	//			else
	//			{
	//				for (int i = 0; i < 3; ++i);
	//				{
	//					int randomChance = randomRange(0, 100);
	//					if (randomChance < 33)
	//						StaticVariables::playerParty.backRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				}
	//			}
	//		}
	//		if (StaticVariables::playerParty.backLeft)
	//		{
	//			if (StaticVariables::playerParty.backLeft->getClass() == RPGClass::Thief)
	//			{
	//				StaticVariables::playerParty.backLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				for (int i = 0; i < 4; ++i);
	//				{
	//					int randomChance = randomRange(0, 100);
	//					if (randomChance < 33)
	//						StaticVariables::playerParty.backLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				}
	//			}
	//			else
	//			{
	//				for (int i = 0; i < 3; ++i);
	//				{
	//					int randomChance = randomRange(0, 100);
	//					if (randomChance < 33)
	//						StaticVariables::playerParty.backLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				}
	//			}
	//		}
	//		if (StaticVariables::playerParty.frontRight)
	//		{
	//			if (StaticVariables::playerParty.frontRight->getClass() == RPGClass::Thief)
	//			{
	//				StaticVariables::playerParty.frontRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				for (int i = 0; i < 4; ++i);
	//				{
	//					int randomChance = randomRange(0, 100);
	//					if (randomChance < 33)
	//						StaticVariables::playerParty.frontRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				}
	//			}
	//			else
	//			{
	//				for (int i = 0; i < 3; ++i);
	//				{
	//					int randomChance = randomRange(0, 100);
	//					if (randomChance < 33)
	//						StaticVariables::playerParty.frontRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				}
	//			}
	//		}
	//		if (StaticVariables::playerParty.frontLeft)
	//		{
	//			if (StaticVariables::playerParty.frontLeft->getClass() == RPGClass::Thief)
	//			{
	//				StaticVariables::playerParty.frontLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				for (int i = 0; i < 4; ++i);
	//				{
	//					int randomChance = randomRange(0, 100);
	//					if (randomChance < 33)
	//						StaticVariables::playerParty.frontLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				}
	//			}
	//			else
	//			{
	//				for (int i = 0; i < 3; ++i);
	//				{
	//					int randomChance = randomRange(0, 100);
	//					if (randomChance < 33)
	//						StaticVariables::playerParty.frontLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				}
	//			}
	//		}
	//		tile.up->SetTileType(TileType::Path);
	//	}

	//}
	//if (InputManager::GetKey(Key::down))
	//{
	//	t = tile.down->GetType();
	//	if (t == TileType::Forest ||
	//		t == TileType::Path ||
	//		t == TileType::Lava)
	//	{
	//		++realPY;
	//		--pY;
	//		++stepsTaken;
	//	}
	//	else if (t == TileType::Treasure)
	//	{
	//		if (StaticVariables::playerParty.frontCenter->getClass() == RPGClass::Thief)
	//		{
	//			StaticVariables::playerParty.frontCenter->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			for (int i = 0; i < 2; ++i);
	//			{
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.frontCenter->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//		}
	//		else
	//		{
	//			for (int i = 0; i < 3; ++i);
	//			{
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.frontCenter->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//		}
	//		if (StaticVariables::playerParty.backRight)
	//		{
	//			if (StaticVariables::playerParty.backRight->getClass() == RPGClass::Thief)
	//			{
	//				StaticVariables::playerParty.backRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.backRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//			else
	//			{
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.backRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//		}
	//		if (StaticVariables::playerParty.backLeft)
	//		{
	//			if (StaticVariables::playerParty.backLeft->getClass() == RPGClass::Thief)
	//			{
	//				StaticVariables::playerParty.backLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.backLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//			else
	//			{
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.backLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//		}
	//		if (StaticVariables::playerParty.frontRight)
	//		{
	//			if (StaticVariables::playerParty.frontRight->getClass() == RPGClass::Thief)
	//			{
	//				StaticVariables::playerParty.frontRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.frontRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//			else
	//			{
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.frontRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//		}
	//		if (StaticVariables::playerParty.frontLeft)
	//		{
	//			if (StaticVariables::playerParty.frontLeft->getClass() == RPGClass::Thief)
	//			{
	//				StaticVariables::playerParty.frontLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.frontLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//			else
	//			{
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.frontLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//		}
	//		tile.down->SetTileType(TileType::Path);
	//	}
	//}
	//if (InputManager::GetKey(Key::left))
	//{
	//	t = tile.left->GetType();
	//	if (t == TileType::Forest ||
	//		t == TileType::Path ||
	//		t == TileType::Lava)
	//	{
	//		--realPX;
	//		++pX;
	//		++stepsTaken;
	//	}
	//	else if (t == TileType::Treasure)
	//	{
	//		if (StaticVariables::playerParty.frontCenter->getClass() == RPGClass::Thief)
	//		{
	//			StaticVariables::playerParty.frontCenter->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.frontCenter->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//		}
	//		else
	//		{
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.frontCenter->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//		}
	//		if (StaticVariables::playerParty.backRight)
	//		{
	//			if (StaticVariables::playerParty.backRight->getClass() == RPGClass::Thief)
	//			{
	//				StaticVariables::playerParty.backRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//					int randomChance = randomRange(0, 100);
	//					if (randomChance < 33)
	//						StaticVariables::playerParty.backRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//			else
	//			{
	//					int randomChance = randomRange(0, 100);
	//					if (randomChance < 33)
	//						StaticVariables::playerParty.backRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//		}
	//		if (StaticVariables::playerParty.backLeft)
	//		{
	//			if (StaticVariables::playerParty.backLeft->getClass() == RPGClass::Thief)
	//			{
	//				StaticVariables::playerParty.backLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//					int randomChance = randomRange(0, 100);
	//					if (randomChance < 33)
	//						StaticVariables::playerParty.backLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//			else
	//			{
	//					int randomChance = randomRange(0, 100);
	//					if (randomChance < 33)
	//						StaticVariables::playerParty.backLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//		}
	//		if (StaticVariables::playerParty.frontRight)
	//		{
	//			if (StaticVariables::playerParty.frontRight->getClass() == RPGClass::Thief)
	//			{
	//				StaticVariables::playerParty.frontRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//					int randomChance = randomRange(0, 100);
	//					if (randomChance < 33)
	//						StaticVariables::playerParty.frontRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//			else
	//			{
	//					int randomChance = randomRange(0, 100);
	//					if (randomChance < 33)
	//						StaticVariables::playerParty.frontRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//		}
	//		if (StaticVariables::playerParty.frontLeft)
	//		{
	//			if (StaticVariables::playerParty.frontLeft->getClass() == RPGClass::Thief)
	//			{
	//				StaticVariables::playerParty.frontLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//					int randomChance = randomRange(0, 100);
	//					if (randomChance < 33)
	//						StaticVariables::playerParty.frontLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//			else
	//			{
	//					int randomChance = randomRange(0, 100);
	//					if (randomChance < 33)
	//						StaticVariables::playerParty.frontLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//		}
	//		tile.left->SetTileType(TileType::Path);
	//	}
	//}
	//if (InputManager::GetKey(Key::right))
	//{
	//	t = tile.right->GetType();
	//	if (t == TileType::Forest ||
	//		t == TileType::Path ||
	//		t == TileType::Lava)
	//	{
	//		++realPX;
	//		--pX;
	//		++stepsTaken;
	//	}
	//	else if (t == TileType::Treasure)
	//	{
	//		if (StaticVariables::playerParty.frontCenter->getClass() == RPGClass::Thief)
	//		{
	//			StaticVariables::playerParty.frontCenter->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			int randomChance = randomRange(0, 100);
	//			if (randomChance < 33)
	//				StaticVariables::playerParty.frontCenter->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//		}
	//		else
	//		{
	//			int randomChance = randomRange(0, 100);
	//			if (randomChance < 33)
	//				StaticVariables::playerParty.frontCenter->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//		}
	//		if (StaticVariables::playerParty.backRight)
	//		{
	//			if (StaticVariables::playerParty.backRight->getClass() == RPGClass::Thief)
	//			{
	//				StaticVariables::playerParty.backRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.backRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//			else
	//			{
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.backRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//		}
	//		if (StaticVariables::playerParty.backLeft)
	//		{
	//			if (StaticVariables::playerParty.backLeft->getClass() == RPGClass::Thief)
	//			{
	//				StaticVariables::playerParty.backLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.backLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//			else
	//			{
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.backLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//		}
	//		if (StaticVariables::playerParty.frontRight)
	//		{
	//			if (StaticVariables::playerParty.frontRight->getClass() == RPGClass::Thief)
	//			{
	//				StaticVariables::playerParty.frontRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.frontRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//			else
	//			{
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.frontRight->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//		}
	//		if (StaticVariables::playerParty.frontLeft)
	//		{
	//			if (StaticVariables::playerParty.frontLeft->getClass() == RPGClass::Thief)
	//			{
	//				StaticVariables::playerParty.frontLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.frontLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//			else
	//			{
	//				int randomChance = randomRange(0, 100);
	//				if (randomChance < 33)
	//					StaticVariables::playerParty.frontLeft->AddItem(StaticVariables::items.at(randomRange(0, StaticVariables::items.size())));
	//			}
	//		}
	//		tile.right->SetTileType(TileType::Path);
	//	}
	//}
	//if (stepsTaken >= stepsToNextFight)
	//{
	//	stepsTaken = 0;
	//	stepsToNextFight = randomRange(0, 30);
	//	StateManager::ChangeState(new RPGBattleState());
	//}
	Point curr = tomando.getCurrPosition();
	Point p = tomando.nextStep();
	pX -= p.x - curr.x;
	pY -= p.y - curr.y;
	map->setPlayerPositon(pX, pY);
	map->drawMap();
	player->draw();
}

void MapState::End()
{
}
