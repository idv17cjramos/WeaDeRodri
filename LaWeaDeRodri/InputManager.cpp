#include "InputManager.h"


INPUT_RECORD InputManager::_input[1000];
HANDLE InputManager::_inputHandle = nullptr;
bool InputManager::_totalKeysState[Key::KeysEnd];
DWORD InputManager::_eventsRead;
InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

bool InputManager::GetKeyDown(const Key & key)
{
	for (DWORD i = 0; i < _eventsRead; ++i)
	{
		if (_input[i].EventType == KEY_EVENT &&
			_input[i].Event.KeyEvent.wVirtualKeyCode == key &&
			_input[i].Event.KeyEvent.bKeyDown &&
			!_totalKeysState[key])
		{
			_totalKeysState[key] = true;
			return true;
		}
		else if (_input[i].EventType == KEY_EVENT &&
			_input[i].Event.KeyEvent.wVirtualKeyCode == key &&
			!_input[i].Event.KeyEvent.bKeyDown &&
			_totalKeysState[key])
		{
			_totalKeysState[key] = false;
			return false;
		}
	}
	return false;
}

bool InputManager::GetKeyUp(const Key & key)
{
	for (DWORD i = 0; i < _eventsRead; ++i)
	{
		if (_input[i].EventType == KEY_EVENT &&
			_input[i].Event.KeyEvent.wVirtualKeyCode == key &&
			!_input[i].Event.KeyEvent.bKeyDown)
		{
			_totalKeysState[key] = false;
			return true;
		}
	}
	return false;
}

bool InputManager::GetKey(const Key & key)
{
	for (DWORD i = 0; i < _eventsRead; ++i)
	{
		if (_input[i].EventType == KEY_EVENT &&
			_input[i].Event.KeyEvent.wVirtualKeyCode == key &&
			_input[i].Event.KeyEvent.bKeyDown)
		{
			_totalKeysState[key] = true;
			return true;
		}
	}
	return false;
}

void InputManager::Update()
{
	if (!_inputHandle) _inputHandle = GetStdHandle(STD_INPUT_HANDLE);
	GetNumberOfConsoleInputEvents(_inputHandle, &_eventsRead);
	if (_eventsRead)
		ReadConsoleInput(_inputHandle, _input, 1000, &_eventsRead);
}
