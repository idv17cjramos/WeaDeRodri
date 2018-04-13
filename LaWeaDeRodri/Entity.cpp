#include "Entity.h"
#include "HelperFunctions.h"
#include "SimplePool.h"


Entity::Entity()
{
	SimplePool::subscribe(this);//metes entidad
}


Entity::~Entity()
{
	SimplePool::deSubscribe(this);//quitas entidad
}

void Entity::draw()
{
	COORD pos;
	HANDLE console = getConsoleHandle();
	DWORD nonImportant;
	for (int i = 0; i < _ySize; ++i)
	{
		for (int j = 0; j < _xSize; ++j)
		{
			pos.X = _x + j;
			pos.Y = _y + i;
			SetConsoleCursorPosition(console,pos);
			SetConsoleTextAttribute(console, _colors[getAccessor(j, i, _xSize)]);
			WriteConsole(console, &_tiles[getAccessor(j, i, _xSize)], 1, &nonImportant, NULL);
		}
	}

}

void Entity::setSprite(char * const & tiles, unsigned short * const & colors, const size_t & hSize, const size_t & vSize)
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
	start();
	_initialized = true;
}

bool Entity::isInitialized()
{
	return _initialized;
}
