#include "MainState.h"
#include "MapState.h"
#include "StateManager.h"
#include "Engine.h"
#include "RPGCharacter.h"
#include "StaticVariables.h"
#include "MapState.h"

MainState::MainState()
{
}


MainState::~MainState()
{
}

void MainState::Start()
{
	tw = new TextWindow();
	tw->SetActive(true);
	tw->SetAutoScroll(false);
	tw->SetTextSpeed(3);
	tw->SetDimentions(51, 3);
	tw->SetPosition((Engine::getInstance()->getWidth() / 2) - 25, (Engine::getInstance()->getHeight() / 2) - 2);
	msg = "     Super Mega Ultra Turbo Maxi Extra RPG.                  Press space to start.             ";
	tw->SetText(msg);
	tw->SetLetterColor(LetterColor::WHITE);
	tw->SetBackgroundColor(BackgroundColor::BBLACK);
	tw->SetCloseKey(Key::space);
	Engine::getInstance()->setTextWindow(tw);
}

void MainState::Update()
{
	if (ngChosen)
	{
		if (newGame)
		{
			if (!tw->IsActive() && !startPressed) //Pantalla para indicar que escriban su nombre.
			{
				msg = "Write your name: ";
				tw->SetText(msg);
				tw->SetTextSpeed(100);
				tw->SetActive(true);
				tw->SetCloseKey(Key::returnK);
				tw->SetBlockInput(false);
				startPressed = true;
			} 
			if (startPressed && !nameEntered) //Captura del nombre.
			{
				if (InputManager::GetKeyUp(Key::A))
					name += InputManager::GetKey(Key::shift) ? "A" : "a";
				if (InputManager::GetKeyUp(Key::B))
					name += InputManager::GetKey(Key::shift) ? "B" : "b";
				if (InputManager::GetKeyUp(Key::C))
					name += InputManager::GetKey(Key::shift) ? "C" : "c";
				if (InputManager::GetKeyUp(Key::D))
					name += InputManager::GetKey(Key::shift) ? "D" : "d";
				if (InputManager::GetKeyUp(Key::E))
					name += InputManager::GetKey(Key::shift) ? "E" : "e";
				if (InputManager::GetKeyUp(Key::F))
					name += InputManager::GetKey(Key::shift) ? "F" : "f";
				if (InputManager::GetKeyUp(Key::G))
					name += InputManager::GetKey(Key::shift) ? "G" : "g";
				if (InputManager::GetKeyUp(Key::H))
					name += InputManager::GetKey(Key::shift) ? "H" : "h";
				if (InputManager::GetKeyUp(Key::I))
					name += InputManager::GetKey(Key::shift) ? "I" : "i";
				if (InputManager::GetKeyUp(Key::J))
					name += InputManager::GetKey(Key::shift) ? "J" : "j";
				if (InputManager::GetKeyUp(Key::K))
					name += InputManager::GetKey(Key::shift) ? "K" : "k";
				if (InputManager::GetKeyUp(Key::L))
					name += InputManager::GetKey(Key::shift) ? "L" : "l";
				if (InputManager::GetKeyUp(Key::M))
					name += InputManager::GetKey(Key::shift) ? "M" : "m";
				if (InputManager::GetKeyUp(Key::N))
					name += InputManager::GetKey(Key::shift) ? "N" : "n";
				if (InputManager::GetKeyUp(Key::O))
					name += InputManager::GetKey(Key::shift) ? "O" : "o";
				if (InputManager::GetKeyUp(Key::P))
					name += InputManager::GetKey(Key::shift) ? "P" : "p";
				if (InputManager::GetKeyUp(Key::Q))
					name += InputManager::GetKey(Key::shift) ? "Q" : "q";
				if (InputManager::GetKeyUp(Key::R))
					name += InputManager::GetKey(Key::shift) ? "R" : "r";
				if (InputManager::GetKeyUp(Key::S))
					name += InputManager::GetKey(Key::shift) ? "S" : "s";
				if (InputManager::GetKeyUp(Key::T))
					name += InputManager::GetKey(Key::shift) ? "T" : "t";
				if (InputManager::GetKeyUp(Key::U))
					name += InputManager::GetKey(Key::shift) ? "U" : "u";
				if (InputManager::GetKeyUp(Key::V))
					name += InputManager::GetKey(Key::shift) ? "V" : "v";
				if (InputManager::GetKeyUp(Key::W))
					name += InputManager::GetKey(Key::shift) ? "W" : "w";
				if (InputManager::GetKeyUp(Key::X))
					name += InputManager::GetKey(Key::shift) ? "X" : "x";
				if (InputManager::GetKeyUp(Key::Y))
					name += InputManager::GetKey(Key::shift) ? "Y" : "y";
				if (InputManager::GetKeyUp(Key::Z))
					name += InputManager::GetKey(Key::shift) ? "Z" : "z";
				if ((InputManager::GetKeyUp(Key::del) || InputManager::GetKeyUp(Key::backspace)) &&
					name.size() > 0)
					name.erase(name.size() - 1, 1);
				tw->SetText(msg + name);
			}
			if (startPressed && !nameEntered && !tw->IsActive()) //Selección de clase
			{
				nameEntered = true;
				msg = "Select your class.";
				tw->SetText(msg);
				tw->SetActive(true);
				tw->SetPosition((Engine::getInstance()->getWidth() / 2) - 40,
					(Engine::getInstance()->getHeight() / 2) - 20);
				tw->SetDimentions(21, 2);
				mw = new MenuWindow();
				mw->AddMenuItem("Warrior");
				mw->AddMenuItem("Paladin");
				mw->AddMenuItem("Barbarian");
				mw->AddMenuItem("Archer");
				mw->AddMenuItem("Thief");
				mw->AddMenuItem("Priest");
				mw->AddMenuItem("Mage");
				mw->AddMenuItem("Summoner");
				mw->SetBackgroundColor(BackgroundColor::BBLACK);
				mw->SetLetterColor(LetterColor::WHITE);
				mw->SetDimentions(14, 27);
				mw->SetPosition((Engine::getInstance()->getWidth() / 2) + 20,
					(Engine::getInstance()->getHeight() / 2) - 20);
				mw->SetActive(true);
				mw->SetCursorDownKey(Key::down);
				mw->SetCursorUpKey(Key::up);
				mw->SetCursorType(MenuWindow::CursorType::arrow);
				mw->SetCursorSelection(Key::returnK);
				Engine::getInstance()->setMenuWindow(mw);
				system("cls");
			}
			if (startPressed && nameEntered && mw) //Comprobacion de input
			{
				MenuWindow::MenuItem sel = mw->GetCursorSelection();
				if (sel.buttonPressed)
				{
					cls = (RPGClass)(sel.itemNumber);
					mw->SetActive(false);
					delete mw;
					mw = nullptr;
					Engine::getInstance()->setMenuWindow(nullptr);
					tw->SetDimentions(39, 2);
					tw->SetPosition((Engine::getInstance()->getWidth() / 2) - 19,
						(Engine::getInstance()->getHeight() / 2) - 2);
					msg = "Press return now to enter the world.";
					tw->SetText(msg);
					tw->SetActive(true);
					RPGCharacter* player = new RPGCharacter(cls, 1, name);
					player->SaveToFile();
					StaticVariables::playerParty.frontCenter = &player;
				}
			}
		}
		else
		{
			if (!tw->IsActive() && !startPressed) //Pantalla para seleccionar su archivo.
			{
				std::vector<std::string> fileNames;
				mw = new MenuWindow();
				WIN32_FIND_DATA data;
				HANDLE search = FindFirstFile("Save/*",&data);
				if (search != INVALID_HANDLE_VALUE)
				{
					std::string cdata = data.cFileName;
					if(cdata.find(".dat") != std::string::npos)
						fileNames.push_back(cdata);
					while (FindNextFile(search, &data))
					{
						cdata = data.cFileName;
						if (cdata.find(".dat") != std::string::npos)
							fileNames.push_back(cdata);
					}
				}
				mw->AddMenuItem("Back");
				for (auto &i : fileNames)
					mw->AddMenuItem(i);
				mw->SetBackgroundColor(BackgroundColor::BBLACK);
				mw->SetLetterColor(LetterColor::WHITE);
				int dimH = 4 + (3 * (fileNames.size() + 1));
				mw->SetDimentions(20, dimH);
				mw->SetPosition((Engine::getInstance()->getWidth() / 2) + 7,
					(Engine::getInstance()->getHeight() / 2) - (dimH/2));
				mw->SetCursorDownKey(Key::down);
				mw->SetCursorUpKey(Key::up);
				mw->SetCursorType(MenuWindow::CursorType::arrow);
				mw->SetCursorSelection(Key::returnK);
				mw->SetActive(true);
				msg = "Select your save.";
				tw->SetText(msg);
				tw->SetActive(true);
				tw->SetPosition((Engine::getInstance()->getWidth() / 2) - 40,
					(Engine::getInstance()->getHeight() / 2) - 20);
				tw->SetDimentions(21, 2);
				startPressed = true;
				Engine::getInstance()->setMenuWindow(mw);
			}
			if (startPressed && !nameEntered) //Manejo de inputs.
			{
				MenuWindow::MenuItem sel = mw->GetCursorSelection();
				if (sel.buttonPressed)
				{
					if (sel.itemNumber == 0)
					{
						startPressed = false;
						ngChosen = false;
					}
					else
					{
						RPGCharacter* player = new RPGCharacter(sel.name.erase(sel.name.length() - 4, 4));
						StaticVariables::playerParty.frontCenter = &player;
						tw->SetActive(false);
					}
					mw->SetActive(false);
					delete mw;
					mw = nullptr;
					Engine::getInstance()->setMenuWindow(nullptr);
				}
			}
			if (startPressed && !nameEntered && !tw->IsActive())
			{
				tw->SetDimentions(39, 2);
				tw->SetPosition((Engine::getInstance()->getWidth() / 2) - 19,
					(Engine::getInstance()->getHeight() / 2) - 2);
				tw->SetCloseKey(Key::returnK);
				msg = "Press return now to enter the world.";
				tw->SetText(msg);
				tw->SetActive(true);
				nameEntered = true;
			}
		}
		if (startPressed && nameEntered && !tw->IsActive())
		{
			StateManager::EndState();
			StateManager::ChangeState(new MapState());
		}
	}
	else
	{
		if (!selMenuSetup && !tw->IsActive())
		{
			mw = new MenuWindow();
			mw->AddMenuItem("New Game");
			mw->AddMenuItem("Load Game");
			mw->SetBackgroundColor(BackgroundColor::BBLACK);
			mw->SetLetterColor(LetterColor::WHITE);
			mw->SetDimentions(15, 3);
			mw->SetPosition((Engine::getInstance()->getWidth() / 2) + 7,
				(Engine::getInstance()->getHeight() / 2) - 2);
			mw->SetActive(true);
			mw->SetCursorDownKey(Key::down);
			mw->SetCursorUpKey(Key::up);
			mw->SetCursorType(MenuWindow::CursorType::arrow);
			mw->SetCursorSelection(Key::returnK);
			Engine::getInstance()->setMenuWindow(mw);
			selMenuSetup = true;
		}
		if (selMenuSetup)
		{
			MenuWindow::MenuItem sel = mw->GetCursorSelection();
			if (sel.buttonPressed)
			{
				if (sel.itemNumber == 0)
					newGame = true;
				mw->SetActive(false);
				delete mw;
				mw = nullptr;
				Engine::getInstance()->setMenuWindow(nullptr);
				ngChosen = true;
			}
		}
	}
}

void MainState::End()
{
	delete tw;
	tw = nullptr;
	Engine::getInstance()->setTextWindow(nullptr);
}
