#include "MainState.h"
#include <iostream>
#include "Engine.h"
#include "MenuWindow.h"


MainState::MainState()
{
}


MainState::~MainState()
{
}

TextWindow* mw;
void MainState::Start()
{
	mw = new TextWindow();
	mw->SetPosition(10, 10);
	mw->SetDimentions(15, 2);
	mw->SetBackgroundColor(BackgroundColor::BDARKYELLOW);
	mw->SetLetterColor(LetterColor::CYAN);
	mw->SetTextSpeed(2);
	Engine::getInstance()->setTextWindow(mw);
	Engine::getInstance()->setTextWindowActive(true);
	mw->SetText("texterino maxerino alderino");
	mw->SetCloseKey(Key::space);
	mw->SetUpScrollKey(Key::up);
	mw->SetDownScrollKey(Key::down);
	mw->CloseOnScrollEnd(true);
	mw->SetAutoScroll(false);
}

void MainState::Update()
{
}

void MainState::End()
{
}
