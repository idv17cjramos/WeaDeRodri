#include "Entity.h"
#include "HelperFunctions.h"
#include "SimplePool.h"
#include "Engine.h"

Entity::Entity()
{

}


Entity::~Entity()
{
}

void Entity::draw()
{
	if (!_tiles || !_colors) return;
	COORD pos;
	HANDLE console = getConsoleHandle();
	DWORD nonImportant;
	for (int i = 0; i < _ySize; ++i)
	{
		for (int j = 0; j < _xSize; ++j)
		{
			pos.X = _x + j;
			pos.Y = _y + i;
			if (pos.X < 0 || pos.Y < 0 ||
				pos.X > Engine::getInstance()->getWidth() - 2 ||
				pos.Y > Engine::getInstance()->getHeight() - 2)
				continue;
			SetConsoleCursorPosition(console,pos);
			SetConsoleTextAttribute(console, _colors[getAccessor(j, i, _xSize)]);
			WriteConsole(console, &_tiles[getAccessor(j, i, _xSize)], 1, &nonImportant, NULL);
		}
	}
}

void Entity::setSprite(unsigned char * const & tiles, unsigned short * const & colors, const size_t & hSize, const size_t & vSize)
{
	_tiles = tiles;
	_colors = colors;
	_xSize = hSize;
	_ySize = vSize;
}

void Entity::move(const int & x, const int & y)
{
	_x += x;
	_y += y;
}

void Entity::setX(const int & x)
{
	_x = x;
}

void Entity::setY(const int & y)
{
	_y = y;
}

void Entity::setXY(const int & x, const int & y)
{
	_x = x;
	_y = y;
}

void Entity::start()
{
}

void Entity::update()
{
}

void Entity::destroy()
{
}

void Entity::Init()
{
	SimplePool::subscribe(this);//metes entidad
	start();
	_initialized = true;
}

bool Entity::isInitialized()
{
	return _initialized;
}
