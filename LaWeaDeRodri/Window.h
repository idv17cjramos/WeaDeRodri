#pragma once
#include "Definitions.h"

class Window
{
public:
	Window();
	virtual ~Window();
	virtual void draw();
	virtual void update();
	void SetPosition(const size_t& x, const size_t& y);
	void SetDimentions(const size_t& w, const size_t& h);
	bool IsActive();
	void SetActive(const bool& value);
	void SetBackgroundColor(const BackgroundColor& color);
	void SetLetterColor(const LetterColor& color);
protected:
	size_t _x, _y, _width, _height;
	BackgroundColor _backgroundColor;
	LetterColor _letterColor;
	bool _isActive;
	INPUT_RECORD _input[32];//32 para no tener tantos inputs
private:
	const unsigned char borders[6]{ 187, 188, 200, 201, 186, 205 };
	enum {
		topRight = 0,
		bottomRight,
		bottomLeft,
		topLeft,
		vertical,
		horizontal
	};
};

