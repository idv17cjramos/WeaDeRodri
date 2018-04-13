#include "SimplePool.h"
/*le indicas que va a ser la inicializacion, que va a ser la actualozacion, la v a ahacer autmaticamente, eso es uando Simplepool dentro dle main loop*/

std::list<Entity*> SimplePool::_pool;
SimplePool::SimplePool()
{
}


SimplePool::~SimplePool()
{
}

void SimplePool::subscribe(Entity * const & obj)
{
	_pool.push_back(obj);
}

void SimplePool::deSubscribe(Entity * const & obj)
{
	obj->destroy();
	_pool.remove(obj);
}

void SimplePool::drawAll()
{
	for (auto &obj : _pool)//para cada objeto dentro de la lista:haz//no accesas por numero, si no por objeto
	{
		if (!obj->isInitialized())//pregunta si esta inicializado
			obj->Init();//si no esta, lo inicializas	
		obj->draw();//y lo dibujas
	}
}
void SimplePool::updateAll()
{
	for (auto &obj : _pool)//para cada objeto dentro de la lista:haz//no accesas por numero, si no por objeto
	{
		obj->update();//si ya esta lo actualizas
	}
}
/*for auto == for each*/
/*for repeticion
auto --> automatic el compilador va a detectar el tipo de variable que requieres
vairable tipo no sbes y no te importa, como no lo sabes usas auto, en realidad si lo sabes, es un apuntador a Entity
: es una manera especial de asignar en C++, */