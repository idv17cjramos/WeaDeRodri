#include "MainState.h"
#include "MapState.h"
#include "StateManager.h"
MainState::MainState()
{
}


MainState::~MainState()
{
}


void MainState::Start()
{
	StateManager::ChangeState(new MapState());
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

}

void MainState::Update()
{
	//if(InputManager::GetKeyDown(Key::A))
	//	std::cout << " A" << std::endl;
	//if(InputManager::GetKeyUp(Key::C))
	//	std::cout << " C" << std::endl;
	//if(InputManager::GetKey(Key::U))
	//	std::cout << " U" << std::endl;

}

void MainState::End()
{
}
