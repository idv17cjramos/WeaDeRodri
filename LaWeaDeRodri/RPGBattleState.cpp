#include "RPGBattleState.h"



RPGBattleState::RPGBattleState()
{
}


RPGBattleState::~RPGBattleState()
{
}

void RPGBattleState::Start()
{
	StaticVariables::GenerateEnemyParty();
}

void RPGBattleState::Update()
{
	if(!battleStarted)
		StartBattle();
	if (battleStarted)
		MidBattle();
	if (battleStarted && battleEnded)
		EndBattle();
}

void RPGBattleState::End()
{
	if (mw)
		delete mw;
	if (partyDisplay)
		delete partyDisplay;
	if (tw)
		delete tw;
}

void RPGBattleState::StartBattle()
{
	//TODO: Set textWindows.
	battleStarted = true;
}

void RPGBattleState::MidBattle()
{
	if (!playerDone) //Players choose their actions.
	{
		RPGCharacter * ref;
		switch (currentSelection)
		{
		case 0:
		{
			ref = StaticVariables::playerParty.frontCenter;
			break;
		}
		case 1:
		{
			ref = StaticVariables::playerParty.frontLeft;
			break;
		}
		case 2:
		{
			ref = StaticVariables::playerParty.frontRight;
			break;
		}
		case 3:
		{
			ref = StaticVariables::playerParty.backLeft;
			break;
		}
		case 4:
		{
			ref = StaticVariables::playerParty.backRight;
			break;
		}
		default:
		{
			ref = nullptr;
			break;
		}
		}
		if (ref == nullptr)
		{
			playerDone = true;
			return;
		}
		if (!displayingItems && !displayingSkills && !selectTarget)
			DisplayOptions();
		if (displayingItems)
			DisplayItems(ref);
		if (displayingSkills)
			DisplaySkills(ref);
		if (selectTarget)
			SelectTarget(StaticVariables::enemyParty);
	}
	else if (playerDone && !enemiesDone)
	{
		//TODO:Set enemy behaviour.
		switch (currentSelection)
		{
		case 0:
		{
			break;
		}
		case 1:
		{
			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			break;
		}
		case 4:
		{
			break;
		}
		default:
		{
			break;
		}
		}
		
	}
	else if (playerDone && enemiesDone)
	{
		//TODO: Execute commands.
		//TODO: If all enemies or or allies are dead, finish battle.
		playerDone = false; 
		enemiesDone = false;
	}
	//TODO: draw Info display.
}

void RPGBattleState::EndBattle()
{
	//TODO: Gain experience and Ferrum
}

void RPGBattleState::DisplaySkills(RPGCharacter * chr)
{
	if (!menuSetup)
	{
		mw = new MenuWindow();
		mw->SetBackgroundColor(BackgroundColor::BBLACK);
		mw->SetLetterColor(LetterColor::WHITE);
		mw->AddMenuItem("Back");
		size_t skills = chr->GetSkillAmmount();
		for (size_t i = 0; i < skills; ++i)
			mw->AddMenuItem(chr->GetSkillName(i));
		mw->SetDimentions(14, 27);
		mw->SetPosition((Engine::getInstance()->getWidth() - 16),
			(Engine::getInstance()->getHeight() / 2) - 18);
		mw->SetActive(true);
		mw->SetCursorDownKey(Key::down);
		mw->SetCursorUpKey(Key::up);
		mw->SetCursorType(MenuWindow::CursorType::arrow);
		mw->SetCursorSelection(Key::returnK);
		Engine::getInstance()->setMenuWindow(mw);
		menuSetup = true;
	}
	else
	{
		MenuWindow::MenuItem sel = mw->GetCursorSelection();
		if (sel.buttonPressed)
		{
			displayingSkills = false;
			menuSetup = false;
			if(sel.itemNumber != 0)
			{
				currSkill.f = &RPGCharacter::UseSkill; 
				currSkill.skillNum = sel.itemNumber - 1;
				currSkill.dex = chr->getDexterity();
				currSkill.caller = chr;
				selectTarget = true;
			}
			if (mw)
				delete mw;
			mw = nullptr;
			Engine::getInstance()->setMenuWindow(nullptr);
		}
	}
}

void RPGBattleState::DisplayItems(RPGCharacter * chr)
{
	//TODO: Display items.
	if (!menuSetup)
	{

	}
	else
	{

	}
}

void RPGBattleState::SelectTarget(Party & p)
{
	if (!menuSetup)
	{
		mw = new MenuWindow();
		mw->SetBackgroundColor(BackgroundColor::BBLACK);
		mw->SetLetterColor(LetterColor::WHITE);
		mw->AddMenuItem("Back");
		if (p.backLeft)
			mw->AddMenuItem(p.backLeft->GetName());
		else mw->AddMenuItem("");
		if (p.backRight)
			mw->AddMenuItem(p.backRight->GetName());
		else mw->AddMenuItem("");
		if (p.frontCenter)
			mw->AddMenuItem(p.frontCenter->GetName());
		else mw->AddMenuItem("");
		if (p.frontLeft)
			mw->AddMenuItem(p.frontLeft->GetName());
		else mw->AddMenuItem("");
		if (p.frontRight)
			mw->AddMenuItem(p.frontRight->GetName());
		else mw->AddMenuItem("");
		mw->SetDimentions(14, 27);
		mw->SetPosition((Engine::getInstance()->getWidth() - 16),
			(Engine::getInstance()->getHeight() / 2) - 18);
		mw->SetActive(true);
		mw->SetCursorDownKey(Key::down);
		mw->SetCursorUpKey(Key::up);
		mw->SetCursorType(MenuWindow::CursorType::arrow);
		mw->SetCursorSelection(Key::returnK);
		Engine::getInstance()->setMenuWindow(mw);
		menuSetup = true;
	}
	else
	{
		MenuWindow::MenuItem sel = mw->GetCursorSelection();
		if (sel.buttonPressed && sel.name != "")
		{
			selectTarget = false;
			menuSetup = false;
			if (sel.itemNumber != 0)
			{
				switch (sel.itemNumber)
				{
				case 1:
					currSkill.target = p.backLeft;
					break;
				case 2:
					currSkill.target = p.backRight;
					break;
				case 3:
					currSkill.target = p.frontCenter;
					break;
				case 4:
					currSkill.target = p.frontLeft;
					break;
				case 5:
					currSkill.target = p.frontRight;
					break;
				}
				turnQueue.push(currSkill);
				currSkill.caller = nullptr;
				currSkill.target = nullptr;
				currSkill.f = nullptr;
				currSkill.dex = 0;
				currSkill.skillNum = 0;
				++currentSelection;
				selectTarget = false;
			}
			if (mw)
				delete mw;
			mw = nullptr;
			Engine::getInstance()->setMenuWindow(nullptr);
		}
	}
}

void RPGBattleState::DisplayOptions()
{
	if (!menuSetup)
	{
		mw = new MenuWindow();
		mw->SetBackgroundColor(BackgroundColor::BBLACK);
		mw->SetLetterColor(LetterColor::WHITE);
		mw->AddMenuItem("Use Skill.");
		mw->AddMenuItem("Use Item.");
		mw->AddMenuItem("Talk.");
		mw->SetDimentions(14, 27);
		mw->SetPosition((Engine::getInstance()->getWidth() - 16),
			(Engine::getInstance()->getHeight() / 2) - 18);
		mw->SetActive(true);
		mw->SetCursorDownKey(Key::down);
		mw->SetCursorUpKey(Key::up);
		mw->SetCursorType(MenuWindow::CursorType::arrow);
		mw->SetCursorSelection(Key::returnK);
		Engine::getInstance()->setMenuWindow(mw);
		menuSetup = true;
	}
	else
	{
		MenuWindow::MenuItem sel = mw->GetCursorSelection();
		if (sel.buttonPressed)
		{
			menuSetup = false;
			if (sel.itemNumber == 0)
				displayingSkills = true;
			else if (sel.itemNumber == 1)
				displayingItems = true;
			if (mw)
				delete mw;
			mw = nullptr;
			Engine::getInstance()->setMenuWindow(nullptr);
		}
	}
}
