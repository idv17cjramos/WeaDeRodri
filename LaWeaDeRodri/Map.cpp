#include "Map.h"
#include <cstdlib>
#include <fstream>
#include "HelperFunctions.h"
#include "Engine.h"

int _livingBosses;

Map::Map(int w, int h, float ratioW, float ratioH, int iterations)
{
	_width = w;
	_height = h;
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			_tiledMap.push_back(Tile(TileType::TileEnumEnd));
			_tiledMap[_tiledMap.size() - 1].setXY(j, i);
			//_tiledMap[_tiledMap.size() - 1].Init();
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
	Engine::getInstance()->ReportInteraction();
}

void Map::SaveMapToFile(std::string path)
{
	std::fstream elArchivo(path,std::ios::out | std::ios::trunc);
	elArchivo << *this;
}

Tile Map::getTileAt(size_t x, size_t y) const
{
	if (x > _width || y > _height) return Tile(TileType::TileEnumEnd);
	return _tiledMap[getAccessor(x,y,_width)];
}

void Map::setPlayerPositon(int x, int y)
{
	for (int i = 0; i < _height; ++i)
		for (int j = 0; j < _width; ++j)
			_tiledMap[getAccessor(j, i, _width)].setXY(j + x, i + y);
	
}

int Map::getLivingBosses()
{
	return _livingBosses;
}

void Map::KillBoss()
{
	--_livingBosses;
}

void Map::LoadFromFile(std::string path)
{ 
	std::fstream elArchivo(path, std::ios::in);
	elArchivo >> *this;
}

Map::Tree::Point::Point(int xval, int yval)
{
	x = xval;
	y = yval;
}

Map::Tree::Point Map::Tree::Point::operator-(Point other)
{
	return Point(x - other.x, y - other.y);
}

Map::Tree::Rect::Rect()
{
	x = y = h = w = 0;
}

Map::Tree::Rect::Rect(int xval, int yval, int wval, int hval)
{
	x = xval;
	y = yval;
	h = hval;
	w = wval;
}

Map::Tree::Rect::Rect(Rect * head)
{
	x = head->x;
	y = head->y;
	h = head->h;
	w = head->w;
}

Map::Tree::Point Map::Tree::Rect::center()
{
	return Point(x + (w / 2), y + (h / 2));
}

void Map::Tree::Rect::drawPath(std::vector<Tile>& tmap, int w, Rect * other)
{
	Point otherCenter = other->center();
	Point dir = center() - otherCenter;
	if (abs(dir.x) > abs(dir.y))
	{
		if (!dir.x)return;
		int dirX = dir.x / abs(dir.x);
		for (int i = center().x; i < otherCenter.x; ++i)
		{
			if(tmap[getAccessor(i, otherCenter.y, w)].GetType() == TileType::TileEnumEnd)
				tmap[getAccessor(i, otherCenter.y, w)].SetTileType(TileType::Path);
		}
	}
	else{
		if (!dir.y)return;
		int dirY = dir.y / abs(dir.y);
		for (int i = center().y; i < otherCenter.y; ++i)
		{
			if (tmap[getAccessor(otherCenter.x, i, w)].GetType() == TileType::TileEnumEnd)
				tmap[getAccessor(otherCenter.x, i, w)].SetTileType(TileType::Path);
		}
	}
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
	container = new Rect(rect);
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
	_rooms.reserve(leafs.size());
	for (auto &i : leafs)
		_rooms.emplace_back(i->container);
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
		auto vec = RandomSplitContainer(root->container);
		root->l = SplitContainer(vec[0], iteration - 1);
		root->r = SplitContainer(vec[1], iteration - 1);
		delete vec[0];
		delete vec[1];
	}
	return root;
}

std::vector<Map::Tree::Rect*> Map::Tree::RandomSplitContainer(Rect * container)
{
	Rect *r1 = nullptr, *r2 = nullptr;
	if (randomRange(1, 100) <= 50) //vertical
	{
		do
		{
			if (r1)
				delete r1;
			if (r2)
				delete r2;
			r1 = new Rect(container->x, container->y, randomRange(1, container->w), container->h);
			r2 = new Rect(container->x + r1->w, container->y, container->w - r1->w, container->h);
		} while (/*((float)r1->w / (float)r1->h) < _ratioW || ((float)r2->w / (float)r2->h) < _ratioW*/ false);
	}
	else
	{
		do
		{
			if (r1)
				delete r1;
			if (r2)
				delete r2;
			r1 = new Rect(container->x, container->y, container->w, randomRange(1,container->h));
			r2 = new Rect(container->x, container->y + r1->h, container->w, container->h - r1->h);
		} while (/*((float)r1->h / (float)r1->w) < _ratioH || ((float)r2->h / (float)r2->w) < _ratioH*/ false);
	}
	return std::vector<Rect*>() = { r1, r2 };
}

void Map::Tree::draw(std::vector<Tile>& tmap, int w)
{
	size_t height = tmap.size() / w;
	for (int j = 0; j < height; ++j)
		for (int k = 0; k < w; ++k)
		{
			size_t accessor = getAccessor((size_t)k, (size_t)j, w);
			if (k - 1 > 0)
				tmap[accessor].left = &tmap[getAccessor((size_t)k - 1, (size_t)j, w)];
			else
				tmap[accessor].left = new Tile(TileType::TileEnumEnd);
			if (k + 1 < w)
				tmap[accessor].right = &tmap[getAccessor((size_t)k + 1, (size_t)j, w)];
			else
				tmap[accessor].right = new Tile(TileType::TileEnumEnd);
			if (k - 1 > 0)
				tmap[accessor].up = &tmap[getAccessor((size_t)k, (size_t)j - 1, w)];
			else
				tmap[accessor].up = new Tile(TileType::TileEnumEnd);
			if (k + 1 < height)
				tmap[accessor].down = &tmap[getAccessor((size_t)k, (size_t)j + 1, w)];
			else
				tmap[accessor].down = new Tile(TileType::TileEnumEnd);
		}
	for (auto &i : _rooms)
	{
		TileType newType = (TileType)randomRange(0,2);
		for (int j = 0; j < i.rect->h; ++j)
			for (int k = 0; k < i.rect->w; ++k)
			{
				size_t accessor = getAccessor((size_t)k + (size_t)i.rect->x, (size_t)j + (size_t)i.rect->y, w);
				tmap[accessor].SetTileType(newType);
			}
	}
}

void Map::Tree::drawPaths(std::vector<Tile>& tmap, int w)
{
	recursiveDrawPath(tmap, w, _head);
}

void Map::Tree::populate(std::vector<Tile>& tmap, int w)
{
	for (int i = 0; i < tmap.size(); ++i)
	{
		if (tmap[i].GetType() == TileType::TileEnumEnd)
			tmap[i].SetTileType((TileType)randomRange(TileType::Lava, TileType::Rock + 1));
		if (tmap[i].GetType() == TileType::Path || tmap[i].GetType() == TileType::Forest)
		{
			if ((tmap[i].left->GetType() == TileType::Path || tmap[i].left->GetType() == TileType::Forest) &&
				(tmap[i].right->GetType() == TileType::Path || tmap[i].right->GetType() == TileType::Forest) &&
				(tmap[i].up->GetType() == TileType::Path || tmap[i].up->GetType() == TileType::Forest) &&
				(tmap[i].down->GetType() == TileType::Path || tmap[i].down->GetType() == TileType::Forest) &&
				randomRange(0,1000) < 3)
				tmap[i].SetTileType((TileType)randomRange(TileType::Rock, TileType::Merchant + 1));
		}
	}
	for (auto &i : _rooms)
	{
		tmap[getAccessor(randomRange(i.rect->x, i.rect->x + i.rect->w),
			randomRange(i.rect->y, i.rect->y + i.rect->h), w)].SetTileType(TileType::Boss);
		++_livingBosses;
	}
}

void Map::Tree::recursiveDrawPath(std::vector<Tile>& tmap, int w, Leaf * head)
{
	if (!head->l || !head->r) return;
	head->l->container->drawPath(tmap, w, head->r->container);
	recursiveDrawPath(tmap, w, head->l);
	recursiveDrawPath(tmap, w, head->r);
}

Map::Tree::Room::Room(Rect * const& container) : Room()
{
	rect = new Rect(container->x + randomRange(0, container->w / 3), container->y + randomRange(0, container->h / 3), 0, 0);
	rect->w = container->w - (rect->x - container->x);
	rect->h = container->h - (rect->y - container->y);
	rect->w -= randomRange(0, rect->w / 3);
	rect->h -= randomRange(0, rect->h / 3);
}

Map::Tree::Room::Room(const Rect & container)
{
	rect = new Rect(container.x + randomRange(0, container.w / 3), container.y + randomRange(0, container.h / 3), 0, 0);
	rect->w = container.w - (rect->x - container.x);
	rect->h = container.h - (rect->y - container.y);
	rect->w -= randomRange(0, rect->w / 3);
	rect->h -= randomRange(0, rect->h / 3);
}

Map::Tree::Room::Room()
{
	rect = nullptr;
}

Map::Tree::Room::~Room()
{
	if(rect)
		delete rect;
}

std::ostream & operator<<(std::ostream & o, Map& map)
{
	//o.write((char*)((size_t)map._width), sizeof(int));
	//o.write((char*)((size_t)map._height), sizeof(int));
	o << map._width << " " << map._height << " ";
	for (auto &i : map._tiledMap)
	{
		//o.write((char*)i.GetType(), sizeof(TileType));
		//o.write((char*)i.getX(), sizeof(int));
		//o.write((char*)i.getY(), sizeof(int));
		o << (int)i.GetType() << " " << i.getX() << " " << i.getY() << " ";
	}
	return o;
}

std::istream & operator>>(std::istream & i, Map& map)
{
	//i.read((char*)&map._width, sizeof(int));
	//i.read((char*)&map._height, sizeof(int));
	i >> map._width >> map._height;
	for (int j = 0; j < map._width * map._height; ++j)
	{
		int t;
		int x, y;
		i >> t >> x >> y;
		//i.read((char*)&t, sizeof(TileType));
		//i.read((char*)&x, sizeof(int));
		//i.read((char*)&y, sizeof(int));
		map._tiledMap.push_back(Tile((TileType)t));
		map._tiledMap[j].setXY(x, y);
	}
	for (int j = 0; j < map._height; ++j)
		for (int k = 0; k < map._width; ++k)
		{
			size_t accessor = getAccessor((size_t)k, (size_t)j, map._width);
			if (k - 1 > 0)
				map._tiledMap[accessor].left = &map._tiledMap[getAccessor((size_t)k - 1, (size_t)j, map._width)];
			else
				map._tiledMap[accessor].left = new Tile(TileType::TileEnumEnd);
			if (k + 1 < map._width)
				map._tiledMap[accessor].right = &map._tiledMap[getAccessor((size_t)k + 1, (size_t)j, map._width)];
			else
				map._tiledMap[accessor].right = new Tile(TileType::TileEnumEnd);
			if (k - 1 > 0)
				map._tiledMap[accessor].up = &map._tiledMap[getAccessor((size_t)k, (size_t)j - 1, map._width)];
			else
				map._tiledMap[accessor].up = new Tile(TileType::TileEnumEnd);
			if (k + 1 < map._height)
				map._tiledMap[accessor].down = &map._tiledMap[getAccessor((size_t)k, (size_t)j + 1, map._width)];
			else
				map._tiledMap[accessor].down = new Tile(TileType::TileEnumEnd);
		}
	// TODO: insert return statement here
	return i;
}
