#pragma once
#include "Window.h"
#include "Definitions.h"
#include <string>
#include <list>
class MenuWindow :
	public Window
{
public:
	typedef enum {
		underscore,
		arrow
	} CursorType;
	typedef struct {
		bool buttonPressed;
		std::string name;
		size_t itemNumber;
	}  MenuItem;
	MenuWindow();
	~MenuWindow();
	void update() override;
	void draw() override;
	void AddMenuItem(const std::string& item);
	void RemoveMenuItem(const std::string& item);
	void SetCursorType(const CursorType& type);
	void ShouldBlink(const bool& blink);
	void SetCursorUpKey(const Key& key);
	void SetCursorDownKey(const Key& key);
	void SetCursorSelection(const Key& key);
	MenuItem GetCursorSelection();
private:
	std::list<std::string> _menuItems;
	size_t _selectedItem = 0;
	CursorType _type = underscore;
	bool _blink = false,
		 _itemSelected = false;
	Key _selection,
		_up,
		_down;
	char arrowCursorPRight = 175;
	char arrowCursorPLeft = 174;
};

