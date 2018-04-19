#include "MenuWindow.h"
#include "HelperFunctions.h"
#include <algorithm>
#include "Engine.h"

MenuWindow::MenuWindow()
{
}

MenuWindow::~MenuWindow()
{
}

void MenuWindow::update()
{
	if (!_isActive) return;
	DWORD numInputRead;//Bits bytes words 8bytes dword 16bytes
	GetNumberOfConsoleInputEvents(GetStdHandle(STD_INPUT_HANDLE), &numInputRead);
	if (numInputRead)//el nuemro de inputs
	{
		if (_blockInput)
			ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), _input, 32, &numInputRead);//agarra std input handle, va a ver cuantos inputs lee, almacena ciert numero,almacena los inputs, no el numerod e inpuits
		else
			PeekConsoleInput(GetStdHandle(STD_INPUT_HANDLE), _input, 32, &numInputRead);
		for (DWORD i = 0; i < numInputRead; ++i)
		{
			if (_input[i].EventType == KEY_EVENT)//ve el key que est[a apretado y hasce algo 
			{
				WORD keyC = _input[i].Event.KeyEvent.wVirtualKeyCode;
				bool keypressed = _input[i].Event.KeyEvent.bKeyDown;
				if (keyC == _up && !keypressed && 
					_selectedItem > 0 && !_itemSelected)
				{
					--_selectedItem; 
					Engine::getInstance()->ReportInteraction();
				}
				if (keyC == _down && !keypressed && 
					_selectedItem < _menuItems.size() - 1 && !_itemSelected)
				{
					++_selectedItem; 
					Engine::getInstance()->ReportInteraction();
				}
				if (keyC == _selection && !keypressed && !_itemSelected)
				{
					//_isActive = false; 
					_itemSelected = true;
					Engine::getInstance()->ReportInteraction();
				}
			}
		}
	}
}

void MenuWindow::draw()
{
	Window::draw();
	if (!_isActive) return;
	COORD pos;
	DWORD nonImportant;
	HANDLE console = getConsoleHandle();
	unsigned short attribs;
	if (_menuItems.size() <= 0) return;
	int spacingBetweenItems = (int)(_height - 3) / (int)_menuItems.size();
	if (spacingBetweenItems < 1)
		pos.Y = (SHORT)_y + ((SHORT)spacingBetweenItems + 1);
	else
		pos.Y = (SHORT)_y + (SHORT)spacingBetweenItems;
	size_t item = 0;
	for (auto &i : _menuItems)
	{
		pos.X = (SHORT)_x + 1;
		SetConsoleCursorPosition(console, pos);
		if (_type == CursorType::arrow && _selectedItem == item)
		{
			WriteConsole(console, &_arrowCursorPRight, 1, &nonImportant, NULL);
			pos.X += 2;
			SetConsoleCursorPosition(console, pos);
		}
		if (_type == CursorType::underscore && _selectedItem == item)
			attribs = _letterColor | _backgroundColor | ExtraOptions::underscore;
		else
			attribs = _letterColor | _backgroundColor;
		SetConsoleTextAttribute(console, attribs);
		WriteConsole(console, i.data(), (DWORD)i.length(), &nonImportant, NULL);
		if (spacingBetweenItems < 1)
			pos.Y += ((SHORT)spacingBetweenItems + 1);
		else
			pos.Y += (SHORT)spacingBetweenItems;
		++item;
	}
}

void MenuWindow::AddMenuItem(const std::string & item)
{
	_menuItems.push_back(item);
}

void MenuWindow::RemoveMenuItem(const std::string & item)
{
	_menuItems.remove(item);
}

void MenuWindow::SetCursorType(const CursorType & type)
{
	_type = type;
}

void MenuWindow::ShouldBlink(const bool & blink)
{
	_blink = blink;
}

void MenuWindow::SetCursorUpKey(const Key & key)
{
	_up = key;
}

void MenuWindow::SetCursorDownKey(const Key & key)
{
	_down = key;
}

void MenuWindow::SetCursorSelection(const Key & key)
{
	_selection = key;
}

MenuWindow::MenuItem MenuWindow::GetCursorSelection()
{
	int j = 0;
	std::string retVal;
	if (_menuItems.size() == 0)
		return MenuItem{ false, "", 0 };
	for (auto &i : _menuItems)
	{
		if (j == _selectedItem)
		{
			retVal = i;
			break;
		}
		++j;
	}
	bool valSaved = _itemSelected;
	_itemSelected = false;
	return MenuItem { valSaved, retVal, _selectedItem };
}
