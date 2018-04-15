#pragma once
#include <Windows.h>

class Entity {
public:
	Entity();
	virtual ~Entity();//Virtual es para que puedas volver a escribir los contenidos de la función
	void draw();
	void setSprite(char* const& tiles, unsigned short* const& colors, const size_t& hSize, const size_t& vSize);
	void move(const int& x, const int& y);
	void setX(const int& x);
	void setY(const int& y);
	void setXY(const int& x, const int& y);
	virtual void start();
	virtual void update();
	virtual void destroy();
	void Init();
	bool isInitialized();
protected:
	int _x, _y;
	char* _tiles = nullptr;
	unsigned short* _colors = nullptr;
	size_t _xSize, _ySize;
private:
	bool _initialized = false;
};