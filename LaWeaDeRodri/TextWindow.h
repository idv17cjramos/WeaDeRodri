#pragma once
#include "Window.h"
#include <string>
#include <Windows.h>

class TextWindow :
	public Window
{
public:
	TextWindow();//contructor
	~TextWindow();//desturctor
	
	//Class Functions
	void draw() override;
	void update() override;
	void SetTextSpeed(const unsigned short& speed);
	void SetText(const std::string& text);
	void SetAutoScroll(const bool& val);
	void CloseOnScrollEnd(const bool& val);
	void SetScrollKey(const Key& val);
	void SetCloseKey(const Key& val);
	void SetUpScrollKey(const Key& val);
	void SetDownScrollKey(const Key& val);
	bool FinishedRendering();
private:
	std::string _string;
	unsigned short _speed, _scrollLine = 0, _maxScrollLines, _maxLineWidth;//unsigned shorts
	bool	_autoScroll,// 2 bools
			_closeOnScrollEnd;
	Key	_scrollKey,//4 keys
		_closeKey,
		_upScroll,
		_downScroll;
	INPUT_RECORD _input[32];//por que e sun arreglode 32
	int _currentLetter = 0;
};

