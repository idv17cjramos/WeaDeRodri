#include "Window.h"
#include "Engine.h"
#include "HelperFunctions.h"

Window::Window()
{
	_x = _y = _width = _height = 0;
	_isActive = false;
}


Window::~Window()
{
}

void Window::draw()
{
	if (!_isActive)
		return;
	COORD pos;
	HANDLE console = getConsoleHandle();
	DWORD nonImportant;
	SetConsoleTextAttribute(console, _backgroundColor | _letterColor);
	pos.X = _x;
	pos.Y = _y;
	SetConsoleCursorPosition(console, pos);
	WriteConsole(console, &borders[topLeft], 1, &nonImportant, NULL);
	pos.X = _x + _width;
	pos.Y = _y;
	SetConsoleCursorPosition(console, pos);
	WriteConsole(console, &borders[topRight], 1, &nonImportant, NULL);
	pos.X = _x;
	pos.Y = _y + _height;
	SetConsoleCursorPosition(console, pos);
	WriteConsole(console, &borders[bottomLeft], 1, &nonImportant, NULL);
	pos.X = _x + _width;
	pos.Y = _y + _height;
	SetConsoleCursorPosition(console, pos);
	WriteConsole(console, &borders[bottomRight], 1, &nonImportant, NULL);
	for (int i = 1; i < _width; ++i)
	{
		pos.X = _x + i;
		pos.Y = _y;
		SetConsoleCursorPosition(console, pos);
		WriteConsole(console, &borders[horizontal], 1, &nonImportant, NULL);
		pos.Y = _y + _height;
		SetConsoleCursorPosition(console, pos);
		WriteConsole(console, &borders[horizontal], 1, &nonImportant, NULL);
	}
	for (int i = 1; i < _height; ++i)
	{
		pos.X = _x;
		pos.Y = _y + i;
		SetConsoleCursorPosition(console, pos);
		WriteConsole(console, &borders[vertical], 1, &nonImportant, NULL);
		pos.X = _x + _width;
		SetConsoleCursorPosition(console, pos);
		WriteConsole(console, &borders[vertical], 1, &nonImportant, NULL);
	}
	for (int i = 1; i < _width; ++i)
	{
		for (int j = 1; j < _height; ++j)
		{
			pos.X = _x + i;
			pos.Y = _y + j;
			SetConsoleCursorPosition(console, pos);
			WriteConsole(console, "\0", 1, &nonImportant, NULL);
		}
	}
}

void Window::update()
{
}

void Window::SetPosition(const size_t & x, const size_t & y)
{
	if (x + _width > Engine::getInstance()->getWidth() ||
		y + _height > Engine::getInstance()->getHeight())
		return;
	_x = x;
	_y = y;
}

void Window::SetDimentions(const size_t & w, const size_t & h)
{
	if (_x + w > Engine::getInstance()->getWidth() ||
		_y + h > Engine::getInstance()->getHeight())
		return;
	_width = w;
	_height = h;
}

bool Window::IsActive()
{
	return _isActive;
}

void Window::SetActive(const bool & value)
{
	_isActive = value;
}

void Window::SetBackgroundColor(const BackgroundColor & color)
{
	_backgroundColor = color;
}

void Window::SetLetterColor(const LetterColor & color)
{
	_letterColor = color;
}
