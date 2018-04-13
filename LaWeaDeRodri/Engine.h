#pragma once
#include "TextWindow.h"
#include "MenuWindow.h"
#include "Window.h"
class Engine
{
public:
	Engine();
	~Engine();
	static Engine* getInstance();
	void app(const size_t& x, const size_t& y, const char* title, const bool& fullScreen);
	size_t getWidth() const;
	size_t getHeight() const;
	void setTextWindowActive(const bool& value);
	void setMenuWindowActive(const bool& value);
	void setTextWindow(TextWindow* const& val);
	void setMenuWindow(MenuWindow* const& val);
	TextWindow* getTextWindow() const;
	MenuWindow* getMenuWindow() const;
	void CloseApp();
private:
	static Engine* _singleton;//nop
	size_t _width, _height;
	bool _closing;
	Window* _windows[2] = { nullptr, nullptr };//wat
};

