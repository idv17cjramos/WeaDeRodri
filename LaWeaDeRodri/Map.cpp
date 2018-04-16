#include "Map.h"



Map::Map()
{
}


Map::~Map()
{
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

Map::Tree::Leaf::Leaf()
{
}

Map::Tree::Leaf::Leaf(Leaf * const & left, Leaf * const & right)
{
	l = left;
	r = right;
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
	std::vector<Leaf*> arr;
	if (!l && !r)
		return std::vector<Leaf*>() = { this };
	else
		return ;
}

std::queue<Map::Tree::Leaf*> Map::Tree::Leaf::getLevel(int level, std::queue<Leaf*> queue)
{
	return std::queue<Leaf*>();
}

Map::Tree::Tree(int w, int h)
{
	head = new Leaf();
	head->container = new Rect(0, 0, w, h);
}

Map::Tree::~Tree()
{
	if (head)
		delete head;
}

Map::Tree::Leaf * Map::Tree::SplitContainer(Leaf * head, int iteration)
{
	return nullptr;
}

std::vector<Map::Tree::Leaf*> Map::Tree::RandomSplitContainer(Leaf * container)
{
	return std::vector<Leaf*>();
}

int Map::Tree::randomRange(int min, int max)
{
	return 0;
}

void Map::Tree::draw()
{
}
