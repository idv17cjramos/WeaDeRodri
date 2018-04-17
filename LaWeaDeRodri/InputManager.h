#pragma once
#include <Windows.h>
#include "Definitions.h"
class InputManager
{
public:
	InputManager();
	~InputManager();
	static bool GetKeyDown(const Key& key);
	static bool GetKeyUp(const Key& key);
	static bool GetKey(const Key& key);
	static void Update();
private:
	static INPUT_RECORD _input[1000];
	static HANDLE _inputHandle;
	static bool _totalKeysState[Key::KeysEnd];//Representa el tamaño máximo del arreglo
	static DWORD _eventsRead;
};

