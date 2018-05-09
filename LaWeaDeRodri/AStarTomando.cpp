#include "AStarTomando.h"
#include <algorithm>
#include "HelperFunctions.h"

AStarTomando::AStarTomando()
{
}


AStarTomando::~AStarTomando()
{
}

void AStarTomando::SetStart(Point start)
{
	_start = start;
}

void AStarTomando::SetEnd(Point end)
{
	_end = end;
}

Point AStarTomando::getCurrPosition()
{
	return Point(_nodeList[_iterator].getX(), _nodeList[_iterator].getY());
}

Point AStarTomando::nextStep()
{
	++_iterator;
	if(_iterator >= _nodeList.size())
		return Point(_nodeList[_nodeList.size() - 1].getX(), _nodeList[_nodeList.size() - 1].getY());
	return Point(_nodeList[_iterator].getX(), _nodeList[_iterator].getY());
}

void AStarTomando::CalculateRoute()
{
	_nodeList.clear();
	if (_map == nullptr)
		return;
	if (_start == _end)
	{
		_nodeList.push_back(Tile());
		return;
	}
	std::vector<Tile> closedSet;
	std::vector<Tile> openSet;
	std::vector<Tile> cameFrom(_map->getMap().size());
	openSet.push_back(_map->getTileAt(_start.x,_start.y));
	std::vector<__int64> gScore(_map->getMap().size(), 9999999), fScore(_map->getMap().size(), 9999999);
	gScore[getAccessor(_start.x, _start.y, gScore.size())] = 0;
	fScore[getAccessor(_start.x, _start.y, gScore.size())] = Point::Manhattan(_start, _end);
	Tile current;
	Point currPoint;
	int currindex;
	while (!openSet.empty())
	{
		currindex = getSmallestF(fScore);
		current = openSet[currindex];
		currPoint = Point(current.getX(), current.getY());
		size_t curracc = getAccessor(current.getX(), current.getY(), gScore.size());
		if (currPoint == _end)
		{
			reconstructPath(cameFrom, current);
			return;
		}
		openSet.erase(openSet.begin() + currindex);
		closedSet.push_back(current);
		if (!tileInSet(closedSet, *current.down))
		{
			size_t downacc = getAccessor(current.down->getX(), current.down->getY(), cameFrom.size());
			Point downPoint = Point(current.down->getX(), current.down->getY());
			openSet.push_back(*current.down);
			__int64 tentativeGScore = gScore[curracc] +
				Point::Manhattan(downPoint, _end);
			if (tentativeGScore < gScore[downacc])
			{
				cameFrom[downacc] = current;
				cameFrom[downacc].SetStatus(TileStatus::Walked);
				gScore[downacc] = tentativeGScore;
				fScore[downacc] = gScore[downacc] + Point::Manhattan(downPoint, _end);
			}
		}
		if (!tileInSet(closedSet, *current.up))
		{
			size_t upacc = getAccessor(current.up->getX(), current.up->getY(), cameFrom.size());
			Point upPoint = Point(current.up->getX(), current.up->getY());
			openSet.push_back(*current.up);
			__int64 tentativeGScore = gScore[curracc] +
				Point::Manhattan(upPoint, _end);
			if (tentativeGScore < gScore[upacc])
			{
				cameFrom[upacc] = current;
				cameFrom[upacc].SetStatus(TileStatus::Walked);
				gScore[upacc] = tentativeGScore;
				fScore[upacc] = gScore[upacc] + Point::Manhattan(upPoint, _end);
			}
		}
		if (!tileInSet(closedSet, *current.left))
		{
			size_t leftacc = getAccessor(current.left->getX(), current.left->getY(), cameFrom.size());
			Point leftPoint = Point(current.left->getX(), current.left->getY());
			openSet.push_back(*current.left);
			__int64 tentativeGScore = gScore[curracc] +
				Point::Manhattan(leftPoint, _end);
			if (tentativeGScore < gScore[leftacc])
			{
				cameFrom[leftacc] = current;
				gScore[leftacc] = tentativeGScore;
				cameFrom[leftacc].SetStatus(TileStatus::Walked);
				fScore[leftacc] = gScore[leftacc] + Point::Manhattan(leftPoint, _end);
			}
		}
		if (!tileInSet(closedSet, *current.right))
		{
			size_t rightacc = getAccessor(current.right->getX(), current.right->getY(), cameFrom.size());
			Point rightPoint = Point(current.right->getX(), current.right->getY());
			openSet.push_back(*current.right);
			__int64 tentativeGScore = gScore[curracc] +
				Point::Manhattan(rightPoint, _end);
			if (tentativeGScore < gScore[rightacc])
			{
				cameFrom[rightacc] = current;
				cameFrom[rightacc].SetStatus(TileStatus::Walked);
				gScore[rightacc] = tentativeGScore;
				fScore[rightacc] = gScore[rightacc] + Point::Manhattan(rightPoint, _end);
			}
		}
	}
	return;
}

void AStarTomando::SetMap(Map * const & map)
{
	_map = map;
}

int AStarTomando::getSmallestF(const std::vector<__int64>& fvals)
{
	__int64 minVal = INT64_MAX;
	int ret = 0;
	for (int i = 0; i < fvals.size(); ++i)
	{
		if (fvals[i] <= minVal)
		{
			minVal = fvals[i];
			ret = i;
		}
	}
	return ret;
}

bool AStarTomando::tileInSet(std::vector<Tile>& set, Tile & tile)
{
	for(auto &i : set)
	{ 
		if (i.getX() == tile.getX() && i.getY() == tile.getY())
			return true;
	}
	return false;
}

void AStarTomando::reconstructPath(const std::vector<Tile>& cameFrom, const Tile & current)
{
	_nodeList.push_back(current);
	//añadir a NodeList todos los elementos que tengan walked recorriendo desde current
	//https://en.wikipedia.org/wiki/A*_search_algorithm
}
