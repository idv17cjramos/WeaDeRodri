#pragma once
#include "Entity.h"
#include <list>

class SimplePool
{
public:
	SimplePool();
	~SimplePool();
	static void subscribe(Entity* const& obj);
	static void deSubscribe(Entity* const& obj);
	static void drawAll();
private:
	static std::list<Entity*> _pool;
};

