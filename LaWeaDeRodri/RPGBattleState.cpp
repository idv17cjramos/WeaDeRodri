#include "RPGBattleState.h"
#include "HelperFunctions.h"
#include "StateEnd.h"


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
	Engine::getInstance()->setMenuWindow(nullptr);
	if (partyDisplay)
		delete partyDisplay;
	if (tw)
		delete tw;
	Engine::getInstance()->setTextWindow(nullptr);
}

void RPGBattleState::StartBattle()
{
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
	enemNum = StaticVariables::enemies();
}

void RPGBattleState::MidBattle()
{
	if (!playerDone) //Players choose their actions.
	{
		battleStarted = true;
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
		RPGCharacter * ref;
		switch (currentSelection)
		{
		case 0:
		{
			ref = StaticVariables::enemyParty.frontCenter;
			break;
		}
		case 1:
		{
			ref = StaticVariables::enemyParty.frontLeft;
			break;
		}
		case 2:
		{
			ref = StaticVariables::enemyParty.frontRight;
			break;
		}
		case 3:
		{
			ref = StaticVariables::enemyParty.backLeft;
			break;
		}
		case 4:
		{
			ref = StaticVariables::enemyParty.backRight;
			break;
		}
		}
		if (ref == nullptr)
		{
			currentSelection = 0;
			enemiesDone = true;
			return;
		}
		else
		{
			currSkill.f = &RPGCharacter::UseSkill;
			currSkill.caller = ref;
			currSkill.dex =	ref->getDexterity();
			currSkill.skillNum = randomRange(0, ref->GetSkillAmmount());
			while (currSkill.target == nullptr)
			{
				int targ = randomRange(0, 5);
				currSkill.target = targ == 0 ? StaticVariables::playerParty.frontCenter : targ == 1 ?
					StaticVariables::enemyParty.frontLeft : targ == 2 ?
					StaticVariables::enemyParty.frontRight : targ == 3 ?
					StaticVariables::enemyParty.backLeft :
					StaticVariables::enemyParty.backRight;
			}
			turnQueue.push_back(currSkill);
			currSkill.f = nullptr;
			currSkill.caller = nullptr;
			currSkill.dex = 0;
			currSkill.skillNum = 0;
			currSkill.target = nullptr;
			++currentSelection;

		}
		
	}
	else if (playerDone && enemiesDone)
	{
		if (!startedRender)
			std::sort(turnQueue.begin(), turnQueue.begin(), &compareSkillUsage);
		if (tw->FinishedRendering())
			tw->SetCloseKey(Key::returnK);
		if (turnQueue.size() && (!tw->IsActive() || !startedRender))
		{
			SkillUsage usg = turnQueue.back();
			tw->SetText((usg.caller->*usg.f)(*usg.target, usg.skillNum));
			turnQueue.pop_back();
			tw->SetCloseKey(Key::KeysEnd);
			tw->SetActive(true);
			startedRender = true;
		}
		else if (!turnQueue.size() && tw->FinishedRendering())
		{
			playerDone = false;
			enemiesDone = false;
			displayingItems = displayingSkills = selectTarget = false;
			currentSelection = 0;
			startedRender = false;
		}

		if (StaticVariables::playerParty.frontCenter != nullptr && !StaticVariables::playerParty.frontCenter->isAlive())
			StateManager::ChangeState(new StateEnd());
		if (StaticVariables::playerParty.frontLeft != nullptr && !StaticVariables::playerParty.frontLeft->isAlive())
		{
			delete StaticVariables::playerParty.frontLeft;
			StaticVariables::playerParty.frontLeft = nullptr;
		}
		if (StaticVariables::playerParty.frontRight != nullptr && !StaticVariables::playerParty.frontRight->isAlive())
		{
			delete StaticVariables::playerParty.frontRight;
			StaticVariables::playerParty.frontRight = nullptr;
		}
		if (StaticVariables::playerParty.backLeft != nullptr && !StaticVariables::playerParty.backLeft->isAlive())
		{
			delete StaticVariables::playerParty.backLeft;
			StaticVariables::playerParty.backLeft = nullptr;
		}
		if (StaticVariables::playerParty.backRight != nullptr && !StaticVariables::playerParty.backRight->isAlive())
		{
			delete StaticVariables::playerParty.backRight;
			StaticVariables::playerParty.backRight = nullptr;
		}
		if (StaticVariables::enemyParty.frontCenter != nullptr && !StaticVariables::enemyParty.frontCenter->isAlive())
		{
			delete StaticVariables::enemyParty.frontCenter;
			StaticVariables::enemyParty.frontCenter = nullptr;
		}
		if (StaticVariables::enemyParty.frontLeft != nullptr && !StaticVariables::enemyParty.frontLeft->isAlive())
		{
			delete StaticVariables::enemyParty.frontLeft;
			StaticVariables::enemyParty.frontLeft = nullptr;
		}
		if (StaticVariables::enemyParty.frontRight != nullptr && !StaticVariables::enemyParty.frontRight->isAlive())
		{
			delete StaticVariables::enemyParty.frontRight;
			StaticVariables::enemyParty.frontRight = nullptr;
		}
		if (StaticVariables::enemyParty.backLeft != nullptr && !StaticVariables::enemyParty.backLeft->isAlive())
		{
			delete StaticVariables::enemyParty.backLeft;
			StaticVariables::enemyParty.backLeft = nullptr;
		}
		if (StaticVariables::enemyParty.backRight != nullptr && !StaticVariables::enemyParty.backRight->isAlive())
		{
			delete StaticVariables::enemyParty.backRight;
			StaticVariables::enemyParty.backRight = nullptr;
		}
		if (StaticVariables::enemyParty.frontCenter == nullptr && StaticVariables::enemyParty.frontLeft == nullptr &&
			StaticVariables::enemyParty.frontRight == nullptr && StaticVariables::enemyParty.backLeft == nullptr &&
			StaticVariables::enemyParty.backRight == nullptr)
		{
			battleEnded = true;
			playerWon = true;
			return;
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
	int totalXpPerPlayer = enemNum * 5 * StaticVariables::playerParty.frontCenter->getLevel() / StaticVariables::players();
	StaticVariables::playerParty.frontCenter->AddExperience(totalXpPerPlayer);
	if (StaticVariables::playerParty.backRight)
		StaticVariables::playerParty.backRight->AddExperience(totalXpPerPlayer);
	if (StaticVariables::playerParty.backLeft)
		StaticVariables::playerParty.backLeft->AddExperience(totalXpPerPlayer);
	if (StaticVariables::playerParty.frontRight)
		StaticVariables::playerParty.frontRight->AddExperience(totalXpPerPlayer);
	if (StaticVariables::playerParty.frontLeft)
		StaticVariables::playerParty.frontLeft->AddExperience(totalXpPerPlayer);
	StateManager::EndState();
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
				turnQueue.push_back(currSkill);
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
