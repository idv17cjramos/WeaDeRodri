#include "Map.h"
#include <cstdlib>
#include <fstream>
#include "HelperFunctions.h"

Map::Map(int w, int h, float ratioW, float ratioH, int iterations)
{
	_width = w;
	_height = h;
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			_tiledMap.push_back(Tile(TileType::TileEnumEnd));
			_tiledMap.end()->setXY(j, i);
		}
	}
	_map = new Tree(w, h, ratioW, ratioH, _tiledMap, iterations);
	delete _map;
}

Map::Map(std::string path)
{
	LoadFromFile(path);
}

Map::~Map()
{

}

void Map::drawMap()
{
	for (auto &i : _tiledMap)
	{
		i.draw();
	}
}

void Map::SaveMapToFile(std::string path)
{
	//TODO: Rodri, te toca hacer esto.
}

Tile Map::getTileAt(size_t x, size_t y) const
{
	if (x > _width || y > _height) return Tile(TileType::TileEnumEnd);
	return _tiledMap[getAccessor(x,y,_width)];
}

void Map::setPlayerPositon(int x, int y)
{
	//TODO: mover todas las tiles de forma relativa a la posicion del personaje.
	//nota, la posicion del personaje real siempre va a ser _width/2, _height/2.
}

void Map::LoadFromFile(std::string path)
{
	//TODO: Rodri, te toca hacer esto.
}

Map::Tree::Point::Point(int xval, int yval)
{
	x = xval;
	y = yval;
}

Map::Tree::Rect::Rect(int xval, int yval, int hval, int wval)
{
	x = xval;
	y = yval;
	h = hval;
	w = wval;
}

Map::Tree::Point Map::Tree::Rect::center()
{
	return Point(x + (w / 2), y + (h / 2));
}

void Map::Tree::Rect::drawPath(std::vector<Tile>& tmap, int w, Rect * other)
{
	//TODO: hacer una linea con TileType::path
}

Map::Tree::Leaf::Leaf()
{
}

Map::Tree::Leaf::Leaf(Leaf * const & left, Leaf * const & right)
{
	l = left;
	r = right;
}

Map::Tree::Leaf::Leaf(Rect * rect)
{
	container = rect;
}

Map::Tree::Leaf::~Leaf()
{
	if (l)
		delete l;
	if (r)
		delete r;
	if (container)
		delete container;
}

std::vector<Map::Tree::Leaf*> Map::Tree::Leaf::getLeafs()
{
	if (!l && !r)
		return std::vector<Leaf*>() = { this };
	else
	{
		std::vector<Leaf*> arr;
		if (l)
		{
			auto vec = this->l->getLeafs();
			arr.insert(arr.end(), vec.begin(), vec.end());
		}
		if (r)
		{
			auto vec = this->r->getLeafs();
			arr.insert(arr.end(), vec.begin(), vec.end());
		}
		return arr;
	}
}

std::queue<Map::Tree::Leaf*> Map::Tree::Leaf::getLevel(int level, std::queue<Leaf*>& queue)
{
	if (level == 1)
		queue.push(this);
	else
	{
		if (l)
			l->getLevel(level - 1, queue);
		if (r)
			r->getLevel(level - 1, queue);
	}
	return queue;
}

Map::Tree::Tree(int w, int h, float ratioW, float ratioH, std::vector<Tile>& tmap, int iterations)
{
	_head = new Leaf();
	_ratioH = ratioH;
	_ratioW = ratioW;
	_head->container = new Rect(0, 0, w, h);
	_head = SplitContainer(_head->container, iterations);
	auto leafs = _head->getLeafs();
	for (auto &i : leafs)
		_rooms.push_back(Room(i->container));
	draw(tmap, w);
	drawPaths(tmap, w);
	populate(tmap, w);
}

Map::Tree::~Tree()
{
	if (_head)
		delete _head;
}

Map::Tree::Leaf * Map::Tree::SplitContainer(Rect * head, int iteration)
{
	Leaf* root = new Leaf(head);
	if (iteration)
	{
		auto vec = RandomSplitContainer(head);
		root->l = SplitContainer(vec[0], iteration - 1);
		root->r = SplitContainer(vec[1], iteration - 1);
	}
	return root;
}

std::vector<Map::Tree::Rect*> Map::Tree::RandomSplitContainer(Rect * container)
{
	Rect *r1, *r2;
	if (randomRange(1, 100) <= 50) //vertical
	{
		do
		{
			r1 = new Rect(container->x, container->y, randomRange(1, container->w), container->h);
			r2 = new Rect(container->x + r1->w, container->y, container->w - r1->w, container->h);
		} while (((float)r1->w / (float)r1->h) < _ratioW || ((float)r2->w / (float)r2->h) < _ratioW);
	}
	else
	{
		do
		{
			r1 = new Rect(container->x, container->y, container->w, randomRange(1,container->h));
			r2 = new Rect(container->x, container->y + r1->h, container->w, container->h - r1->h);
		} while (((float)r1->h / (float)r1->w) < _ratioH || ((float)r2->h / (float)r2->w) < _ratioH);
	}
	return std::vector<Rect*>() = { r1, r2 };
}

void Map::Tree::draw(std::vector<Tile>& tmap, int w)
{
	for (auto &i : _rooms)
	{
		TileType newType = (TileType)randomRange(0,1);
		for (int j = 0; j < i.rect->h; ++j)
			for (int k = 0; k < i.rect->w; ++k)
				tmap[getAccessor(k + i.rect->x, j + i.rect->y, w)].SetTileType(newType);
	}
}

void Map::Tree::drawPaths(std::vector<Tile>& tmap, int w)
{
	recursiveDrawPath(tmap, w, _head);
}

void Map::Tree::populate(std::vector<Tile>& tmap, int w)
{
	//TODO: para todas las casillas que no tengan tipo, añadir aleatorio un tipo 
	//de casilla de las que no son chidas, despues para todas las casillas que sean
	//pasillo o bosque añadir aleatoriamente un tesoro o un merchant si no hay casillas
	//adyacientes que no sean bosque o pasillo. Finalmente añadir un boss aleatoriamente
	//por room.
}

void Map::Tree::recursiveDrawPath(std::vector<Tile>& tmap, int w, Leaf * head)
{
	if (!head->l || !head->r) return;
	head->l->container->drawPath(tmap, w, head->r->container);
	recursiveDrawPath(tmap, w, head->l);
	recursiveDrawPath(tmap, w, head->r);
}

Map::Tree::Room::Room(Rect * container)
{
	rect = new Rect(container->x + randomRange(0, container->w / 3), container->y + randomRange(0, container->h / 3), 0, 0);
	rect->w = container->w - (rect->x - container->x);
	rect->h = container->h - (rect->y - container->y);
	rect->w -= randomRange(0, rect->w / 3);
	rect->h -= randomRange(0, rect->h / 3);
}

Map::Tree::Room::~Room()
{
	delete rect;
}
