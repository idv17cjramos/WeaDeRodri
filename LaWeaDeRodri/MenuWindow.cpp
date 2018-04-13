#include "MenuWindow.h"
#include "HelperFunctions.h"
#include <algorithm>

MenuWindow::MenuWindow()
{
}

MenuWindow::~MenuWindow()
{
}

void MenuWindow::update()
{
}

void MenuWindow::draw()
{
	Window::draw();
	if (!_isActive) return;
	COORD pos;
	DWORD nonImportant;
	HANDLE console = getConsoleHandle();
	for (auto &i : _menuItems)
	{
		
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
	for (auto &i : _menuItems)
	{
		if (j == _selectedItem)
		{
			retVal = i;
		}
		++j;
	}
	return MenuItem { _itemSelected, retVal, _selectedItem };
}
