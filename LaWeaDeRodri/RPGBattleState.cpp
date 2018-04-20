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
	tw = new TextWindow();
	tw->SetDimentions(Engine::getInstance()->getWidth() - 20, 10);
	tw->SetPosition(1, Engine::getInstance()->getHeight() - 12);
	tw->SetTextSpeed(2);
	tw->SetLetterColor(LetterColor::WHITE);
	tw->SetBackgroundColor(BackgroundColor::BBLACK);
	tw->SetActive(true);
	Engine::getInstance()->setTextWindow(tw);

	partyDisplay = new TextWindow();
	partyDisplay->SetDimentions(Engine::getInstance()->getWidth() - 20, 30);
	partyDisplay->SetPosition(1, 1);
	partyDisplay->SetTextSpeed(1000);
	partyDisplay->SetLetterColor(LetterColor::WHITE);
	partyDisplay->SetBackgroundColor(BackgroundColor::BBLACK);
	partyDisplay->SetActive(true);
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
			currentSelection = 0;
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
			SelectTarget();
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
			enemiesDone = true;
			break;
		}
		}
		
	}
	else if (playerDone && enemiesDone)
	{
		if (turnQueue.size() && tw->FinishedRendering())
		{
			tw->SetText((*turnQueue.back().caller.*turnQueue.back().f)(*turnQueue.back().target, turnQueue.back().skillNum));
			turnQueue.pop();
		}
		else if(!turnQueue.size() && tw->FinishedRendering())
		{
			playerDone = false; 
			enemiesDone = false;
			displayingItems = displayingSkills = selectTarget = false;
			currentSelection = 0;
		}
	}

#pragma region PartyDisplay
	std::string partiesData;
	if (StaticVariables::enemyParty.backLeft)
	{
		partiesData += StaticVariables::enemyParty.backLeft->GetName();
		partiesData += " ";
		partiesData += std::to_string(StaticVariables::enemyParty.backLeft->getLevel());
		partiesData += " ";
		partiesData += std::to_string(StaticVariables::enemyParty.backLeft->gethp());
		partiesData += " ";
		partiesData += std::to_string(StaticVariables::enemyParty.backLeft->getmp());
		partiesData += "\n";
	}
	else partiesData += "\n";
	if (StaticVariables::enemyParty.backRight)
	{
		partiesData += StaticVariables::enemyParty.backRight->GetName();
		partiesData += " ";
		partiesData += std::to_string(StaticVariables::enemyParty.backRight->getLevel());
		partiesData += " ";
		partiesData += std::to_string(StaticVariables::enemyParty.backRight->gethp());
		partiesData += " ";						   
		partiesData += std::to_string(StaticVariables::enemyParty.backRight->getmp());
		partiesData += "\n";
	}
	else partiesData += "\n";
	if (StaticVariables::enemyParty.frontCenter)
	{
		partiesData += StaticVariables::enemyParty.frontCenter->GetName();
		partiesData += " ";						   
		partiesData += std::to_string(StaticVariables::enemyParty.frontCenter->getLevel());
		partiesData += " ";						   
		partiesData += std::to_string(StaticVariables::enemyParty.frontCenter->gethp());
		partiesData += " ";						   
		partiesData += std::to_string(StaticVariables::enemyParty.frontCenter->getmp());
		partiesData += "\n";
	}
	else partiesData += "\n";
	if (StaticVariables::enemyParty.frontLeft)
	{
		partiesData += StaticVariables::enemyParty.frontLeft->GetName();
		partiesData += " ";						   
		partiesData += std::to_string(StaticVariables::enemyParty.frontLeft->getLevel());
		partiesData += " ";						   
		partiesData += std::to_string(StaticVariables::enemyParty.frontLeft->gethp());
		partiesData += " ";						   
		partiesData += std::to_string(StaticVariables::enemyParty.frontLeft->getmp());
		partiesData += "\n";
	}
	else partiesData += "\n";
	if (StaticVariables::enemyParty.frontRight)
	{
		partiesData += StaticVariables::enemyParty.frontRight->GetName();
		partiesData += " ";						   
		partiesData += std::to_string(StaticVariables::enemyParty.frontRight->getLevel());
		partiesData += " ";						  
		partiesData += std::to_string(StaticVariables::enemyParty.frontRight->gethp());
		partiesData += " ";						  
		partiesData += std::to_string(StaticVariables::enemyParty.frontRight->getmp());
		partiesData += "\n";
	}
	else partiesData += "\n";
	if (StaticVariables::playerParty.backLeft)
	{
		partiesData += StaticVariables::playerParty.backLeft->GetName();
		partiesData += " ";				
		partiesData += std::to_string(StaticVariables::playerParty.backLeft->getLevel());
		partiesData += " ";				
		partiesData += std::to_string(StaticVariables::playerParty.backLeft->gethp());
		partiesData += " ";			
		partiesData += std::to_string(StaticVariables::playerParty.backLeft->getmp());
		partiesData += "\n";
	}
	else partiesData += "\n";
	if (StaticVariables::playerParty.backRight)
	{
		partiesData += StaticVariables::playerParty.backRight->GetName();
		partiesData += " ";			
		partiesData += std::to_string(StaticVariables::playerParty.backRight->getLevel());
		partiesData += " ";			
		partiesData += std::to_string(StaticVariables::playerParty.backRight->gethp());
		partiesData += " ";			
		partiesData += std::to_string(StaticVariables::playerParty.backRight->getmp());
		partiesData += "\n";
	}
	else partiesData += "\n";
	if (StaticVariables::playerParty.frontCenter)
	{
		partiesData += StaticVariables::playerParty.frontCenter->GetName();
		partiesData += " ";			
		partiesData += std::to_string(StaticVariables::playerParty.frontCenter->getLevel());
		partiesData += " ";			
		partiesData += std::to_string(StaticVariables::playerParty.frontCenter->gethp());
		partiesData += " ";			
		partiesData += std::to_string(StaticVariables::playerParty.frontCenter->getmp());
		partiesData += "\n";
	}
	else partiesData += "\n";
	if (StaticVariables::playerParty.frontLeft)
	{
		partiesData += StaticVariables::playerParty.frontLeft->GetName();
		partiesData += " ";				
		partiesData += std::to_string(StaticVariables::playerParty.frontLeft->getLevel());
		partiesData += " ";				
		partiesData += std::to_string(StaticVariables::playerParty.frontLeft->gethp());
		partiesData += " ";			
		partiesData += std::to_string(StaticVariables::playerParty.frontLeft->getmp());
		partiesData += "\n";
	}
	else partiesData += "\n";
	if (StaticVariables::playerParty.frontRight)
	{
		partiesData += StaticVariables::playerParty.frontRight->GetName();
		partiesData += " ";			
		partiesData += std::to_string(StaticVariables::playerParty.frontRight->getLevel());
		partiesData += " ";			
		partiesData += std::to_string(StaticVariables::playerParty.frontRight->gethp());
		partiesData += " ";			
		partiesData += std::to_string(StaticVariables::playerParty.frontRight->getmp());
		partiesData += "\n";
	}
	else partiesData += "\n";
	partyDisplay->SetText(partiesData);
	partyDisplay->draw();
#pragma endregion
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
		mw = new MenuWindow();
		mw->SetBackgroundColor(BackgroundColor::BBLACK);
		mw->SetLetterColor(LetterColor::WHITE);
		mw->AddMenuItem("Back");
		size_t skills = chr->GetItemNames().size();
		for (size_t i = 0; i < skills; ++i)
			mw->AddMenuItem(chr->GetItemNames().at(i));
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
			displayingItems = false;
			menuSetup = false;
			if (sel.itemNumber != 0)
			{
				chr->ConsumeItem(sel.itemNumber - 1);
				++currentSelection;
			}
			if (mw)
				delete mw;
			mw = nullptr;
			Engine::getInstance()->setMenuWindow(nullptr);
		}
	}
}

void RPGBattleState::SelectTarget()
{
	if (!menuSetup)
	{
		mw = new MenuWindow();
		mw->SetBackgroundColor(BackgroundColor::BBLACK);
		mw->SetLetterColor(LetterColor::WHITE);
		mw->AddMenuItem("Back");
		if (StaticVariables::enemyParty.backLeft)
			mw->AddMenuItem(StaticVariables::enemyParty.backLeft->GetName());
		else mw->AddMenuItem("");
		if (StaticVariables::enemyParty.backRight)
			mw->AddMenuItem(StaticVariables::enemyParty.backRight->GetName());
		else mw->AddMenuItem("");
		if (StaticVariables::enemyParty.frontCenter)
			mw->AddMenuItem(StaticVariables::enemyParty.frontCenter->GetName());
		else mw->AddMenuItem("");
		if (StaticVariables::enemyParty.frontLeft)
			mw->AddMenuItem(StaticVariables::enemyParty.frontLeft->GetName());
		else mw->AddMenuItem("");
		if (StaticVariables::enemyParty.frontRight)
			mw->AddMenuItem(StaticVariables::enemyParty.frontRight->GetName());
		else mw->AddMenuItem("");
		if (StaticVariables::playerParty.backLeft)
			mw->AddMenuItem(StaticVariables::playerParty.backLeft->GetName());
		else mw->AddMenuItem("");
		if (StaticVariables::playerParty.backRight)
			mw->AddMenuItem(StaticVariables::playerParty.backRight->GetName());
		else mw->AddMenuItem("");
		if (StaticVariables::playerParty.frontCenter)
			mw->AddMenuItem(StaticVariables::playerParty.frontCenter->GetName());
		else mw->AddMenuItem("");
		if (StaticVariables::playerParty.frontLeft)
			mw->AddMenuItem(StaticVariables::playerParty.frontLeft->GetName());
		else mw->AddMenuItem("");
		if (StaticVariables::playerParty.frontRight)
			mw->AddMenuItem(StaticVariables::playerParty.frontRight->GetName());
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
					currSkill.target = StaticVariables::enemyParty.backLeft;
					break;
				case 2:
					currSkill.target = StaticVariables::enemyParty.backRight;
					break;
				case 3:
					currSkill.target = StaticVariables::enemyParty.frontCenter;
					break;
				case 4:
					currSkill.target = StaticVariables::enemyParty.frontLeft;
					break;
				case 5:
					currSkill.target = StaticVariables::enemyParty.frontRight;
					break;
				case 6:
					currSkill.target = StaticVariables::playerParty.backLeft;
					break;
				case 7:
					currSkill.target = StaticVariables::playerParty.backRight;
					break;
				case 8:
					currSkill.target = StaticVariables::playerParty.frontCenter;
					break;
				case 9:
					currSkill.target = StaticVariables::playerParty.frontLeft;
					break;
				case 10:
					currSkill.target = StaticVariables::playerParty.frontRight;
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
